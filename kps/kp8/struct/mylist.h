#pragma once 

typedef struct node node;

struct node {
    unsigned int val;
    node *next;
    node *prev;
};

typedef struct {
    node *terminator;
    node *last;
    int len;
} list;

void init(list *list);
void print_list(list *list);
void insert(list *list, unsigned int val);
void delete_by_val(list *list, unsigned int val);
void delete_node(node* node);
int length(list *list);
void delete_range(list *list, unsigned int min, unsigned int max);
void destroy(list *list);