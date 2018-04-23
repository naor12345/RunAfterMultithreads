#include <vector>
#include "threadpool.h"
#include "frame.h"
#include <map>

class FrameGop {
  public:
    vector<frame> frames;
    threadpool thp;
    map<int, int> fmeToIdx;
    FrameGop();
    ~FrameGop();
    void process();
    void init() ;
};