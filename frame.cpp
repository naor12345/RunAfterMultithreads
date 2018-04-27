#include "frame.h"

frame::frame(){
	isFinish = false;
    poc = -1; 
    val = -1; // -> to 300
}

frame::frame(const frame &f) {
    poc = f.poc;
    val = f.val;
	isFinish = f.isFinish;
    depsize = f.depsize;
    std::copy(f.dep.begin(), f.dep.end(), dep.begin());
}

void frame::pushWaiting(int tar, int poc, std::condition_variable *fcv){
    std::lock_guard<std::mutex> lock{mtx_push};
    waiting.emplace(tar, poc, fcv);
}

void frame::set(int idx, int a, int b, int val){
    if(dep.size() != 0) dep.clear();
    poc = idx;
    this->val = val;
	if (val < MAX_VAL) {
		isFinish = false;
	}

    if(a>=0) {
        dep.push_back(a);
    }
    if(b>=0) {
        dep.push_back(b);
    }
    depsize = dep.size();
}

frame::frame(int i, int v):poc(i), val(v) {
	if (val < MAX_VAL) {
		isFinish = false;
	}
}

frame::frame(int i, int v, int a, int b) {
    poc = i;
    val = v;
	if (val < MAX_VAL) {
		isFinish = false;
	}
    if(a>=0) {
        dep.push_back(a);
    }
    if(b>=0) {
        dep.push_back(b);
    }
    depsize = dep.size();
}
