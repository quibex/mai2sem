//на Си

#include <stdbool.h>
#include <stdio.h>
#include <malloc.h>

typedef struct node node;

typedef node* tree;

struct node{
    double val;
    node* left;
    node* rigth;
};

tree* find(tree* t, double val){
    // if (*t == NULL) return t;
    // if (val == (*t)->val) return t;
    // if (val < (*t)->val){
    //     return find(&((*t)->left), val);
    // } else {
    //     return find(&((*t)->rigth), val);
    // }
    while(1){
        if (*t == NULL) return t;
        if (val == (*t)->val) return t;
        if (val < (*t)->val){
            t = &((*t)->left);
        } else {
            t = &((*t)->rigth);
        }
    }
}

bool add(tree* t, double val){
    tree* place = find(t, val);
    if (*place != NULL){
        return false;
    }
    tree new_node = malloc(sizeof(node));
    new_node->val = val;
    new_node->left = NULL;
    new_node->rigth = NULL;
    *place = new_node;
    return true;
}

bool delete(tree* t, double val){
    tree* place = find(t, val);
    if (*place == NULL){
        return false;
    } 
    if ((*t)->left == NULL && (*t)->rigth == NULL){
        free(*place);
        *place = NULL;
    } else if ((*t)->left == NULL){
        tree new_right = (*place)->rigth;
        free(*place);
        *place = new_right;
    } else if ((*t)->rigth == NULL){
        tree new_left = (*place)->left;
        free(*place);
        *place = new_left;
    } else {
        tree *r = &((*place)->rigth);
        while ((*r)->left != NULL){
            r = &((*r)->left);
        }
        tree min_r = (*r);
        *r = (*r)->rigth;
        min_r->left = (*place)->left;
        min_r->rigth = (*place)->rigth;
        free(*place);
        *place = min_r;
    }
    return true;
}

int main(){
    tree root = NULL;
    int n;
    double val;
    scanf("%d", &n);
    for (int i = 0; i < n; i++){
        scanf("%lf", &val);
        bool added = add(&root, val);
        printf(added? "Добавляет\n":"Не добавляет\n");
    }
}