#include<stdio.h>

int min(int a, int b){
    if (a<b) return a;
    else return b;
}
int max(int a, int b){
    if (a>b) return a;
    else return b;
}
int mod(int a, int b){
    if((a<b && a>0 && b>0) || (a>b && a<0 && b<0)){
        return a;
    } else if(a>b && a>0 && b>0){
        while(a>b){
            a-=b;
        } return a;
    } else if(a<b && a<0 && b<0){
        while(a<b){
            a-=b;
        } return a;
    } else if(a>0 && b<0){
        while(a>0){
            a+=b;
        } return a;
    } else if(a<0 && b>0){
        while(a<0){
            a+=b;
        } return a;
    } else return 0;
}
int module(int a){
    if(a>0) return a;
    else return -a;
}




int main(){
    int a = -17, b =5;
    printf("%d \n", module(a));
    return 0;
}