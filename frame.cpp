#include "frame.h"

frame::frame(){
    poc = -1;
    val = -1;
}

frame::frame(const frame &f) {
    poc = f.poc;
    val = f.val;
    depsize = f.depsize;
    copy(f.dep.begin(), f.dep.end(), dep.begin());
}

frame::frame(int i, int v):poc(i), val(v) {}

frame::frame(int i, int v, int a, int b) {
    poc = i;
    val = v;
    if(a>=0) {
        dep.push_back(a);
    }
    if(b>=0) {
        dep.push_back(b);
    }
    depsize = dep.size();
}