#pragma once
#include <stdbool.h> 

typedef struct {
    int *buf;
    int head;
    int size;
    int cap;
} int_dque;

void int_dque_init(int_dque *v);
void int_dque_destroy(int_dque *v); 
bool int_dque_push_back(int_dque *v, int val);
bool int_dque_push_front(int_dque *v,  int val);
int int_dque_pop_back(int_dque *v);
int int_dque_pop_front(int_dque *v);
bool int_dque_is_empty(int_dque *v);
int int_dque_get_size(int_dque *v);
int int_dque_front(int_dque *v);
int int_dque_back(int_dque *v);
int int_dque_get_el(int_dque *v, int idx);