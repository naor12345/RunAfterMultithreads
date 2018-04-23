#include "frame.h"

frame::frame(){
    poc = -1; 
    val = -1; // -> to 300
}

frame::frame(const frame &f) {
    poc = f.poc;
    val = f.val;
    depsize = f.depsize;
    std::copy(f.dep.begin(), f.dep.end(), dep.begin());
}

void frame::set(int idx, int a, int b, int val){
    if(dep.size() != 0) dep.clear();
    poc = idx;
    this->val = val;

    if(a>=0) {
        dep.push_back(a);
    }
    if(b>=0) {
        dep.push_back(b);
    }
    depsize = dep.size();
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