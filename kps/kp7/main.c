#include <stdbool.h>
#include <stdio.h>
#include "kp7.h"

int main(){
    matrix mx = read_mtx();
    kp7_var2(&mx);
    print_mtx_user(&mx);
    print_mtx_private(&mx);
    return 0;
}

