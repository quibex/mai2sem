#pragma once
#include <stdbool.h>

typedef struct {
    int count;
    double *buf;
    int cap;
} dbl_stack;

bool ds_push(dbl_stack *s, double val);

