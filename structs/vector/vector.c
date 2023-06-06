#include <stdbool.h>
#include <malloc.h>
#include "vector.h"

#define MIN_CAP 5

void dv_init(dbl_vec *v){
    v->size = MIN_CAP;
    v->buf = malloc(sizeof(double) * (v->size));
}

void dv_destroy(dbl_vec *v){
    v->size = 0;
    free(v->buf);
}

int dv_size(dbl_vec *v){
    return v->size;
}

void dv_resize(dbl_vec *v, int new_size){
    v->size = new_size;
    v->buf = realloc(v->buf, sizeof(double) * (v->size));
}

void dv_put(dbl_vec *v, int index, double val){
    v->buf[index] = val;
}
double dv_get(dbl_vec *v, int index){
    return v->buf[index];
}




