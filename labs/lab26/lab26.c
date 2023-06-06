#include <stdio.h>
#include "int_dque.h"
#include <stdlib.h>

#define max(a, b) a:b?a>b


void print_dq(int_dque* dq){
    for (int i = 0; i < int_dque_get_size(dq); i++){
        int val = int_dque_get_el(dq, i);
        printf("%d ", val);
    }
} 

void merge(int_dque* left, int_dque* right){
    printf("merge: | "); print_dq(left); printf("| and | "); print_dq(right); printf("|\n");
    int_dque result;
    int_dque_init(&result);
    while ( !int_dque_is_empty(left) && !int_dque_is_empty(right))
    {
        int l_val = int_dque_front(left);
        int r_val = int_dque_front(right);
        if (l_val <= r_val){
            printf("   %d <= %d \n", l_val, r_val);
            int_dque_push_back(&result, int_dque_pop_front(left));
        } else {
            printf("   %d >= %d \n", l_val, r_val);
            int_dque_push_back(&result, int_dque_pop_front(right));
        }   
    }
    if (!int_dque_is_empty(left)){
        printf("   add: | "); print_dq(left); printf("|\n");
        while (!int_dque_is_empty(left))
        {
            int_dque_push_back(&result, int_dque_pop_front(left));
        }
    }
    if (!int_dque_is_empty(right)){
        printf("   add: | "); print_dq(right); printf("|\n");
        while (!int_dque_is_empty(right))
        {
            int_dque_push_back(&result, int_dque_pop_front(right));
        }
    }
    while (!int_dque_is_empty(&result))
    {
        int_dque_push_back(left, int_dque_pop_front(&result));
    }
    printf(" result: | "); print_dq(left); printf("|\n");
    int_dque_destroy(&result);
}

void merge_sort(int_dque* dq){
    if (int_dque_get_size(dq) <= 1) return;
    int mid = int_dque_get_size(dq)/2;
    int_dque left;
    int_dque_init(&left);
    for (int i = 0; i < mid; i++){
        int_dque_push_back(&left, int_dque_pop_front(dq));
    }
    merge_sort(&left);
    merge_sort(dq);
    merge(dq, &left); 
    // int_dque_destroy(&left);
    // printf("--%p -- %p--\n", left.buf, dq->buf);
    // free(left.buf);
}

int main(){
    int n;
    printf("Введите кол-во элементов: ");
    scanf("%d", &n);
    int_dque dq;
    int_dque_init(&dq);
    printf("Введите элементы: ");
    for (int i = 0; i < n; i++){
        int val;
        scanf("%d", &val);
        int_dque_push_back(&dq, val);
    }
    merge_sort(&dq);
    printf("Sorted dqueue: | "); print_dq(&dq); printf("|\n");
    int_dque_destroy(&dq);
}