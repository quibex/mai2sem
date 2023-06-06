#include <stdbool.h>
#include "dack.h"

void dbl_dk_init(dbl_dack *dk){
    dk->count=0;
    dk->head=0;
}

bool dbl_dk_push_back(dbl_dack *dk, double val){
    if (dk->count == DK_CAP){
        return false;
    }
    dk->buff[(dk->count + dk->head)%DK_CAP] = val;
    dk->count++;
    return true;
}

bool dbl_dk_push_front(dbl_dack *dk, double val){
    if (dk->count == DK_CAP){
        return false;
    }
    dk->buff[(dk->head-1+DK_CAP)%DK_CAP] = val;
    dk->head = (dk->head-1+DK_CAP)%DK_CAP;
    dk->count++;
    return true;
}

double dbl_dk_pop_front(dbl_dack *dk){
    double res = dk->buff[dk->head];
    dk->head = (dk->head+1)%DK_CAP;
    dk->count--;
    return res; 
}

double dbl_dk_pop_back(dbl_dack *dk){
    double res = dk->buff[(dk->head+dk->count-1)%DK_CAP];
    dk->count--;
    return res; 
}

bool dbl_dk_is_empty(dbl_dack *dk){
    if (dk->count==0){
        return true;
    }
    return false;
}

void dbl_dk_destr(dbl_dack *dk){
    dk->count=0;
}



