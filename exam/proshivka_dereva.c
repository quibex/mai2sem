#include <stdbool.h>
#include <stdio.h>

#define NULL (void *)0

typedef struct {
    tree* left;
    tree* right;
    double val;
    bool left_sewed;
    bool right_sewed;
} tree;

void pass_sewed(tree* root){
    tree* cur = root;
    bool by_sewed = false;
    while (cur != NULL)
    {
        if ((!cur->left_sewed) && (cur->left != NULL) && (!by_sewed))
        {
            cur = cur->left;
            by_sewed = false;
        }
        else 
        {
            printf("%lf ", cur->val);
            by_sewed = cur->right_sewed;
            cur = cur->right;
        }
    }
}

void sew(tree* t)
{
    sew_right(t, NULL);
    sew_left(t, NULL);
}

void sew_right(tree* t, tree* next)
{
    if ( t == NULL) return;
    if (( t->left != NULL) && (!t->left_sewed))
    {
        sew_right(t->left, t);
    }
    if ((t->right == NULL) || (t->right_sewed)){
        t->right = next;
        t->right_sewed = true;
    }
    else 
    {
        sew_right(t->right, next);
    }
}

void sew_left(tree* t, tree* next)
{
    if ( t == NULL) return;
    if (( t->right != NULL) && (!t->right_sewed))
    {
        sew_left(t->right, t);
    }
    if ((t->left == NULL) || (t->left_sewed)){
        t->left = next;
        t->left_sewed = true;
    }
    else 
    {
        sew_left(t->left, next);
    }
}