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