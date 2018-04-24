#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <unistd.h>

#define DEBUG 1
#define MAX_VAL 300
#define SRT_ITV 30
#define STP_ITV 10
#define LOG(...)\
{\
    fprintf(stderr, "%s %s [%d]: ", __FILE__, __FUNCTION__, __LINE__);\
    fprintf(stderr, __VA_ARGS__);\
}

int Random(int m, int n);
