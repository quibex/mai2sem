#include <stdbool.h>
#include <malloc.h>
#include "vector_mx.h"

#define MIN_CAP 5

void mx_init(mx_vector *v){
    v->size = 0;
    v->head = 0;
    v->cap = MIN_CAP;
    v->buf = malloc(sizeof(dbl_mx_el) * v->cap);

}

void mx_destroy(mx_vector *v){
    v->size = 0;
    free(v->buf);
}

dbl_mx_el mx_get_el(mx_vector *v, int idx){
    return v->buf[(idx + v->head) % v->cap];
}

dbl_mx_el mx_get_front_el(mx_vector *v){
    dbl_mx_el res = v->buf[v->head];
    v->head = (v->head+1)%v->cap;
    return res;
}

dbl_mx_el mx_get_back_el(mx_vector *v){
    return v->buf[(v->head+v->size-1)%v->cap];
}

void mx_set_el(mx_vector *v, int idx, dbl_mx_el val){
    v->buf[(idx + v->head) % v->cap ] = val;
}

static bool increase(mx_vector *v){
    int new_cap = 2 * v->cap;
    dbl_mx_el *tmp = realloc(v->buf, new_cap * sizeof(dbl_mx_el));
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
    return true;
}

static void decrease_if_possible(mx_vector *v){
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
        dbl_mx_el *tmp = realloc(v->buf, new_cap * sizeof(dbl_mx_el));
        v->buf = tmp;
        v->cap = new_cap;
    }
}


bool mx_push_back(mx_vector *v, dbl_mx_el val){
    if (v->size == v->cap){
        if(!increase(v)) return false;
    }
    v->buf[(v->size + v->head)%v->cap] = val;
    v->size++;
    return true;
}

bool mx_push_front(mx_vector *v,  dbl_mx_el val){
    if (v->size == v->cap){
        if(!increase(v)) return false;
    }
    v->buf[(v->head-1+v->cap)%v->cap] = val;
    v->head = (v->head-1+v->cap)%v->cap;
    v->size++;
    return true;

}

dbl_mx_el mx_pop_back(mx_vector *v){
    dbl_mx_el res = v->buf[(v->head+v->size-1)%v->cap];
    v->size--;
    decrease_if_possible(v);
    return res;
}

dbl_mx_el mx_pop_front(mx_vector *v){
    dbl_mx_el res = v->buf[v->head];
    v->head = (v->head+1)%v->cap;
    v->size--;
    decrease_if_possible(v);
    return res; 
}

bool mx_is_empty(mx_vector *v){
    if (v->size == 0){
        return true;
    }
    return false;
}

int mx_get_size(mx_vector *v){
    return v->size;
}

bool mx_set_size(mx_vector *v, int new_size){
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
    dbl_mx_el *tmp = realloc(v->buf, new_cap * sizeof(dbl_mx_el));
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

