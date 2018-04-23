#include <iostream>
#include <algorithm>
#include <map>
#include "threadpool.h"
#include "frame.h"
#include "FrameGop.h"

using namespace std;

struct f_pipe {
    int tar;
    condition_variable &cv;
    f_pipe(int _tar, condition_variable &_cv)
        :tar(_tar), cv(_cv) {}
};

int main() {
    FrameGop framegop;
    framegop.init();
    return 0;
}
