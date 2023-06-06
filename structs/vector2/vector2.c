#include <stdbool.h>
#include <malloc.h>
#include "vector2.h"

#define MIN_CAP 5

void dbl_init(dbl_vector *v){
    v->size = 0;
    v->head = 0;
    v->cap = MIN_CAP;
    v->buf = malloc(sizeof(double) * v->cap);

}

void dbl_destroy(dbl_vector *v){
    v->size = 0;
    free(v->buf);
}

double dbl_get_el(dbl_vector *v, int idx){
    return v->buf[(idx + v->head) % v->cap];
}

void dbl_set_el(dbl_vector *v, int idx, double val){
    v->buf[(idx + v->head) % v->cap ] = val;
}

void static zero_range(dbl_vector *v, int f, int t){
    for (int i = f; i < t; i++){
        dbl_set_el(v, i, 0);
    }
}

static bool increase(dbl_vector *v){
    int new_cap = 2 * v->cap;
    double *tmp = realloc(v->buf, new_cap * sizeof(double));
    if (tmp == NULL){
        return false;
    }
    v->buf = tmp; 
    int old_cap = v->cap;
    v->cap = new_cap; 
    if (v->head + v->size > v->cap){
        if (v->head > (v->cap / 2)){
            for (int i = v->head; i < old_cap; i++){
                v->buf[new_cap - i] = v->buf[i];
                v->buf[i] = 0;
            }
            v->head = new_cap - v->head;
        } else { 
            for (int i = 0; i < (v->head + v->size) % v->cap; i++){
                v->buf[old_cap + i] = v->buf[i];
                v->buf[i] = 0;
            }
        }
    } else {
        zero_range(v, old_cap, new_cap);
    }
    return true;
}

static void decrease_if_possible(dbl_vector *v){
    if (v->size < v->cap/4){
        int new_cap = v->cap/2;
        if (new_cap < MIN_CAP){
            new_cap = MIN_CAP;
        }
        if (new_cap >= v->cap){
            return ;
        } 
        if ((v->head + v->size) > new_cap){
            if ( v->head > new_cap){
                for (int i = new_cap - (v->cap - v->head); i < new_cap; i++){
                    v->buf[i] = v->buf[i + new_cap];
                }
                v->head = new_cap - (v->cap - v->head);
            } else {
                for (int i = 0; i < v->head; i++){
                    v->buf[i] = v->buf[new_cap + i];
                }  
            }
        } 
        double *tmp = realloc(v->buf, new_cap * sizeof(double));
        v->buf = tmp;
        v->cap = new_cap;
    }
}


bool dbl_push_back(dbl_vector *v, double val){
    if (v->size == v->cap){
        if(!increase(v)) return false;
    }
    v->buf[(v->size + v->head)%v->cap] = val;
    v->size++;
    return true;
}

bool dbl_push_front(dbl_vector *v,  double val){
    if (v->size == v->cap){
        if(!increase(v)) return false;
    }
    v->buf[(v->head-1+v->cap)%v->cap] = val;
    v->head = (v->head-1+v->cap)%v->cap;
    v->size++;
    return true;

}

double dbl_pop_back(dbl_vector *v){
    double res = v->buf[(v->head+v->size-1)%v->cap];
    v->size--;
    decrease_if_possible(v);
    return res;
}

double dbl_pop_front(dbl_vector *v){
    double res = v->buf[v->head];
    v->head = (v->head+1)%v->cap;
    v->size--;
    decrease_if_possible(v);
    return res; 
}

bool dbl_is_empty(dbl_vector *v){
    if (v->size == 0){
        return true;
    }
    return false;
}

int dbl_get_size(dbl_vector *v){
    return v->size;
}

bool dbl_set_size(dbl_vector *v, int new_size){
    if ((new_size >= v->size) && (new_size <= v->cap)){
        v->size = new_size;
        decrease_if_possible(v);
        return true;
    }
    if ((new_size < v->size) && (new_size <= v->cap)) {
        if (v->head == 0) return true;
        else {
            for (int i = 0; i < new_size; i++){
                v->buf[i] = v->buf[v->head + i];
            }
            v->size = new_size;
            decrease_if_possible(v);
            return true;
        }
    }
    int new_cap = new_size;
    double *tmp = realloc(v->buf, new_cap * sizeof(double));
    if (tmp == NULL){
        return false;
    }
    v->buf = tmp;
    if (v->head + v->size > v->cap){
        for (int i = v->cap - 1; i >= v->head; i--){
            v->buf[i + new_cap - v->cap] = v->buf[i];
            v->buf[i] = 0;
        }
        v->head += new_cap - v->cap;
    }
    v->size = new_size;
    v->cap = new_cap;
    return true;
}


