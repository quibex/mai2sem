#include <stdio.h>
#include <stdbool.h>

typedef struct {
    double* buf;
} stack_dbl;

void init(stack_dbl* s);
void destroy(stack_dbl* s);
void push(stack_dbl* s, double val);
double pop(stack_dbl* s);
bool is_empty(stack_dbl* s);



double remove_max(stack_dbl *s){
    stack_dbl tmp;
    init(&tmp);
    double max_val = pop(s);
    push(&tmp, max_val);
    while (!is_empty(s)){
        double m = pop(s);
        push(&tmp, m);
        if (m > max_val) max_val = m;
    }
    bool max_detected = false;
    while (!is_empty(&tmp)){
        double v = pop(&tmp);
        if (v == max_val && !max_detected){
            max_detected = true;
        }

    }
}

void sort(stack_dbl* s){
    stack_dbl tmp;
    init(&tmp);
    while (!is_empty(s)){
        push(&tmp, remove_max(s));
    }
    while (!is_empty(&tmp)){
        push(s, remove_max(&tmp));
    }
    destroy(&tmp);
}


////////////////////////////////////////////////////////////////////////////////

void merge_sort(stack_dbl* s){
    if (size(s) == 1) return;
    int mid = size(s)/2;
    stack_dbl left;
    init(&left);
    for (int i=0; i<mid; i++){
        push(&left, pop(s));
    }
    merge_sort(&left);
    merge_sort(s);
    stack_dbl* result;
    result = merge(&left, s); // merge return stack* 
    while (!is_empty(&result)){
        push(s, pop(result));
    }
    destroy(&left);
    destroy(result);
}

