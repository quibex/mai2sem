#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include "kp7.h"

max_el_mx get_max_el(matrix *mx){
    max_el_mx max_el;
    max_el.clmn = 0;
    max_el.row = 0;
    max_el.val = 0;
    max_el.prev_clmn_max_el = -1;
    int cur_row = 0;
    for (int i = 0; i < mx->elems.size; i++){
        dbl_mx_el elem = mx_get_el(&mx->elems, i);
        if ((fabs(elem.val) == fabs(max_el.val)) && (max_el.row == cur_row)){
            max_el.prev_clmn_max_el = max_el.clmn;
            printf("biba - %d\n", elem.clmn);
        }
        if (fabs(elem.val) >= fabs(max_el.val)) {
            max_el.val = elem.val;
            max_el.clmn = elem.clmn;
            max_el.row = cur_row;
            // if (max_el.row == cur_row){
            //     max_el.prev_clmn_max_el = -1;
            // }
        }
        if (elem.next_el_idx == 0) cur_row++;
        
    }
    if (max_el.val == 0) max_el.val = -1;
    return max_el;
}

matrix read_mtx(){
    int n, m;
    scanf("%d %d", &n, &m);
    matrix mx;
    mx.n = n;
    mx.m = m;
    int_init(&mx.row);
    mx_init(&mx.elems);

    for (int i = 0; i < n; i++){
        bool row_empty = true;
        for (int j = 0; j < m; j++){
            double num;
            scanf("%lf", &num);
            if (num != 0){
                if (row_empty){ 
                    row_empty = false;
                    int_push_back(&mx.row, mx_get_size(&mx.elems));
                } else {        
                    dbl_mx_el prev_el = mx_pop_back(&mx.elems);
                    prev_el.next_el_idx = mx_get_size(&mx.elems) + 1;
                    mx_push_back(&mx.elems, prev_el);
                }
                dbl_mx_el el;
                el.clmn = j;
                el.val = num;
                el.next_el_idx = 0;
                mx_push_back(&mx.elems, el);
            }
        }
        if (row_empty){
            int_push_back(&mx.row, -1);
        }
    }
    return mx;
}

void print_mtx_user(matrix *mx){
    printf("Matrix:\n");
    for (int i = 0; i < mx->n; i++){
        bool row_empty = false;
        int elem_idx = int_get_el(&mx->row, i);
        if (elem_idx == -1) row_empty = true;
        dbl_mx_el elem = mx_get_el(&mx->elems, elem_idx);
        for (int j = 0; j < mx->m; j++){
            if (!row_empty && elem.clmn == j){
                printf("%lf ", elem.val);
                elem_idx = elem.next_el_idx;
                if (elem_idx == 0) row_empty = true;
                elem = mx_get_el(&mx->elems, elem_idx);
            } else {
                printf("0.000000 ");
            }
        }
        printf("\n");
    }
}

void print_mtx_private(matrix *mx){
    printf("Matrix M: | ");
    for (int i = 0; i < mx->row.size; i++){
        printf("%d | ", int_get_el(&mx->row, i));
    }
    printf("\nMatrix A: ");
    for (int i = 0; i < mx->elems.size; i++){
        dbl_mx_el elem = mx_get_el(&mx->elems, i);
        printf("[ %d | %lf | %d ] ", elem.clmn, elem.val, elem.next_el_idx);
    }
    printf("\n");
}

void kp7_var2(matrix *mx){
    max_el_mx max_el = get_max_el(mx);
    int changeable_clmn;
    printf("\n%d\n", max_el.prev_clmn_max_el);
    if (max_el.prev_clmn_max_el == -1){
        changeable_clmn = max_el.clmn;
    } else {
        changeable_clmn = max_el.prev_clmn_max_el;
    }
    for (int i = 0; i < mx->elems.size; i++){
        dbl_mx_el elem = mx_get_el(&(mx->elems), i);
        if (elem.clmn == changeable_clmn){
            elem.val = (elem.val)/max_el.val;
            mx_set_el(&(mx->elems), i, elem);
        }
    }
}