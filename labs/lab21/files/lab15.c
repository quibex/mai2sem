#include<stdio.h>

void building_array(int size_array, int array[size_array][size_array]){
    for(int i=0; i!=size_array; i++){
        for(int j=0; j!=size_array; j++){
            scanf("%d", &array[i][j]);
        }
    }
}

void checking_array(int size_array, int array[size_array][size_array], int deleted_lines[size_array]){
    deleted_lines[0]=0;
    for(int i1=0; i1<size_array; i1++){
        for(int i2=i1+1; i2<size_array; i2++){
            int number_of_coincidences=0;
            for(int j=0; j<size_array; j++){
                if(array[i1][j]==array[i2][j]){
                    number_of_coincidences++;
                }
            }
            if(number_of_coincidences==size_array){
                deleted_lines[i2]=1;
            } else if(deleted_lines[i2]!=1){
                deleted_lines[i2]=0;
            }
        }
    }
}

void building_new_array(int size_array,  int array[size_array][size_array],int size_row_new_array, int new_array[size_row_new_array][size_array], int deleted_lines[size_array]){
    
    int i_new=0;
    for(int i=0; i<size_array; i++){
        if(deleted_lines[i]!=1){
            for(int j=0; j<size_array; j++){
                new_array[i_new][j]=array[i][j];
            }
        i_new++;
        }
    }
}

void print_array(int size_row_array, int size_column_array, int array[size_row_array][size_column_array]){
    for(int i=0; i<size_row_array; i++){
        for(int j=0; j<size_column_array; j++){
            printf("%d ", array[i][j]);
        }
    putchar('\n');
    }
}

int main(){
    int size_array, size_row_new_array=0;
    scanf("%d", &size_array);
    int array[size_array][size_array]; int deleted_lines[size_array];
    building_array(size_array, array);
    checking_array(size_array, array, deleted_lines);
    for(int i=0; i<size_array; i++){
        if(deleted_lines[i]!=1){
            size_row_new_array++;
        }
    }
    int new_array[size_row_new_array][size_array];
    building_new_array(size_array, array, size_row_new_array, new_array, deleted_lines);
    print_array(size_row_new_array, size_array, new_array);
}