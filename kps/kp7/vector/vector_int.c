#include <stdbool.h>
#include <malloc.h>
#include "vector_int.h"

#define MIN_CAP 5

void int_init(int_vector *v){
    v->size = 0;
    v->head = 0;
    v->cap = MIN_CAP;
    v->buf = malloc(sizeof(int) * v->cap);
}

void int_destroy(int_vector *v){
    v->size = 0;
    free(v->buf);
}

int int_get_el(int_vector *v, int idx){
    return v->buf[(idx + v->head) % v->cap];
}

void int_set_el(int_vector *v, int idx, int val){
    v->buf[(idx + v->head) % v->cap ] = val;
}

void static zero_range(int_vector *v, int f, int t){
    for (int i = f; i < t; i++){
        int_set_el(v, i, 0);
    }
}

static bool increase(int_vector *v){
    int new_cap = 2 * v->cap;
    int *tmp = realloc(v->buf, new_cap * sizeof(int));
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

static void decrease_if_possible(int_vector *v){
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
        int *tmp = realloc(v->buf, new_cap * sizeof(int));
        v->buf = tmp;
        v->cap = new_cap;
    }
}


bool int_push_back(int_vector *v, int val){
    if (v->size == v->cap){
        if(!increase(v)) return false;
    }
    v->buf[(v->size + v->head)%v->cap] = val;
    v->size++;
    return true;
}

bool int_push_front(int_vector *v,  int val){
    if (v->size == v->cap){
        if(!increase(v)) return false;
    }
    v->buf[(v->head-1+v->cap)%v->cap] = val;
    v->head = (v->head-1+v->cap)%v->cap;
    v->size++;
    return true;

}

int int_pop_back(int_vector *v){
    int res = v->buf[(v->head+v->size-1)%v->cap];
    v->size--;
    decrease_if_possible(v);
    return res;
}

int int_pop_front(int_vector *v){
    int res = v->buf[v->head];
    v->head = (v->head+1)%v->cap;
    v->size--;
    decrease_if_possible(v);
    return res; 
}

bool int_is_empty(int_vector *v){
    if (v->size == 0){
        return true;
    }
    return false;
}

int int_get_size(int_vector *v){
    return v->size;
}

bool int_set_size(int_vector *v, int new_size){
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
    int *tmp = realloc(v->buf, new_cap * sizeof(int));
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