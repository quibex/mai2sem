#pragma once 
#include <stdbool.h>
#include "vector/vector_dbl.h"
#include "vector/vector_int.h"
#include "vector/vector_mx.h"

typedef struct {
    int n, m;
    int_vector row;
    mx_vector elems;
} matrix;

typedef struct {
    double val;
    int prev_clmn_max_el;
    int clmn;
    int row;
} max_el_mx;

matrix read_mtx();
void print_mtx_user(matrix *mx);
void print_mtx_private(matrix *mx);
void kp7_var2(matrix *mx);
max_el_mx get_max_el(matrix *mx);
