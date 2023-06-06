#include <stdio.h>
#include "queue.h"

int main(){
    double a;
    dbl_queue q;
    dbl_q_init( &q);
    while (1==scanf("%lf", &a)){
        dbl_q_push(&q, a);
    }
    while (!dbl_q_is_empty(&q)){
        a=dbl_q_pop(&q);
        printf("%lf", a);
    }
    dbl_q_destr(&q);
    return 0;
}