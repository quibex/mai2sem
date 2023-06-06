#pragma once
#include <stdbool.h> 

typedef struct{
    double *buff;
    int count;
    int head;
    int cap;
} dbl_dk;

void dbl_dk_init(dbl_dk *dk);
// bool dbl_dk_resize(dbl_dk *dk, int new_cap);
bool dbl_dk_push_back(dbl_dk *dk, double val);
bool dbl_dk_push_front(dbl_dk *dk, double val);
double dbl_dk_pop_back(dbl_dk *dk);
double dbl_dk_pop_front(dbl_dk *dk);
bool dbl_dk_is_empty(dbl_dk *dk);
void dbl_dk_destr(dbl_dk *dk);
