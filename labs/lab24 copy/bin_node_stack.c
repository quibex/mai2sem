#include <stdbool.h>
#include <malloc.h>
#include "lexeme.h"
#include "tree_exp.h"
#include "bin_node_stack.h"

#define MIN_CAP 5 // > 0!

void bin_node_stack_init(bin_node_stack *v){
    v->size = 0;
    v->head = 0;    
    v->cap = MIN_CAP;
    v->buf = malloc(sizeof(bin_node*) * v->cap);
}

void bin_node_stack_destroy(bin_node_stack *v){
    free(v->buf);
    v->buf = NULL;
    v->head = 0;
    v->size = 0;
    v->cap = 0;
}

static bool increase(bin_node_stack *v){
    
    int new_cap = 2 * v->cap;
    bin_node* *tmp = realloc(v->buf, new_cap * sizeof(bin_node*));
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

static void decrease_if_possible(bin_node_stack *v){
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
        
        bin_node* *tmp = realloc(v->buf, new_cap * sizeof(bin_node*));
        v->buf = tmp;
        v->cap = new_cap;
    }
}


bool bin_node_stack_push(bin_node_stack *v, bin_node* el){
    if (v->size == v->cap){
        if(!increase(v)) {
            return false;
            printf("== false ==\n"); 
        }
    }
    v->buf[(v->size + v->head)%v->cap] = el;
    v->size++;
    return true;
}

bin_node* bin_node_stack_pop(bin_node_stack *v){
    bin_node* res = v->buf[(v->head+v->size-1)%v->cap];
    v->size--;
    decrease_if_possible(v);
    return res;
}

bool bin_node_stack_is_empty(bin_node_stack *v){
    if (v->size == 0){
        return true;
    }
    return false;
}

int bin_node_stack_get_size(bin_node_stack *v){
    return v->size;
}

bin_node* bin_node_stack_top(bin_node_stack *v){
    return v->buf[(v->head+v->size-1)%v->cap];
}


