#include <stdbool.h>
#include "queue.h"

void dbl_q_init(dbl_queue *q){
    q->count=0;
    q->head=0;
}

bool dbl_q_push(dbl_queue *q, double val){
    if (q->count == QU_CAP){
        return false;
    }
    q->buff[(q->count + q->head)%QU_CAP] = val;
    q->count++;
    return true;
}

double dbl_q_pop(dbl_queue *q){
    double res = q->buff[q->head];
    q->head = (q->head+1)%QU_CAP;
    q->count--;
    return res; 
}

bool dbl_q_is_empty(dbl_queue *q){
    if (q->count==0){
        return true;
    }
    return false;
}

void dbl_q_destr(dbl_queue *q){
    q->count=0;
}



