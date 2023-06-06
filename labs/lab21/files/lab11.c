#include<stdio.h>
#include<stdlib.h>

enum state{
    SEARCH_NUMBER,
    NOT_A_NUMBER_OR_NEGATIVE_NUMBER_OR_NUMBER_LESS_INT_MAX,
    MAYBE_NUMBER_WITH_LEADING_ZEROS,
    MAYBE_SIGNED_NUMBER,
    MAYBE_NUMBER,
    MAYBE_NUMBER_OVER_INT_MAX
}; 

enum state state=SEARCH_NUMBER;

int sep(int symbol){
    if (symbol==' ' || symbol==',' || symbol=='\t' || symbol=='\n' || symbol==EOF){
        return 1;
    } 
    return 0;
}

int what_number_or_not_a_number(int symbol){
    if (symbol>='0' && symbol<='9'){
        return symbol-'0';
    } 
    return -1;
}


void print_sign_zeros_nan_number(int *sign_number, int *number_of_leading_zeros, int *size_array, int array[], int *number,  int symbol){
    if(*sign_number!=' '){
        printf("%c", *sign_number);
        *sign_number=' ';
    }
    while(*number_of_leading_zeros>0){
        printf("0");
        *number_of_leading_zeros-=1;
    }
    if(*size_array>0){
        for(int i=0; i<*size_array; i++){
        printf("%d", array[i]);
        }
        *size_array=0;
    }
    if(*number>0){
        printf("%d", *number);
        *number=0;
    }
    if(symbol!=EOF){
        printf("%c", symbol);
    }
}
void print_end(int *sign_number, int *number_of_leading_zeros, int *size_array, int array[], int *number){
    if(*sign_number!=' '){
        printf("%c", *sign_number);
    }
    while(*number_of_leading_zeros>0){
        printf("0");
    }
    if(*number>0 && *size_array==0){
        printf("%d", *number);
    }
}

int main(){
    int symbol, sign_number=' ', number_of_leading_zeros=0, number=0, size_array=0;
    int *array = (int*)malloc(sizeof(int) * size_array);
    do {
        symbol=getchar();
        if(state==SEARCH_NUMBER){
            if(sep(symbol)){
                state=SEARCH_NUMBER;
                if(symbol!=EOF){
                    printf("%c", symbol);
                }
            } else if(symbol=='0'){
                state=MAYBE_NUMBER_WITH_LEADING_ZEROS;
            } else if(symbol=='+'){
                sign_number='+';
                state=MAYBE_SIGNED_NUMBER;
            } else if(what_number_or_not_a_number(symbol)>0){
                number=number*10+what_number_or_not_a_number(symbol);
                state=MAYBE_NUMBER;
            } else {
                state=NOT_A_NUMBER_OR_NEGATIVE_NUMBER_OR_NUMBER_LESS_INT_MAX;
                if(symbol!=EOF){
                    printf("%c", symbol);
                }
            }
        } else if(state==MAYBE_SIGNED_NUMBER){
            if(sep(symbol)){
                state=SEARCH_NUMBER;
                print_sign_zeros_nan_number(&sign_number, &number_of_leading_zeros, &size_array, array, &number, symbol);
            } else if(symbol=='0'){
                state=MAYBE_NUMBER_WITH_LEADING_ZEROS;
            } else if(what_number_or_not_a_number(symbol)>0){
                state=MAYBE_NUMBER;
                number=number*10+what_number_or_not_a_number(symbol);
            } else {
                state=NOT_A_NUMBER_OR_NEGATIVE_NUMBER_OR_NUMBER_LESS_INT_MAX;
                print_sign_zeros_nan_number(&sign_number, &number_of_leading_zeros, &size_array, array, &number, symbol);
            }
        }else if(state==MAYBE_NUMBER_WITH_LEADING_ZEROS){
            number_of_leading_zeros++;
            if(sep(symbol)){
                print_sign_zeros_nan_number(&sign_number, &number_of_leading_zeros, &size_array, array, &number, symbol);
                state=SEARCH_NUMBER;
            }else if(what_number_or_not_a_number(symbol)>0){
                number=number*10+what_number_or_not_a_number(symbol);
                state=MAYBE_NUMBER;
            }else if(symbol=='0'){
                state=MAYBE_NUMBER_WITH_LEADING_ZEROS;
            }else {
                state=NOT_A_NUMBER_OR_NEGATIVE_NUMBER_OR_NUMBER_LESS_INT_MAX;
                print_sign_zeros_nan_number(&sign_number, &number_of_leading_zeros, &size_array, array, &number, symbol);
            }
        }else if(state==NOT_A_NUMBER_OR_NEGATIVE_NUMBER_OR_NUMBER_LESS_INT_MAX){
            if(sep(symbol)){
                state=SEARCH_NUMBER;
                if(symbol!=EOF){
                    printf("%c", symbol);
                }
            } else {
                state=NOT_A_NUMBER_OR_NEGATIVE_NUMBER_OR_NUMBER_LESS_INT_MAX;
                if(symbol!=EOF){
                    printf("%c", symbol);
                }
            }
        }else if(state==MAYBE_NUMBER){
            if (what_number_or_not_a_number(symbol)>=0){
                if(number!=((number*10+what_number_or_not_a_number(symbol))-what_number_or_not_a_number(symbol))/10){ 
                    state=MAYBE_NUMBER_OVER_INT_MAX;
                }else { 
                    number=number*10+what_number_or_not_a_number(symbol);
                    state=MAYBE_NUMBER;
                } 
            } else if (sep(symbol)){
                if(size_array==0){
                    print_sign_zeros_nan_number(&sign_number, &number_of_leading_zeros, &size_array, array, &number, symbol);
                }
                if(size_array>0){
                    size_array=0;
                }  
                number=0; sign_number=' '; number_of_leading_zeros=0;
                if(symbol!=EOF){
                    printf("%c", symbol);
                }
                state=SEARCH_NUMBER;
            } else {
                state=NOT_A_NUMBER_OR_NEGATIVE_NUMBER_OR_NUMBER_LESS_INT_MAX;
                print_sign_zeros_nan_number(&sign_number, &number_of_leading_zeros, &size_array, array, &number, symbol);
            }
        }
        if(state==MAYBE_NUMBER_OVER_INT_MAX){
            size_array++;
            array = (int*)realloc(array, sizeof(int) * size_array);
            array[size_array-1]=number;
            number=what_number_or_not_a_number(symbol);
            state=MAYBE_NUMBER;
        }
        
    } while(symbol!=EOF);
    free(array);
    //print_end(&sign_number, &number_of_leading_zeros, &size_array, array, &number);
}