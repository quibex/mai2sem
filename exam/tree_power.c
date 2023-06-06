#define NULL (void*)0 

typedef struct tree tree;
struct tree
{
    tree *child;
    tree *bro;
    int val;
};

int tree_power(tree* t)
{
    if ((t = NULL) || (t->child == NULL)){
        return 0;
    }
    int cur_pow = 0, max_child_pow = 0;
    tree *tmp = t->child;
    while (tmp != NULL)
    {
        cur_pow++;
        int child_pow = tree_power(tmp);
        if (max_child_pow < child_pow) max_child_pow = child_pow;
        tmp = t->bro;
    }
    return max(cur_pow, max_child_pow);
}