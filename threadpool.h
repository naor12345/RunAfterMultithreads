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
    void addThread(int size);

    void init(int size);
    inline threadpool() {}

    inline ~threadpool() {
        _run = false;
        _task_cv.notify_all();
        for(thread &th : _pool) {
            if(th.joinable()) th.join();
        }
    }

    template<class F, class ... Args>
    auto commit(F &&f, Args &&...args) -> future<decltype(f(args...))>;

    void drain_task();
};

