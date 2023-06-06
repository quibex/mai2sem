#pragma once
#include <stdbool.h> 
#include "lexeme.h"

typedef struct {
    lexeme *buf;
    int head;
    int size;
    int cap;
} lexeme_stack;

void lexeme_stack_init(lexeme_stack *v);
void lexeme_stack_destroy(lexeme_stack *v); 
bool lexeme_stack_push(lexeme_stack *v, lexeme val);
lexeme lexeme_stack_pop(lexeme_stack *v);
bool lexeme_stack_is_empty(lexeme_stack *v);
int lexeme_stack_get_size(lexeme_stack *v);
lexeme lexeme_stack_top(lexeme_stack *v);