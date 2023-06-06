#include <stdio.h>
#include <stdbool.h>
#include "lexeme.h"
#include "lexeme_que.h"
#include "lexeme_stack.h"


static void print_lexeme(lexeme lex)
{
    if (lex.type == LEX_BR_L) printf("( ");
    if (lex.type == LEX_BR_R) printf(") ");
    if (lex.type == LEX_OPER) printf("%c ", lex.oper);
    if (lex.type == LEX_CONST) printf("%.2lf ", lex.cnst);
    if (lex.type == LEX_VAR_NAME) printf("%c ", lex.var_name);
    if (lex.type == LEX_NONE) printf("aboba ");
}

bool is_operator(char letter)
{
    return (letter == '*' || letter == '/' || letter == '+' || letter == '-' || letter == '~' || letter == '^');
}

LEX_READ_RESULT read_lexeme(LEXTYPE prev_type, lexeme *out)
{
    int letter;
    while ((letter = getchar()) == ' ')
    {
    };
    if (letter >= '0' && letter <= '9')
    {
        ungetc(letter, stdin);
        double num;
        scanf("%lf", &num);
        out->type = LEX_CONST;
        out->cnst = num;
        return LEX_READ_OK;
    }
    else if (letter == '(')
    {
        out->type = LEX_BR_L;
        return LEX_READ_OK;
    }
    else if (letter == ')')
    {
        out->type = LEX_BR_R;
        return LEX_READ_OK;
    }
    else if ((letter == 'x') || (letter == 'X'))
    {
        out->var_name = letter;
        out->type = LEX_VAR_NAME;
        return LEX_READ_OK;
    }
    else if (is_operator(letter))
    {
        if (letter == '-')
        {
            if (prev_type == LEX_NONE || prev_type == LEX_BR_L || prev_type == LEX_OPER)
            {
                out->oper = '~';
                out->oper_priority = high;
                out->oper_assoc = right;
            }
            else
            {
                out->oper = '-';
                out->oper_priority = low;
                out->oper_assoc = left;
            }
        }
        else
        {
            out->oper = letter;
            if (letter == '-' || letter == '+')
            {
                out->oper_priority = low;
                out->oper_assoc = left;
            }
            else if (letter == '*' || letter == '/')
            {
                out->oper_priority = middle;
                out->oper_assoc = left;
            }
            else if (letter == '^')
            {
                out->oper_priority = high;
                out->oper_assoc = right;
            }
        }
        out->type = LEX_OPER;
        return LEX_READ_OK;
    }
    else if (letter == '\n' || letter == EOF)
    {
        out->type = LEX_NONE;
        return LEX_READ_END;
    }
    else
    {
        out->type = LEX_NONE;
        return LEX_READ_ERROR;
    }
}

EXPR_READ_RESULT read_expr(lexeme_que *out)
{
    lexeme cur_lex;
    LEXTYPE prev_lex_type = LEX_NONE;
    LEX_READ_RESULT read_res;
    while ((read_res = read_lexeme(prev_lex_type, &cur_lex)) == LEX_READ_OK)
    {
        lexeme_que_push(out, cur_lex);
        prev_lex_type = cur_lex.type;
    }
    if (read_res == LEX_READ_ERROR)
    {
        return EXPR_READ_ERROR;
    }
    else
    {
        return EXPR_READ_OK;
    }
}

bool dijkstra_sort_station(lexeme_que *in, lexeme_que *out)
{
    lexeme_stack operations;
    lexeme_stack_init(&operations);
    while (!lexeme_que_is_empty(in)) // and no error
    { 
        lexeme cur_lex = lexeme_que_pop(in);
        if ((cur_lex.type == LEX_CONST) || (cur_lex.type == LEX_VAR_NAME))
        {
            lexeme_que_push(out, cur_lex);
        }
        else if (cur_lex.type == LEX_BR_L)
        {
            lexeme_stack_push(&operations, cur_lex);
        }
        else if (cur_lex.type == LEX_OPER)
        {
            lexeme top_stack = lexeme_stack_top(&operations);
            while ((top_stack.type == LEX_OPER) && 
                !lexeme_stack_is_empty(&operations)) 
            {
                if (((top_stack.oper_priority >= cur_lex.oper_priority) && (cur_lex.oper_assoc == left))
                    || ((top_stack.oper_priority > cur_lex.oper_priority) && (cur_lex.oper_assoc == right))) 
                {
                    lexeme_que_push(out, lexeme_stack_pop(&operations));
                    top_stack = lexeme_stack_top(&operations);
                } else 
                {
                    break;
                }
            }
            lexeme_stack_push(&operations, cur_lex);
        }
        else if (cur_lex.type == LEX_BR_R)
        {
            lexeme top_stack = lexeme_stack_top(&operations);
            while (top_stack.type != LEX_BR_L) 
            {
                lexeme_que_push(out, lexeme_stack_pop(&operations));
                top_stack = lexeme_stack_top(&operations);
                if (lexeme_stack_is_empty(&operations)) 
                {
                    lexeme_stack_destroy(&operations);
                    return false;  // brackets are entered incorrectly
                }
            }
            lexeme_stack_pop(&operations);
        }
    }
    while (!lexeme_stack_is_empty(&operations))
    {
        lexeme_que_push(out, lexeme_stack_pop(&operations));
    }
    lexeme_stack_destroy(&operations);
    return true;
}

void lexeme_que_print(lexeme_que* exp)
{
    int que_size = lexeme_que_get_size(exp);
    for (int i = 0; i < que_size; i++)
    {
        lexeme cur_lex = lexeme_que_pop(exp);
        print_lexeme(cur_lex);
        lexeme_que_push(exp, cur_lex);
    }
    putchar('\n');
}

