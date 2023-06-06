#pragma once 
#include <stdbool.h>

typedef struct {
    int *buf;
    int size;
} dbl_vec;

void dv_init(dbl_vec *v);
void dv_destroy(dbl_vec *v);
int dv_size(dbl_vec *v);
void dv_resize(dbl_vec *v, int new_size);
double dv_get(dbl_vec *v, int index);
void dv_put(dbl_vec *v, int index, double val);
