#include <iostream>
#include <algorithm>
#include <map>
#include "framegop.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 


int main() {
    srand((int)time(NULL));
    FrameGop framegop;
    framegop.init();
    framegop.processparallel();
    
    return 0;
}
