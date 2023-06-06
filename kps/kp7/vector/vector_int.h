#pragma once
#include <stdbool.h> 

typedef struct {
    int * buf;
    int head;
    int size;
    int cap;
} int_vector;

void int_init(int_vector *v);
void int_destroy(int_vector *v);
bool int_push_back(int_vector *v, int val);
bool int_push_front(int_vector *v,  int val);
int int_pop_back(int_vector *v);
int int_pop_front(int_vector *v);
bool int_is_empty(int_vector *v);
int int_get_size(int_vector *v);
bool int_set_size(int_vector *v, int new_size);
int int_get_el(int_vector *v, int index);
void int_set_el(int_vector *v, int index, int val);