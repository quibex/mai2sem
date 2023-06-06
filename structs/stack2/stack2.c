#include <stdbool.h>
#include "stack2.h"

#define MIN_CAP 32
#define ST_CAP 100
#define NULL 0

static bool inrease(dbl_stack *s){
    int new_cap = 2 * s->cap;
    if (new_cap < MIN_CAP){
        new_cap = MIN_CAP;
    }
    double *tmp = realloc(s->buf, new_cap * sizeof(double));
    if (tmp == NULL){
        return false;
    }
    s->cap = new_cap;
    s->buf = tmp;
    return true;
}

bool ds_push(dbl_stack *s, double val){
    if (s->count==s->cap){
        if(!increase(s)) return false;
    }
    s->buf[s->count] = val;
    s->count++;
    return true;
}

static void decrease_if_possible(dbl_stack *s){
    if (s->count < s->cap/4){
        int new_cap = s->cap/2;
        if (new_cap < MIN_CAP){
            new_cap = MIN_CAP;
        }
        if (new_cap < s->cap){
            s->buf = realloc(s->buf, new_cap*sizeof(double));
        }
        s->cap=new_cap;
    }
}

double ds_pop(dbl_stack *s){
    double res = s->buf[s->count-1];
    s->count--;
    decrease_if_possible(s);
    return res;
}


