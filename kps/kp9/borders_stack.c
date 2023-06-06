#include <stdbool.h>
#include <malloc.h>
#include "borders_stack.h"

#define MIN_CAP 5 // > 0

void borders_stack_init(borders_stack *v){
    v->size = 0;
    v->head = 0;    
    v->cap = MIN_CAP;
    v->buf = malloc(sizeof(borders) * v->cap);
}

void borders_stack_destroy(borders_stack *v){
    free(v->buf);
    v->buf = NULL;
    v->head = 0;
    v->size = 0;
    v->cap = 0;
}

static bool increase(borders_stack *v){
    
    int new_cap = 2 * v->cap;
    borders* tmp = realloc(v->buf, new_cap * sizeof(borders));
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

static void decrease_if_possible(borders_stack *v){
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
        borders *tmp = realloc(v->buf, new_cap * sizeof(borders));
        v->buf = tmp;
        v->cap = new_cap;
    }
}


bool borders_stack_push(borders_stack *v, borders val){
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

borders borders_stack_pop(borders_stack *v){
    borders res = v->buf[(v->head+v->size-1)%v->cap];
    v->size--;
    decrease_if_possible(v);
    return res;
}

bool borders_stack_is_empty(borders_stack *v){
    if (v->size == 0){
        return true;
    }
    return false;
}

int borders_stack_get_size(borders_stack *v){
    return v->size;
}

borders borders_stack_top(borders_stack *v){
    return v->buf[(v->head+v->size-1)%v->cap];
}


