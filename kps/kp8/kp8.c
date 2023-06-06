#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "struct/mylist.h"
#include "struct/iterator.h"

void clean_input(){
    char s;
    while (s != '\n') s = getchar();
    fflush(stdin);
}

bool check_extra_input(){
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF) {
        if (ch != ' ' && ch != '\t') { // игнорируем пробелы и табуляцию
            return false;
        }
    }
    return true;
}

bool input_errors(){
    if (!check_extra_input()) {
        clean_input();
        printf("error: extra input after command\n");
        return true;
    } 
    return false;
}

bool correct_input_uint(unsigned int *val) {
    int stat = scanf("%u", val);
    if (stat != 1) {
        clean_input();
        printf("error: invalid input format\n");
        return false;
    }
    return true;
}

void process_unknown_command(){
    clean_input();
    printf("there is no such command\n");
}

void print_manual(){
    printf("This program provides the ability to use the list structure with values unsigned int. \nThe following commands are defined: \n1. add \"val\"\t\t - Add an element to the list \n2. rm \"val\"\t\t - Remove an element from the list \n3. len\t\t\t - Length of the list \n4. rm range \"min\" \"max\"\t - Remove list elements with values within a specified range \n5. print \t\t - Print list \n6. help\t\t\t - Print manual\n7. end\t\t\t - Finish the program. \n");
}



int main() {

    setbuf(stdout, NULL);

    print_manual();

    char command[10];
    list list;
    init(&list);

    while (1){
        printf(">>> ");
        scanf("%s", command);
        if ((strcmp(command, "end") == 0) || feof(stdin)) break;
        else if (strcmp(command, "add") == 0) {
            unsigned int val;
            if (correct_input_uint(&val)){
                if (!input_errors()){
                    insert(&list, val);
                }
            }
        } else if (strcmp(command, "rm") == 0) {
            char subcommand[10];
            scanf("%s", subcommand);
            if (strcmp(subcommand, "range") == 0) {
                unsigned int min, max;
                int stat = scanf("%u %u", &min, &max);
                if (stat != 2) {
                    clean_input();
                    printf("error: invalid input format\n");
                } else {
                    if (!input_errors()){
                        delete_range(&list, min, max);
                    }
                }
            } else {
                unsigned int val = atoi(subcommand);
                if (!input_errors()){
                    delete_by_val(&list, val);
                }
            }
        } else if (strcmp(command, "len") == 0) {
            if (!input_errors()){
                printf("len: %d\n", length(&list));
            }
        } else if (strcmp(command, "print") == 0) {
            if (!input_errors()){
                printf("list: "); print_list(&list);
            }
        } else if (strcmp(command, "help") == 0) {
            print_manual();
        } else {
            process_unknown_command();
        }
    }
    destroy(&list);
    
    return 0;
}