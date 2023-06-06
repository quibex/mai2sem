#pragma once
#include <stdbool.h> 
#include "tree2.h" 


typedef struct {
    tree* buf;
    int head;
    int size;
    int cap;
} tree_queue;

void q_init(tree_queue *q);
void q_destroy(tree_queue *q);
bool q_push_back(tree_queue *q, tree val);
bool q_push_front(tree_queue *q,  tree val);
tree q_pop_back(tree_queue *q);
tree q_pop_front(tree_queue *q);
bool q_is_empty(tree_queue *q);
int q_get_size(tree_queue *q);
bool q_set_size(tree_queue *q, int new_size);
tree q_get_el(tree_queue *q, int index);
void q_set_el(tree_queue *q, int index, tree val);