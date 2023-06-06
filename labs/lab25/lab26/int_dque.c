#include <stdbool.h>
#include <malloc.h>
#include "int_dque.h"

#define MIN_CAP 5 // > 0

void int_dque_init(int_dque *v){
    v->size = 0;
    v->head = 0;    
    v->cap = MIN_CAP;
    v->buf = malloc(sizeof(int) * v->cap);
}

void int_dque_destroy(int_dque *v){
    free(v->buf);
    v->buf = NULL;
    v->head = 0;
    v->size = 0;
    v->cap = 0;
}

static bool increase(int_dque *v){
    
    int new_cap = 2 * v->cap;
    int* tmp = realloc(v->buf, new_cap * sizeof(int));
    if (tmp == NULL){
        return false;
    }
    v->buf = tmp; 
    int old_cap = v->cap;
    v->cap = new_cap; 
    if (v->head + v->size > old_cap){
        for (int i = old_cap; i >= v->head; i--){
            v->buf[i+old_cap] = v->buf[i];
        }
        v->head += old_cap;
    }
    return true;
}

static void decrease_if_possible(int_dque *v){
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
        int *tmp = realloc(v->buf, new_cap * sizeof(int));
        v->buf = tmp;
        v->cap = new_cap;
    }
}


bool int_dque_push_back(int_dque *v, int val){
    if (v->size == v->cap){
        if(!increase(v)) {
            return false;
            printf("== false ==\n"); 
        }
    }
    v->buf[(v->size + v->head)%v->cap] = val;
    v->size++;
    return true;
}

bool int_dque_push_front(int_dque *v,  int val){
    if (v->size == v->cap){
        if(!increase(v)) {
            return false;
            printf("== false ==\n"); 
        }
    }
    v->buf[(v->head-1+v->cap)%v->cap] = val;
    v->head = (v->head-1+v->cap)%v->cap;
    v->size++;
    return true;

}

int int_dque_pop_back(int_dque *v){
    int res = v->buf[(v->head+v->size-1)%v->cap];
    v->size--;
    decrease_if_possible(v);
    return res;
}

int int_dque_pop_front(int_dque *v){
    int res = v->buf[v->head];
    v->head = (v->head+1)%v->cap;
    v->size--;
    decrease_if_possible(v);
    return res; 
}

bool int_dque_is_empty(int_dque *v){
    if (v->size == 0){
        return true;
    }
    return false;
}

int int_dque_get_size(int_dque *v){
    return v->size;
}

int int_dque_front(int_dque *v){
    return v->buf[v->head];
}

int int_dque_back(int_dque *v){
    return v->buf[(v->head+v->size-1)%v->cap];
}

int int_dque_get_el(int_dque *v, int idx){
    return v->buf[(idx + v->head) % v->cap];
}



