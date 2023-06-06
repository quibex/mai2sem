#include <stdio.h>
#include "vector.h"

int main(){
    dbl_vec v;
    dv_init(&v);
    dv_resize(&v, 10);
    int s = dv_size(&v);
    double a = 0;
    for (int i = 0; i < dv_size(&v); i++){
        scanf("%lf", &a);
        // printf("%lf \n", a);
        dv_put(&v, i, a);
    }
    for (int i = dv_size(&v); i > 0; i--){
        printf("%lf \n", dv_get(&v, i-1));
    }
}