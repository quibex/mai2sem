#pragma once
#include <stdbool.h> 
#include "lexeme.h"

typedef struct {
    lexeme *buf;
    int head;
    int size;
    int cap;
} lexeme_que;

void lexeme_que_init(lexeme_que *v);
void lexeme_que_destroy(lexeme_que *v); 
bool lexeme_que_push(lexeme_que *v, lexeme val);
lexeme lexeme_que_pop(lexeme_que *v);
bool lexeme_que_is_empty(lexeme_que *v);
int lexeme_que_get_size(lexeme_que *v);
lexeme lexeme_que_top(lexeme_que *v);