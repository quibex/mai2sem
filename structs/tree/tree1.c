#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>


typedef struct node node;

typedef node* tree;

struct node{
    double val;
    node* left;
    node* rigth;
};

typedef struct{
    tree new_t;
    double rm_val;
}rm_min_res;


bool is_empty(tree t){
    return (t == NULL);
}

tree empty_tree(){
    return NULL;
}

tree build_tree(double val, tree l, tree r){
    node *t = malloc(sizeof(node));
    t->val = val;
    t->left = l;
    t->rigth = r;
    return t;
}

void destroy_root(tree t){
    t = NULL;
}

double root_val(tree t){
    return t->val;
}

tree left(tree t){
    return t->left;
}

tree rigth(tree t){
    return t->rigth;
}

tree find(tree t, double val){
    if (is_empty(t)) return t;
    // if (val == t->val){
    //     return t;
    // } else if (val < t->val){
    //     return find(t->left, val);
    // } else {
    //     return find(t->rigth, val);
    // }
    while (t->val != val){
        if (is_empty(t)) return t;
        if (val < t->val){
            t = t->left;
        } else {
            t = t->rigth;
        }
    }
    return t;
}

tree add(tree t, double val){
    if (is_empty(t)) return build_tree(val, empty_tree(), empty_tree());
    if (val < t->val){
        tree new_left = add(t->left, val);
        tree new_right = t->rigth;
        double new_val = t->val;
        destroy_root(t);
        return build_tree(new_val, new_left, new_right);
    } else if (val > t->val) {
        tree new_left = t->left;
        tree new_right = add(t->rigth, val);
        double new_val = t->val;
        destroy_root(t);
        return build_tree(new_val, new_left, new_right);
    } else {
        return t;
    }
}

rm_min_res rm_min(tree t){
    rm_min_res res;
    // if (is_empty(t)) return t;
    // if (val < t->val){
    //     tree new_left = delete(t->left, val);
    //     tree new_right = t->rigth;
    //     double new_val = t->val;
    //     destroy_root(t);
    //     return build_tree(new_val, new_left, new_right);
    // } else if (val > t->val){
    //     tree new_left = t->rigth;
    //     tree new_right = delete(t->rigth, val);
    //     double new_val = t->val;
    //     destroy_root(t);
    //     return build_tree(new_val, new_left, new_right);
    // }
    return res;
}

tree delete(tree t, double val){
    if (is_empty(t)) return t;
    if (val < t->val){
        tree new_left = delete(t->left, val);
        tree new_right = t->rigth;
        double new_val = t->val;
        destroy_root(t);
        return build_tree(new_val, new_left, new_right);
    } else if (val > t->val){
        tree new_left = t->rigth;
        tree new_right = delete(t->rigth, val);
        double new_val = t->val;
        destroy_root(t);
        return build_tree(new_val, new_left, new_right);
    } else {
        if (is_empty(t->left) && is_empty(t->rigth)){
            destroy_root(t);
            return empty_tree();
        } else if (is_empty(t->left)){
            tree new_right = t->rigth;
            destroy_root(t);
            return new_right;
        } else if (is_empty(t->rigth)){
            tree new_left = t->left;
            destroy_root(t);
            return new_left;
        } else {
            rm_min_res r = rm_min(t->rigth);
            tree new_left = t->left;
            destroy_root(t);
            return build_tree(r.rm_val, new_left, r.new_t);
        }
    }
}

int main(){
    int n;
    scanf("%d", &n);
    tree t = empty_tree();
    for (int i = 0; i< n; i++){
        double val;
        scanf("%lf", &val);
        t = add(t, val);
    }
    double val;
    while (scanf("%lf", &val) == 1){
        if (find(t, val) != NULL){
            return printf("%lf - Da\n", val);
        } else {
            printf("%lf - Net\n", val);
        }
    }
}





