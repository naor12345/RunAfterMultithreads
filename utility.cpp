#include "utility.h"

// a: second
void ssleep(int a){
#if linux
	sleep(a);
#endif

#if WIN32
	Sleep(a * 1000);
#endif
}

int Random(int m, int n)
{
	srand((int)time(NULL));
    int pos, dis;
    if(m == n)
    {
        return m;
    }
    else if(m > n)
    {
        pos = n;
        dis = m - n + 1;
        return rand() % dis + pos;
    }
    else
    {
        pos = m;
        dis = n - m + 1;
        return rand() % dis + pos;
    }
}