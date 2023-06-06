#include<stdio.h>

void print_array(int n, int array[n][n]){
    for(int id_line=0; id_line<(n+n-1); id_line++){
        if(id_line%2==0){
            if(id_line<n){
                for(int i=0; i<=id_line; i++){
                    printf("%d ", array[i][(n-id_line-1)+i]);
                }
            } else {
                    int j=0;
                for(int i=id_line-n+1; i<n; i++){
                    printf("%d ", array[i][j]);
                    j++;
                }
            }
        } else {
            if(id_line<n){
                    int j=n-1;
                for(int i=id_line; i>=0; i--){
                    printf("%d ", array[i][j]);
                    j--;
                }
            } else {
                    int j=n-id_line+(n-2);
                for(int i=n-1; i>=id_line-n+1; i--){
                    printf("%d ", array[i][j]);
                    j--;
                }
            }
        }
    }
}

int main(){
    int n;
    scanf("%d", &n);
    int array[n][n];
    for(int i=0; i!=n; i++){
        for(int j=0; j!=n; j++){
            scanf("%d", &array[i][j]);
        }
    }
    print_array(n, array);
}