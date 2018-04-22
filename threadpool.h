#pragma once
#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <vector>
#include <queue>
#include <atomic>
#include <future>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <assert.h>

#define MAX_NUM 17

using namespace std;

class threadpool {
  private:
    using Task = function<void()>;
    vector<thread> _pool;
    queue<Task> _tasks;
    mutex _lock;
    mutex _drain_lock;
    condition_variable _task_cv;
    condition_variable _drain_cv;
    atomic<bool> _run{true};
    atomic<int> _idlThrNum{0};
    atomic<int> _ttlThrNum{0};

  public:
    inline threadpool(unsigned short size) {
        addThread(size);
    }

    inline ~threadpool() {
        _run = false;
        _task_cv.notify_all();
        for(thread &th : _pool) {
            if(th.joinable()) th.join();
        }
    }

    template<class F, class ... Args>
    auto commit(F &&f, Args &&...args) -> future<decltype(f(args...))> {
        if(!_run) {
            assert(false);
        }

        using Ret = decltype(f(args...));
        auto task = make_shared<packaged_task<Ret()>>(bind(forward<F>(f), forward<Args>(args)...));
        future<Ret> fut = task->get_future();
        {
            lock_guard<mutex> lock{_lock};
            _tasks.emplace([task]{
                (*task)();
            });
        }
        _task_cv.notify_one();
        return fut;
    }

    void drain_task() {
        unique_lock<mutex> lock{_drain_lock};
        _drain_cv.wait(lock, [this] {
            return _run && _tasks.empty() && (_idlThrNum == _ttlThrNum);
        });
    }

    void addThread(unsigned int size) {
        for(; _pool.size() < MAX_NUM && size>0; --size) {
            _pool.emplace_back([this] {
                while(_run) {
                    Task task;
                    {
                        unique_lock<mutex> lock{_lock};
                        _task_cv.wait(lock, [this] {
                            return !_run || !_tasks.empty();
                        });
                        if(!_run && _tasks.empty())
                            return;
                        task = move(_tasks.front());
                        _tasks.pop();
                        _idlThrNum--;
                        task();
                        _idlThrNum++;
                        if(_run && _tasks.empty() && _idlThrNum == _ttlThrNum)
                            _drain_cv.notify_one();
                    }
                }
            });
            _idlThrNum++;
            _ttlThrNum++;
        }
    }
};




#endif
