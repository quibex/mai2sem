#include <malloc.h>
#include "tree_exp.h"
#include "lexeme_que.h"
#include "lexeme_stack.h"
#include "bin_node_stack.h"


static void print_lexeme(lexeme lex)
{
    if (lex.type == LEX_BR_L) printf("(\n");
    if (lex.type == LEX_BR_R) printf(")\n");
    if (lex.type == LEX_OPER) printf("%c\n", lex.oper);
    if (lex.type == LEX_CONST) printf("%.2lf\n", lex.cnst);
    if (lex.type == LEX_VAR_NAME) printf("%c\n", lex.var_name);
    if (lex.type == LEX_NONE) printf("aboba\n");
}

static bin_node* create_lexeme_bin_node(lexeme lex)
{
    bin_node* new_bin_node = malloc(sizeof(bin_node));
    new_bin_node->val = lex;
    new_bin_node->left = NULL;
    new_bin_node->right = NULL;
    return new_bin_node;
}

static bin_tree build_bin_op_bin_tree(bin_node* op, bin_node* a, bin_node* b){
    op->left = a;
    op->right = b;
    return op;
}

static bin_tree build_un_op_bin_tree(bin_node* op, bin_node* a){
    op->left = a;
    return op;
}

bin_tree build_exp_bin_tree(lexeme_que* exp){
    bin_node_stack stack;
    bin_node_stack_init(&stack);

    while (!lexeme_que_is_empty(exp)){
        lexeme cur_lex = lexeme_que_pop(exp);
        if ((cur_lex.type == LEX_CONST) || (cur_lex.type == LEX_VAR_NAME))
        {
            bin_node* bin_node_lex = create_lexeme_bin_node(cur_lex);
            bin_node_stack_push(&stack, bin_node_lex);
        } 
        else if (cur_lex.type == LEX_OPER)
        {
            if (cur_lex.oper == '~')
            {
                bin_tree bin_tree_op = create_lexeme_bin_node(cur_lex);
                bin_node* a = bin_node_stack_pop(&stack);
                bin_tree_op = build_un_op_bin_tree(bin_tree_op, a);
                bin_node_stack_push(&stack, bin_tree_op);
            }
            else 
            {
                bin_tree bin_tree_op = create_lexeme_bin_node(cur_lex);
                bin_node* b = bin_node_stack_pop(&stack);
                bin_node* a = bin_node_stack_pop(&stack);
                bin_tree_op = build_bin_op_bin_tree(bin_tree_op, a, b);
                bin_node_stack_push(&stack, bin_tree_op);
            }
        }
    }
    bin_tree exp_bin_tree = bin_node_stack_pop(&stack);
    if (!bin_node_stack_is_empty(&stack)) return NULL;
    return exp_bin_tree;
}



static void draw_bin_tree_internal(bin_tree t, int depth){ // обход в глубину
    if (t == NULL) return;
    draw_bin_tree_internal(t->right, depth+1);
    for (int i = 0; i < depth; i++){
        printf("  ");
    }
    print_lexeme(t->val);
    draw_bin_tree_internal(t->left, depth+1);
}

void draw_bin_tree(bin_tree t){
    draw_bin_tree_internal(t, 0);
}

void destroy_bin_tree(bin_tree t){
    if (t == NULL){
        return;
    }
    if (t->right == NULL && t->right == NULL) {
        free(t);
        t = NULL;
        return;
    }
    destroy_bin_tree(t->left);
    destroy_bin_tree(t->right);
    free(t);
    t = NULL;
    return;
}


