#pragma once
#include <stdbool.h>

typedef struct {
    int L;
    int R;
} borders;

typedef struct {
    borders *buf;
    int head;
    int size;
    int cap;
} borders_stack;

void borders_stack_init(borders_stack *v);
void borders_stack_destroy(borders_stack *v); 
bool borders_stack_push(borders_stack *v, borders val);
borders borders_stack_pop(borders_stack *v);
bool borders_stack_is_empty(borders_stack *v);
int borders_stack_get_size(borders_stack *v);
borders borders_stack_top(borders_stack *v);