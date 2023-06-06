#include <stdio.h>
#include "dack.h"

int main(){
    double a;
    dbl_dack dk;
    dbl_dk_init( &dk);
    while (1==scanf("%lf", &a)){
        dbl_dk_push_front(&dk, a);
    }
    while (!dbl_dk_is_empty(&dk)){
        a=dbl_dk_pop_back(&dk);
        printf("%lf \n", a);
    }
    dbl_dk_destr(&dk);
    return 0;
}