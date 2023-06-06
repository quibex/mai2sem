#include <stdbool.h>
#include "vector2.h"
#include <stdio.h>



void merge(dbl_vector *p1, dbl_vector *p2, dbl_vector *p3, dbl_vector *p4){

    dbl_vector *cur_arr = p1;
    printf("=1= p1: %d ; p2: %d; p3: %d; p4: %d\n", p1->size, p2->size,  p3->size,  p4->size);

    while(!dbl_is_empty(p3) && !dbl_is_empty(p4)){
        printf("%lf <= %lf == %lf\n", top(p3), top(p4), tail(cur_arr));
        if(top(p3) <= top(p4)) {
            dbl_push_back(cur_arr, dbl_pop_front(p3));
        }  else {
            dbl_push_back(cur_arr, dbl_pop_front(p4));
        }
        if((tail(cur_arr) > top(p3)) && (tail(cur_arr) > top(p4))) {
            if (cur_arr == p2){
                cur_arr = p1;
            } else {
                cur_arr = p2;
            }
        }
    }
    while (!dbl_is_empty(p3))
    {
        dbl_push_back(cur_arr, dbl_pop_front(p3));
        if((tail(cur_arr) > top(p3))) {
            if (cur_arr == p2){
                cur_arr = p1;
            } else {
                cur_arr = p2;
            }
        }
    }
    while (!dbl_is_empty(p4))
    {
        dbl_push_back(cur_arr, dbl_pop_front(p4));
        if((tail(cur_arr) > top(p4))) {
            if (cur_arr == p2){
                cur_arr = p1;
            } else {
                cur_arr = p2;
            }
        }
    }
    
    printf("=2= p1: %d ; p2: %d; p3: %d; p4: %d\n\n", p1->size, p2->size,  p3->size,  p4->size);
}

void merge_sort(dbl_vector *p1){
    dbl_vector p2, p3, p4;
    dbl_init(&p2);
    dbl_init(&p3);
    dbl_init(&p4);
    dbl_vector *cur_arr = &p3;
    
    dbl_push_back(cur_arr, dbl_pop_front(p1));


    while (!dbl_is_empty(p1))
    {
        if (top(p1) >= tail(cur_arr)) {
            dbl_push_back(cur_arr, dbl_pop_front(p1));
        } else {
            if (cur_arr == &p3) cur_arr = &p4;
            else cur_arr = &p3;
            dbl_push_back(cur_arr, dbl_pop_front(p1));
        
        }
    }

    while((!dbl_is_empty(&p2) || !dbl_is_empty(&p3) || !dbl_is_empty(&p4))) // пока не отсортирован 
    { 
        merge(&p3, &p4, p1, &p2);
        merge(p1, &p2, &p3, &p4);
    }

}



int main()
{
    dbl_vector res;
    dbl_init(&res);

    double arr[] = {1, 1, 1, 3, 6, -24};
    for(int i = 0; i < 6; i++){
        dbl_push_back(&res, arr[i]);
    }
    merge_sort(&res);

    for(int i = 0; i < 6; i++) {
        printf("%lf ", dbl_get_el(&res, i));
    }

}