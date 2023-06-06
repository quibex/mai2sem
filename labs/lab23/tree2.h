#pragma once

typedef struct node node;

typedef node* tree;

struct node{
    int val;
    node* left;
    node* right;
};

tree* find(tree* t, int val);
bool add(tree* t, int val);
bool delete(tree* t, int val);
void destroy(tree* t);
void draw_tree(tree t);
int count_leaves(tree root);