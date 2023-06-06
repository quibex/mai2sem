#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "lexeme.h"
#include "lexeme_que.h"
#include "lexeme_stack.h" 
#include "tree_exp.h" 

LEX_READ_RESULT read_lexeme(LEXTYPE prev_type, lexeme *out);
EXPR_READ_RESULT read_expr(lexeme_que *out);
void lexeme_que_print(lexeme_que* que);


double calculate_exp_by_x(bin_tree exp_tree, double x)
{   
    if ((exp_tree->left == NULL) && (exp_tree->right == NULL))
    {
        if (exp_tree->val.type == LEX_CONST) return exp_tree->val.cnst;
        if ((exp_tree->val.type == LEX_VAR_NAME)) return x;
        else printf("\n##aboba##\n");
    }
    if (exp_tree->val.type == LEX_OPER)
    {
        if (exp_tree->val.oper == '~') 
            return -(calculate_exp_by_x(exp_tree->left, x));
        
        if (exp_tree->val.oper == '+') 
            return (calculate_exp_by_x(exp_tree->left, x) + calculate_exp_by_x(exp_tree->right, x));
        
        if (exp_tree->val.oper == '-') 
            return (calculate_exp_by_x(exp_tree->left, x) - calculate_exp_by_x(exp_tree->right, x));
        
        if (exp_tree->val.oper == '*') 
            return (calculate_exp_by_x(exp_tree->left, x) * calculate_exp_by_x(exp_tree->right, x));
        
        if (exp_tree->val.oper == '/') 
            return (calculate_exp_by_x(exp_tree->left, x) / calculate_exp_by_x(exp_tree->right, x));
        
        if (exp_tree->val.oper == '^') 
            return pow(calculate_exp_by_x(exp_tree->left, x), calculate_exp_by_x(exp_tree->right, x));
    }
    
}

int main()
{
    lexeme_que in;
    lexeme_que_init(&in);

    printf("Enter polynomial of x: ");
    EXPR_READ_RESULT read_res = read_expr(&in);
    if (read_res == EXPR_READ_ERROR)
    {
        printf("invalid input\n");
        return 1;
    }

    lexeme_que out;
    lexeme_que_init(&out);

    dijkstra_sort_station(&in, &out);
    printf("#Reverse Polish Notation:\n");
    printf("-------------------------------------------------------------------\n");
    lexeme_que_print(&out);
    printf("-------------------------------------------------------------------\n");
   
    bin_tree exp_tree = build_exp_bin_tree(&out);
    printf("#Binary expression tree:\n");
    printf("-------------------------------------------------------------------\n");
    draw_bin_tree(exp_tree);
    printf("-------------------------------------------------------------------\n");
    
    printf("Enter the x value: ");
    double x = 0;
    scanf("%lf", &x);
    double result_exp = calculate_exp_by_x(exp_tree, x);
    printf("#Result: %.2lf\n", result_exp);

    destroy_bin_tree(exp_tree);
    lexeme_que_destroy(&in);
    lexeme_que_destroy(&out);
    return 0;
}