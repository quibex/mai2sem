#pragma once
#include <stdbool.h> 

typedef struct {
    int clmn;
    double val;
    int next_el_idx;
} dbl_mx_el;

typedef struct {
    dbl_mx_el * buf;
    int head;
    int size;
    int cap;
} mx_vector;

void mx_init(mx_vector *v);
void mx_destroy(mx_vector *v);
bool mx_push_back(mx_vector *v, dbl_mx_el val);
bool mx_push_front(mx_vector *v,  dbl_mx_el val);
dbl_mx_el mx_pop_back(mx_vector *v);
dbl_mx_el mx_pop_front(mx_vector *v);
bool mx_is_empty(mx_vector *v);
int mx_get_size(mx_vector *v);
bool mx_set_size(mx_vector *v, int new_size);
dbl_mx_el mx_get_el(mx_vector *v, int index);
dbl_mx_el mx_get_front_el(mx_vector *v);
dbl_mx_el mx_get_back_el(mx_vector *v);
void mx_set_el(mx_vector *v, int index, dbl_mx_el val);