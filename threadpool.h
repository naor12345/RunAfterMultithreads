#pragma once
#ifndef THREAD_POOL_H
#define THREAD_POOL_H
#include <vector>
#include <queue>
#include <atomic>
#include <future>
#include <condition_variable>
#include <thread>
#include <functional>
#include <stdexcept>

#define  THREADPOOL_MAX_NUM 17

namespace std{
class threadpool {
    using Task = function < void() > ;
    vector<thread> _pool;
    queue<Task> _tasks;
    mutex _lock;
    mutex _drain_lock;
    condition_variable _task_cv;
    condition_variable _drain_cv;
    atomic<bool> _run{ true };
    atomic<int>  _idlThrNum{ 0 };
    atomic<int>  _totalThrNum{ 0 };
  public:
    inline threadpool(unsigned short size = 4) {
        addThread(size);
    }
    inline ~threadpool() {
        _run = false;
        _task_cv.notify_all();
        for (thread& thread : _pool) {
            if (thread.joinable()) thread.join();
        }
    }
  public:
    template<class F, class... Args>
    auto commit(F&& f, Args&&... args) -> future < decltype(f(args...)) > {
        if (!_run) throw runtime_error("commit on ThreadPool is stopped.");
        using RetType = decltype(f(args...));
        auto task = make_shared<packaged_task<RetType()>>(
            bind(forward<F>(f), forward<Args>(args)...)
        );
        future<RetType> future = task->get_future();
        {
            lock_guard<mutex> lock{ _lock };
            _tasks.emplace([task]() {
                (*task)();
            });
        }
        _task_cv.notify_one();
        return future;
    }

    void drainTask() {
        unique_lock<mutex> lock{ _drain_lock };
        _drain_cv.wait(lock, [this] {
            return _run && _tasks.empty() && (_idlThrNum == _totalThrNum);
        });
    }
    int idlCount() {
        return _idlThrNum;
    }
    int thrCount() {
        return _pool.size();
    }

    void addThread(unsigned short size) {
        for (; _pool.size() < THREADPOOL_MAX_NUM && size > 0; --size) {
            _pool.emplace_back([this] {
                while (_run) {
                    Task task;
                    {
                        unique_lock<mutex> lock{ _lock };
                        _task_cv.wait(lock, [this] {
                            return !_run || !_tasks.empty();
                        });
                        if (!_run && _tasks.empty())
                            return;
                        task = move(_tasks.front());
                        _tasks.pop();
                    }
                    _idlThrNum--;
                    task();
                    _idlThrNum++;
                    if (_run && _tasks.empty() && _idlThrNum == _totalThrNum) {
                        _drain_cv.notify_one();
                    }
                }
            });
            _idlThrNum++;
            _totalThrNum++;
        }
    }
};
}
#endif
