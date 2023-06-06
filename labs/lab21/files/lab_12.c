#include<stdio.h>

int abs(int a){
    if (a>0){
        return a;
    }    
    else {
        return -a;
    }
}
int chek_non_existence(int a){
    int b=0, c=0;
    while ((a/10)!=0){
        b = abs(a%10); 
        c = abs((a%100)/10);
        if (b<c){
            return 0;
        } else
        a/=10;
    }
    return 1;
}

void print_result(int ordered){
    if (ordered) {
        printf("Цифры в числе упорядочены по неубыванию \n");
    } else {
        printf("Цифры в числе не упорядочены по неубыванию \n");
    }
}

int main(){
    int num=0;
    while(1==scanf("%d", &num)){
        print_result(chek_non_existence(num));
    }
    return 1;
}