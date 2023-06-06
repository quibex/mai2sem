#pragma once
#include <stdbool.h> 

typedef struct
{
    double key;
    char data[100];
} elem ;

typedef struct {
    elem * buf;
    int head;
    int size;
    int cap;
} dbl_vec;

void dbl_vec_init(dbl_vec *v);
void dbl_vec_destroy(dbl_vec *v);
bool dbl_vec_push_back(dbl_vec *v, elem val);
bool dbl_vec_push_front(dbl_vec *v,  elem val);
elem dbl_vec_pop_back(dbl_vec *v);
elem dbl_vec_pop_front(dbl_vec *v);
bool dbl_vec_is_empty(dbl_vec *v);
int dbl_vec_get_size(dbl_vec *v);
bool dbl_vec_set_size(dbl_vec *v, int new_size);
elem dbl_vec_get_el(dbl_vec *v, int index);
void dbl_vec_set_el(dbl_vec *v, int index, elem val);
elem dbl_vec_head(dbl_vec * v);
elem dbl_vec_tail(dbl_vec * v);