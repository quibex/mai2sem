
enum pass_state{
    START,
    LEFT_VISIT,
    RIGHT_VISIT
};

typedef struct{
    tree* right;
    tree* left;
} tree;


void pass(tree root)
{
    pass_stack s;
    stack_init(&s);
    if (root) stack_push(&s, {.t=root, .state=START});
    while (!stack_empty(&s))
    {
        node_pass n = stack_pop(&s);
        if 
    }
    
}