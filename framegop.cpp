#include "framegop.h"

FrameGop::FrameGop(){}

FrameGop::~FrameGop(){}

void FrameGop::process(){

}

void FrameGop::init(){
    thp.init(17);
    frames.emplace_back(0, 0, -1, -1);
    frames.emplace_back(16, 0, 0, -1);
    frames.emplace_back(8, 0, 0, 16);
    frames.emplace_back(4, 0, 0, 8);
    frames.emplace_back(2, 0, 0, 4);
    frames.emplace_back(1, 0, 0, 2);
    frames.emplace_back(3, 0, 2, 4);
    frames.emplace_back(6, 0, 4, 8);
    frames.emplace_back(5, 0, 4, 6);
    frames.emplace_back(7, 0, 6, 8);
    frames.emplace_back(12, 0, 8, 16);
    frames.emplace_back(10, 0, 8, 12);
    frames.emplace_back(9, 0, 8, 10);
    frames.emplace_back(11, 0, 10, 12);
    frames.emplace_back(14, 0, 12, 16);
    frames.emplace_back(13, 0, 12, 14);
    frames.emplace_back(15, 0, 14, 16);
    fmeToIdx[0] = 0;
    fmeToIdx[16] = 1;
    fmeToIdx[8] = 2;
    fmeToIdx[4] = 3;
    fmeToIdx[2] = 4;
    fmeToIdx[1] = 5;
    fmeToIdx[3] = 6;
    fmeToIdx[6] = 7;
    fmeToIdx[5] = 8;
    fmeToIdx[7] = 9;
    fmeToIdx[12] = 10;
    fmeToIdx[10] = 11;
    fmeToIdx[9] = 12;
    fmeToIdx[11] = 13;
    fmeToIdx[14] = 14;
    fmeToIdx[13] = 15;
    fmeToIdx[15] = 16;
}