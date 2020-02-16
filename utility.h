#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#if WIN32
#include <windows.h>
#endif

#if linux
#include <unistd.h>
#endif

#define DEBUG 1
#define MAX_VAL 100
#define SRT_ITV 30
#define STP_ITV 10
#define WAIT_SECOND 1
#define LOG(...)\
{\
    fprintf(stderr, "%s %s [%d]: ", __FILE__, __FUNCTION__, __LINE__);\
    fprintf(stderr, __VA_ARGS__);\
}

int Random(int m, int n);

void ssleep(int a);
