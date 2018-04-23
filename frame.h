#include <vector>
#include <mutex>
#include <condition_variable>
using namespace std;

class frame {
  public:
    int poc;
    int val;
    vector<int> dep;
    int depsize;
    mutex _wait;
    condition_variable _goCv;

    frame();

    frame::frame(const frame &f);

    frame(int i, int v);

    frame::frame(int i, int v, int a, int b); 
};