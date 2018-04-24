#include <vector>
#include "threadpool.h"
#include "frame.h"
#include <map>

class FrameGop {
  public:
    std::vector<frame> frames{17, frame()};
    std::threadpool thp{17};
    std::map<int, int> fmeToIdx;
    FrameGop();
    ~FrameGop();
    void process(int i);
    void process0(int i);
    void process1(int i);
    void process2(int i);
    void init() ;
    void processparallel();
};