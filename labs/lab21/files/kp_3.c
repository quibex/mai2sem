#include <stdio.h>
#include "func_kp3.h"

int main(){
    double eps = get_mch_eps();
    double delta = eps * 16;
    printf("mch eps for double = %e\n",delta);

    //Для 8 варианта: 
    var8(delta);
    //Для 9 варианта: 
    var9(delta);
}



