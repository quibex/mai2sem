#include <stdio.h>

int main(){
    char c = '1';
    int lvl = 0;
    while(c != EOF){
        c = getc(stdin);
        if (c == '('){
            lvl++;
        }
        else if (c == ')'){
            lvl--;
        }
        else if (c == ' ' || c == '\t'){
            continue;
        }
        else if (c == '\n') {
            break;
        }
        else {
            fprintf(stderr, "Invalid character\n");
            return 1;
        }
        if (lvl < 0){
            fprintf(stdout, "Incorrect\n");
            break;
        }
    }
    if (lvl == 0){
        fprintf(stdout, "Correct\n");
    }
    else {
        fprintf(stdout, "Incorrect\n");
    }

    return 0;
}