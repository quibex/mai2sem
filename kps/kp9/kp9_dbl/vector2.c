#include <stdbool.h>
#include <malloc.h>
#include "vector2.h"

#define MIN_CAP 10

void dbl_vec_init(dbl_vec *v){
    v->size = 0;
    v->head = 0;
    v->cap = MIN_CAP;
    v->buf = malloc(sizeof(elem) * v->cap);

}

void dbl_vec_destroy(dbl_vec *v){
    v->size = 0;
    free(v->buf);
}

elem dbl_vec_get_el(dbl_vec *v, int idx){
    return v->buf[(idx + v->head) % v->cap];
}

void dbl_vec_set_el(dbl_vec *v, int idx, elem val){
    v->buf[(idx + v->head) % v->cap ] = val;
}

static bool increase(dbl_vec *v){
    int new_cap = 2 * v->cap;
    elem *tmp = realloc(v->buf, new_cap * sizeof(elem));
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
            }
            v->head = new_cap - v->head;
        } else { 
            for (int i = 0; i < (v->head + v->size) % v->cap; i++){
                v->buf[old_cap + i] = v->buf[i];
            }
        }
    } 
    // else {
    //     zero_range(v, old_cap, new_cap);
    // }
    return true;
}

static void decrease_if_possible(dbl_vec *v){
    if (v->size < (v->cap/4)){
        int new_cap = v->cap/2;
        if (new_cap < MIN_CAP){
            new_cap = MIN_CAP;
        }
        if (new_cap >= v->cap){
            return ;
        } 
        if ((v->head + v->size) > v->cap){
            for (int i = v->head - new_cap; i < new_cap; i++){
                v->buf[i] = v->buf[i + new_cap];
            }
            v->head = v->head - new_cap;
        } else if (v->head + v->size > new_cap) {
            for (int i = 0; i < v->size; i++){
                v->buf[i] = v->buf[i + v->head];
            }
            v->head = 0;
        }
        elem *tmp = realloc(v->buf, new_cap * sizeof(elem));
        v->buf = tmp;
        v->cap = new_cap;
    }
}


bool dbl_vec_push_back(dbl_vec *v, elem val){
    if (v->size == v->cap){
        if(!increase(v)) return false;
    }
    v->buf[(v->size + v->head)%v->cap] = val;
    v->size++;
    return true;
}

bool dbl_vec_push_front(dbl_vec *v,  elem val){
    if (v->size == v->cap){
        if(!increase(v)) return false;
    }
    v->buf[(v->head-1+v->cap)%v->cap] = val;
    v->head = (v->head-1+v->cap)%v->cap;
    v->size++;
    return true;

}

elem dbl_vec_pop_back(dbl_vec *v){
    elem res = v->buf[(v->head+v->size-1)%v->cap];
    v->size--;
    // decrease_if_possible(v);
    return res;
}

elem dbl_vec_pop_front(dbl_vec *v){
    elem res = v->buf[v->head];
    v->head = (v->head+1)%v->cap;
    v->size--;
    // decrease_if_possible(v);
    return res; 
}

bool dbl_vec_is_empty(dbl_vec *v){
    if (v->size == 0){
        return true;
    }
    return false;
}

int dbl_vec_get_size(dbl_vec *v){
    return v->size;
}

bool dbl_vec_set_size(dbl_vec *v, int new_size){
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
    elem *tmp = realloc(v->buf, new_cap * sizeof(elem));
    if (tmp == NULL){
        return false;
    }
    v->buf = tmp;
    if (v->head + v->size > v->cap){
        for (int i = v->cap - 1; i >= v->head; i--){
            v->buf[i + new_cap - v->cap] = v->buf[i];
        }
        v->head += new_cap - v->cap;
    }
    v->size = new_size;
    v->cap = new_cap;
    return true;
}


elem dbl_vec_head(dbl_vec * v) {
    return v->buf[v->head];
}

elem dbl_vec_tail(dbl_vec * v) {
    return v->buf[(v->head + v->size - 1) % v->cap];
}
