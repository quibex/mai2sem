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
    if((a<b && a>0 && b>=0) || (a>b && a<0 && b<=0)){
        return a;
    } else if(a>b && a>0 && b>=0){
        return (a%b);
    } else if(a<b && a<0 && b<=0){
        return (a%b);
    } else if(a>0 && b<=0){
        return (a%b)?(a%b+b):(0);
    } else if(a<0 && b>=0){
        return (a%b)?(a%b+b):(0);
    } else return 0;
}

int div(int a, int b){
    int d=0;
    if((a<b && a>0 && b>=0) || (a>b && a<0 && b<=0)){
        return 0;
    } else if(a>b && a>0 && b>=0){
        return (a/b);
    } else if(a<b && a<0 && b<=0){
        return (a/b);
    } else if(a>0 && b<=0){
        return (a%b)?(a/b - 1):(a/b);
    } else if(a<0 && b>=0){
        return (a%b)?(a/b - 1):(a/b);
    } else return 1;
}

int module(int a){
    if(a>0) return a;
    else return -a;
}

int sign(int a){
    if(a>0) return 1;
    else if(a==0) return 0;
    else return -1;
}

int newi(int i, int j, int l, int k){
    return mod((mod(((i)+(j)), ((module(min(((j)-(l)), ((l)-(k))))+1)-(k)))), 30);
}
int newj(int i, int j, int l, int k){
    return max((div(((i)+(j)),(2+sign((j)*(l)-(i)*k)))), (div(((j)+(l)),(2 + sign((i)*(j)-(l)*k)))))-10;
}
int newl(int i, int j, int l, int k){
    return mod(max((i),(j)) * min((i), (l)), 30);
}

void print_result(int hit, int k, int i, int j, int l){
    if(hit) printf("Попал c %d шага, i = %d, j = %d, l = %d \n", k, i, j, l);
    else printf(" Непопал, i = %d, j = %d, l = %d \n", i, j, l );
}


int main(){
    int i=8, j=15, l=10, k, hit=0, iprevious, jprevious, lprevious;
    for(k=0; k<50; k++){
        //printf("%d %d %d \n", i, j, l);
        if ((i<=0 && i>=-10 && j>=0 && j<=10 && (10+i)<=(j)) || ((i<=0 && i>=-10 && j>=10 && j<=20 && module(i)>=(j-10)))){
            hit = 1;
            break;
        }
        iprevious = i; jprevious = j; lprevious = l;
        i = newi(iprevious, jprevious, lprevious, k);
        j = newj(iprevious, jprevious, lprevious, k);
        l = newl(iprevious, jprevious, lprevious, k);
    }
    
    print_result(hit, k, i, j, l);

    int a, b;
    while (2 == scanf("%d%d", &a, &b)) {
        printf("%d %d\n", div(a, b), mod(a, b));
    }
}
