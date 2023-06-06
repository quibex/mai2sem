#include <stdbool.h>
#include <stdio.h>

int main(){
    for (int i = 0; i < 10000; i++){
        printf("%d ", i);
        if (!(i % 100)){
            printf("\n");
        }
    }
}