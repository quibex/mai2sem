#include<stdio.h>

int max();
int min(int a, int b){
    return (b > a)?a:b;
}

int main(){
    int a=5, b=43;
    int c = max(a, b) - min(a, b);
    printf("%d", c);
}
