// дерево общего вида

#include <stdbool.h>
#include <stdio.h>
#include <malloc.h>

typedef struct node node;

typedef node* tree;

struct node{
    double val;
    node* child;
    node* bro;
};

bool add(tree t, double val, char* path){
    tree* place = get_node(t, path);
    if (place == NULL) return false;
    tree new_node = malloc(sizeof(node));
    new_node->val = val;
    new_node->child = NULL;
    new_node->bro = (*place);
    *place = new_node;
    return true;
}

tree * get_node(tree* t, char* path){
    while (path[0] != '\0'){
        if (*t == NULL) { // проверка, что такой пути сущ. в дереве 
            return NULL;
        } else if (path[0] == 'c'){
            t = &(*t)->child;
            path += 1;
        } else if (path[0] == 'b') {
            t = &(*t)->bro;
            path += 1;
        } else { // если неправльно указали путь, типо abbccbcbcbabdffsbh
            return NULL;
        }
    }
    return t;
    // if (path[0] == '\0'){
    //     return t;
    // } else if (*t == NULL) { // проверка, что такой пути сущ. в дереве 
    //     return NULL;
    // } else if (path[0] == 'c') {
    //     return get_node(&(*t)->child, path+1);
    // } else if (path[0] == 'b') {
    //     return get_node(&(*t)->bro, path+1);
    // } else { // если неправльно указали путь, типо abbccbcbcbabdffsbh
    //     return NULL;
    // } 
}