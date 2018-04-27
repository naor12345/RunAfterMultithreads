#include <vector>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <utility>
#include "utility.h"

struct f_pipe {
    int tar;  // target, greater than target -> continue, (0, MAX_VAL]
    int poc;  // poc of the frame
    std::condition_variable *cv;
    f_pipe(int _tar, int _poc, std::condition_variable *_cv)
        :tar(_tar), poc(_poc), cv(_cv) {}
};

struct comp
{
    bool operator() (const f_pipe &a, const f_pipe &b) const
    {
        return a.tar > b.tar;
    }
};

class frame {
  public:
    int poc;
    int val;
	bool isFinish;
    std::vector<int> dep;
    int depsize;
    std::mutex _wait;
    std::condition_variable _goCv;
    std::priority_queue<f_pipe, std::vector<f_pipe>, comp> waiting;
    std::mutex mtx_push;
    
    void pushWaiting(int tar, int poc, std::condition_variable *fcv);

    frame();

    void set(int idx, int a, int b, int v = 0);

    frame(const frame &f);

    frame(int i, int v);

    frame(int i, int v, int a, int b); 
};
