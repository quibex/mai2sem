#include <stdio.h>
#include <stdbool.h>
#include "lesson.h"
#include "lexeme_queue.h"
#include "lexeme_stack.h"

LEX_READ_RESULT read_lex(LEXTYPE prev_type, lexeme *out);
EXPR_READ_RESULT read_expr(lex_queue *out);
// lex_queue postfix_to_infix(lex_queue *in);
bool Dijkstra_sort_station(lex_queue *in, lex_queue *out);

int main()
{
    lex_queue in;
    lex_queue_init(&in);
    read_expr(&in);

    lex_queue output;
    lex_queue_init(&output);
    // printf("-----------------------------\n");
    // lex_queue_show_queue(&in);
    Dijkstra_sort_station(&in, &output);
    printf("-----------------------------\n");
    lex_queue_show_queue(&output);
    printf("-----------------------------\n");
    // printf("Size: %d\n", lex_queue_get_size(&exp));

    return 0;
}

bool is_operator(char letter)
{
    return (letter == '*' || letter == '/' || letter == '+' || letter == '-' || letter == '~' || letter == '^');
}

LEX_READ_RESULT read_lex(LEXTYPE prev_type, lexeme *out)
{
    int letter;
    while ((letter = getchar()) == ' '){};
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
    else if ((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z') || letter == '_')
    {
        ungetc(letter, stdin);
        scanf("%[A-Za-z0-9_]", out->var_name);
        out->type = LEX_VAR_NAME;
        return LEX_READ_OK;
    }
    else if(is_operator(letter))
    {
        if(letter == '-')
        {
            if(prev_type == LEX_NONE || prev_type == LEX_BR_L || prev_type == LEX_OPER)
            {
                out->oper = '~';
            }
            else
            {
                out->oper = '-';
            }
            out->oper_priority = low;
            out->oper_assoc = right;
        }
        else
        {
            out->oper = letter;
            if(letter == '-' || letter == '+')
            {
                out->oper_priority = low;
                out->oper_assoc = left;
            }
            else if(letter == '*' || letter == '/')
            {
                out->oper_priority = middle;
                out->oper_assoc = left;
            }
            else if(letter == '^') 
            {
                out->oper_priority = high;
                out->oper_assoc = right;
            }
        }
        out->type = LEX_OPER;
        return LEX_READ_OK;
    }
    else if(letter == '\n' || letter == EOF)
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

EXPR_READ_RESULT read_expr(lex_queue *out)
{
    lexeme cur_lex;
    LEXTYPE prev_lex_type = LEX_NONE;
    LEX_READ_RESULT read_res;
    while ((read_res = read_lex(prev_lex_type, &cur_lex)) == LEX_READ_OK)
    {
        lex_queue_push(out, cur_lex);
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