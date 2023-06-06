//на Си

#include <stdbool.h>
#include <stdio.h>
#include <malloc.h>
#include "tree2.h"
#include "enummaamg.h"


tree* find(tree* t, int val){
    // if (*t == NULL) return t;
    // if (val == (*t)->val) return t;
    // if (val < (*t)->val){
    //     return find(&((*t)->left), val);
    // } else {
    //     return find(&((*t)->right), val);
    // }
    while(1){
        if (*t == NULL) return t;
        if (val == (*t)->val) return t;
        if (val < (*t)->val){
            t = &((*t)->left);
        } else {
            t = &((*t)->right);
        }
    }
}

bool add(tree* t, int val){
    tree* place = find(t, val);
    if (*place != NULL){
        return false;
    }
    tree new_node = malloc(sizeof(node));
    new_node->val = val;
    new_node->left = NULL;
    new_node->right = NULL;
    *place = new_node;
    return true;
}

bool delete(tree* t, int val){
    tree* place = find(t, val);
    if (*place == NULL){ 
        return false;
    }else if ((*place)->left == NULL && (*place)->right == NULL){ 
        free(*place);
        *place = NULL;
    } else if ((*place)->left == NULL){
        tree new_right = (*place)->right;
        free(*place);
        *place = new_right;
    } else if ((*place)->right == NULL){
        tree new_left = (*place)->left;
        free(*place);
        *place = new_left;
    } else {
        tree *r = &((*place)->right);
        while ((*r)->left != NULL){
            r = &((*r)->left);
        }
        tree min_r = (*r);
        *r = (*r)->right;
        min_r->left = (*place)->left;
        min_r->right = (*place)->right;
        free(*place);
        *place = min_r;
    }
    return true;
}


static void draw_tree_internal(tree t, int depth){ // обход в глубину
    if (t == NULL) return;
    draw_tree_internal(t->right, depth+1);
    for (int i = 0; i < depth; i++){
        printf("\t");
    }
    char* company = get_company_name(t->val);
    printf("%s\n", company);
    draw_tree_internal(t->left, depth+1);
}

void draw_tree(tree t){
    draw_tree_internal(t, 0);
}

int count_leaves(tree root) {
    if (root == NULL) {
        return 0;
    }
    if (root->left == NULL && root->right == NULL) {
        return 1;
    }
    return count_leaves(root->left) + count_leaves(root->right);
}


void destroy(tree* t){
    if ((*t) == NULL){
        return;
    }
    if ((*t)->right == NULL && (*t)->right == NULL) {
        free(*t);
        *t = NULL;
        return;
    }
    destroy(&(*t)->left);
    destroy(&(*t)->right);
    free(*t);
    *t = NULL;
    return;
}


// Тестировние: 
// int main(){
//     tree root = NULL;
//     int n;
//     int val;
//     scanf("%d", &n);
//     for (int i = 0; i < n; i++){
//         scanf("%lf", &val);
//         bool added = add(&root, val);
//         printf(added? "Добавляет\n":"Не добавляет\n");
//     }
//     for (int i = 0; i < n; i++){
//         scanf("%lf", &val);
//         bool added = delete(&root, val);
//         printf(added? "Удаляет\n":"Не удаляет\n");
//     }
// }