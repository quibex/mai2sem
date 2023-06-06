#pragma once
#include <stdbool.h> 

typedef struct {
    double * buf;
    int head;
    int size;
    int cap;
} dbl_vector;

void dbl_init(dbl_vector *v);
void dbl_destroy(dbl_vector *v);
bool dbl_push_back(dbl_vector *v, double val);
bool dbl_push_front(dbl_vector *v,  double val);
double dbl_pop_back(dbl_vector *v);
double dbl_pop_front(dbl_vector *v);
bool dbl_is_empty(dbl_vector *v);
int dbl_get_size(dbl_vector *v);
bool dbl_set_size(dbl_vector *v, int new_size);
double dbl_get_el(dbl_vector *v, int index);
void dbl_set_el(dbl_vector *v, int index, double val);