#pragma once
#include <stdbool.h> 
#include "lexeme.h"

typedef struct {
    bin_node* *buf;
    int head;
    int size;
    int cap;
} bin_node_stack;

void bin_node_stack_init(bin_node_stack *v);
void bin_node_stack_destroy(bin_node_stack *v); 
bool bin_node_stack_push(bin_node_stack *v, bin_node* val);
bin_node* bin_node_stack_pop(bin_node_stack *v);
bool bin_node_stack_is_empty(bin_node_stack *v);
int bin_node_stack_get_size(bin_node_stack *v);
bin_node* bin_node_stack_top(bin_node_stack *v);