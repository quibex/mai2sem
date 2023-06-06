#pragma once
#include <stdbool.h> 

#define DK_CAP 4

typedef struct{
    double buff[DK_CAP];
    int count;
    int head;
} dbl_dack;

void dbl_dk_init(dbl_dack *dk);
bool dbl_dk_push_back(dbl_dack *dk, double val);
bool dbl_dk_push_front(dbl_dack *dk, double val);
double dbl_dk_pop_front(dbl_dack *dk);
double dbl_dk_pop_back(dbl_dack *dk);
bool dbl_dk_is_empty(dbl_dack *dk);
void dbl_dk_destr(dbl_dack *dk);
