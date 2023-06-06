#include <stdbool.h>
#include <malloc.h>
#include "lexeme_que.h"

#define MIN_CAP 5 // > 0

void lexeme_que_init(lexeme_que *v){
    v->size = 0;
    v->head = 0;    
    v->cap = MIN_CAP;
    v->buf = malloc(sizeof(lexeme) * v->cap);
}

void lexeme_que_destroy(lexeme_que *v){
    free(v->buf);
    v->buf = NULL;
    v->head = 0;
    v->size = 0;
    v->cap = 0;
}

static bool increase(lexeme_que *v){
    
    int new_cap = 2 * v->cap;
    lexeme* tmp = realloc(v->buf, new_cap * sizeof(lexeme));
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

static void decrease_if_possible(lexeme_que *v){
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
        lexeme *tmp = realloc(v->buf, new_cap * sizeof(lexeme));
        v->buf = tmp;
        v->cap = new_cap;
    }
}


bool lexeme_que_push(lexeme_que *v, lexeme val){
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

lexeme lexeme_que_pop(lexeme_que *v){
    lexeme res = v->buf[v->head];
    v->head = (v->head+1)%v->cap;
    v->size--;
    decrease_if_possible(v);
    return res; 
}

bool lexeme_que_is_empty(lexeme_que *v){
    if (v->size == 0){
        return true;
    }
    return false;
}

int lexeme_que_get_size(lexeme_que *v){
    return v->size;
}

lexeme lexeme_que_top(lexeme_que *v){
    return v->buf[v->head];
}


