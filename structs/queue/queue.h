#pragma once
#include <stdbool.h> 

#define QU_CAP 100

typedef struct{
    double buff[QU_CAP];
    int count;
    int head;
} dbl_queue;

void dbl_q_init(dbl_queue *q);
bool dbl_q_push(dbl_queue *q, double val);
double dbl_q_pop(dbl_queue *q);
bool dbl_q_is_empty(dbl_queue *q);
void dbl_q_destr(dbl_queue *q);
