#pragma once

typedef enum
{
    LEX_NONE,
    LEX_VAR_NAME,
    LEX_CONST,
    LEX_OPER,
    LEX_BR_R,
    LEX_BR_L
} LEXTYPE;

typedef enum
{
    low,
    middle,
    high,
    megahigh
} priority;

typedef enum 
{
    left,
    right
} oper_associativity;

typedef struct 
{
    char var_name;
    double cnst;
    char oper;
    priority oper_priority;
    oper_associativity oper_assoc;
    LEXTYPE type;
} lexeme;

typedef enum
{
    LEX_READ_OK,
    LEX_READ_END,
    LEX_READ_ERROR
} LEX_READ_RESULT;

typedef enum
{
    EXPR_READ_OK,
    EXPR_READ_END,
    EXPR_READ_ERROR
} EXPR_READ_RESULT;




