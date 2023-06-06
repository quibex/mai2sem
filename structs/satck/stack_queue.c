#include <stdio.h>


#define ST_CAP 100000

typedef struct {
    double buf[ST_CAP];
    int count;
} STACK;

bool dd_push_back(STACK *s, double val){
    if (s->count==(ST_CAP)){
        return false;
    }
    s->buf[s->count] = val;
    s->count++
    return true;
}



