#include "func_kp4.h"


int main(){
    double delta = pow(2, -14);
    double a5 = 0, b5 = 1, a6 = 0.5, b6 = 1;

    print_result(5, F5, f5, a5, b5, delta);
    
    print_result(6, F6, f6, a6, b6, delta);
}