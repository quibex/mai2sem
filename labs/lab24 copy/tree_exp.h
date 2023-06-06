#pragma once 
#include "lexeme.h"
#include "lexeme_que.h"

typedef struct bin_node bin_node;

typedef bin_node* bin_tree;

struct bin_node{
    lexeme val;
    bin_node* left;
    bin_node* right;
};

bin_tree build_exp_bin_tree(lexeme_que* exp);
bool dijkstra_sort_station(lexeme_que *in, lexeme_que *out);
void destroy_bin_tree(bin_tree t);
void draw_bin_tree(bin_tree t);