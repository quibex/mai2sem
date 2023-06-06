//

#include <stdbool.h>
#include <stdio.h>
#include <malloc.h>
#include "tree2.h"
#include "tree_queue.h"
#include "vector_int.h"


int depth(tree t){
    if (t == NULL) return 0;
    return 1+max(depth(t->left), depth(t->left));
}

int max_el(int_vector v){
    int max_el = 0;
    for (int i = 0; i < int_get_size(&v); i++){
        if (int_get_el(&v, i) > max_el) max_el = int_get_el(&v, i);
    }
    return max_el;
}

// int depth2(tree t){
//     if (t == NULL) return 0;
//     return max(depth(t->bro), 1+depth(t->child));
// }

void print_sorted_nodes(tree t){
    if (t == NULL) return;
    print_sorted_nodes(t->left);
    printf("%lf", t->val);
    print_sorted_nodes(t->right);
}

void draw_tree(tree t){
    draw_tree_iternal(t, 0);
}

static void draw_tree_iternal(tree t, int depth){ // обход в глубину
    if (t == NULL) return;
    draw_tree_iternal(t->right, depth+1);
    for (int i = 0; i < depth; i++){
        printf(" ");
    }
    printf("%lf\n", t->val);
    draw_tree_iternal(t->left, depth+1);
}

void bfs(tree t){
    if (t == NULL) return;
    tree_queue  q;
    q_init(&q);
    q_push_back(&q, t);
    while(!q_is_empty(&q)){
        tree cur_tree = q_pop_front(&q);
        printf("%lf ", cur_tree->val);
        if (cur_tree->left != NULL){
            q_push_back(&q, cur_tree->left);
        } 
        if (cur_tree->right != NULL){
            q_push_back(&q, cur_tree->right);
        } 
    }
}

int width(tree t){
    int_vector c_w;
    int_init(&c_w);
    int dep = depth(t);
    int_set_size(&c_w, dep);
    width_rec(t, &c_w, dep);
    int max_width = max_el(c_w);
    int_destroy(&c_w);
    return max_width;
}


static void width_rec(tree t, int_vector* vec, int depth){
    if (t == NULL) return;
    int_set_el(vec, depth, int_get_el(&vec, depth)+1);
    width_rec(t->left, vec, depth+1);
    width_rec(t->right, vec, depth+1);
}