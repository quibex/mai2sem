#include <stdio.h>
#include "dack2.h"

int main(){
    double a;
    dbl_dk dk;
    dbl_dk_init( &dk);
    for (int i = 0; i < 20; i++){
        scanf("%lf", &a);
        dbl_dk_push_back(&dk, a);
    }
    for (int i =0; i < 18; i++){
        dbl_dk_pop_back(&dk);
    }
    while (!dbl_dk_is_empty(&dk)){
        a=dbl_dk_pop_front(&dk);
        printf("%lf - %d \n", a, (&dk)->cap);
    }
    
    dbl_dk_destr(&dk);
    return 0;
}