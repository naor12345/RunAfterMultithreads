#include "framegop.h"
#include "utility.h"
#include <iostream>

FrameGop::FrameGop(){}

FrameGop::~FrameGop(){}

void FrameGop::process0(int idx){
    // vector<frames> idx
    frame &f = frames[idx];
    while(f.val < 300)
    {
        //get the self-plus number
        int dval = Random(5,10);
        if(f.val + dval > 300) dval = MAX_VAL-f.val;
        f.val += dval;
        while(!f.waiting.empty() && f.waiting.top().tar <= f.val)
        {
            f.waiting.top().cv.notify_one();
            f.waiting.pop();
        }
        //sleep
        sleep(2);
    }
    std::cout<<f.poc<<" finished"<<std::endl;
}

void FrameGop::process1(int idx){
    // vector<frames> idx
    frame &f = frames[idx];
    while(f.val < 300)
    {
        //get the self-plus number
        int dval = Random(5,10);
        if(f.val + dval > 300) dval = MAX_VAL-f.val;

        //check        
        int xval = frames[fmeToIdx[f.dep[0]]].val;
        int ftar = f.val + dval
        if(f.val+dval+STP_ITV<xval){
            f.val += dval;
        }
        else{            
            std::unique_lock<std::mutex> lock{f._wait};
            f._goCv.wait(lock, [this]{
                
            });
        }



        
        
        
        
        //sleep
        sleep(2);
    }
}

void FrameGop::process2(int idx){
// vector<frames> idx
    frame &f = frames[idx];
    while(f.val < 300)
    {
        //get the self-plus number
        int dval = Random(5,10);
        if(f.val + dval > 300) dval = MAX_VAL-f.val;

        //check
        if(f.depsize == 0)
            f.val += dval;
        else if(f.depsize == 1){
            int xval = frames[fmeToIdx[f.dep[0]]].val;
            
        }
        
        
        
        //sleep
        sleep(2);
    }
}

void FrameGop::process(int idx){
    if(frames[idx].depsize == 0)
    {
        process0(idx);
    }
    else if(frames[idx].depsize == 1){
        process1(idx);
    }
    else {
        process2(idx);
    }
}

void FrameGop::init(){ 
    frames[0].set(0, -1, -1);
    frames[1].set(16, 0, -1);
    frames[2].set(8, 0, 16);
    frames[3].set(4, 0, 8);
    frames[4].set(2, 0, 4);
    frames[5].set(1, 0, 2);
    frames[6].set(3, 2, 4);
    frames[7].set(6, 4, 8);
    frames[8].set(5, 4, 6);
    frames[9].set(7, 6, 8);
    frames[10].set(12, 8, 16);
    frames[11].set(10, 8, 12);
    frames[12].set(9, 8, 10);
    frames[13].set(11, 10, 12);
    frames[14].set(14, 12, 16);
    frames[15].set(13, 12, 14);
    frames[16].set(15, 14, 16);
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