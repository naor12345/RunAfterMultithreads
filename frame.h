#include <vector>
#include <mutex>
#include <condition_variable>
#include <queue>
struct f_pipe {
    int tar;
    int poc;
    std::condition_variable &cv;
    f_pipe(int _tar, int _poc, std::condition_variable &_cv)
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
    std::vector<int> dep;
    int depsize;
    std::mutex _wait;
    std::condition_variable _goCv;
    std::priority_queue<f_pipe, std::vector<f_pipe>, comp> waiting;


    frame();

    void set(int idx, int a, int b, int v = 0);

    frame(const frame &f);

    frame(int i, int v);

    frame(int i, int v, int a, int b); 
};