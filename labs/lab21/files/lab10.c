#include<stdio.h>

int fact2();

int fact1(int a){
    if (a == 1 || a ==0){
        return a;
    } return a*=fact2(a-1);
}
int fact2(int a){
    if (a == 1 || a ==0){
        return a;
    } return a*=fact1(a-1);
}

int main(){
    int n=5;
    printf("%d", fact1(n));
}