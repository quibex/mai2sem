#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "tree2.h"
#include "enummaamg.h" 

void clean_input(){
    char s;
    while (s != '\n') s = getchar();
    fflush(stdin);
}

void print_manual(){
    printf("This program provides the ability to use the binary tree structure with values MAAMG companies.\nMAAMG: MICROSOFT, APPLE, AMAZON, META, GOOGLE. You can write the company name like this: GOOGLE, Google, google.\nThe following commands are defined: \n1. add \"company name\"\t - Add a company to the mytree\n2. rm \"company name\"\t - Remove a company from the mytree \n3. print\t\t - Print tree\n4. count leaves \t - Number of tree leaves \n5. end\t\t\t - Finish the program\n6. help\t\t\t - Print manual. \n");
}

int main() {

    print_manual();
    
    tree mytree = NULL;
    char command[10];

    setbuf(stdout, NULL);

    while (1){
        printf(">>>");
        scanf("%s", command);
        if ((strcmp(command, "end") == 0) || feof(stdin)) break;
        else if (strcmp(command, "add") == 0) {
            char company[10];
            char invalid_input[2];
            int nmber_of_elmnt_entered = scanf("%s%s", company, invalid_input);
            if (nmber_of_elmnt_entered != 1) {
                clean_input();
                printf("error: invalid input format\n");
            } else {
                int company_id = get_enum_id(company);
                if (company_id == -1) {
                    printf("error: such a company does not exist or is not MAAMG\n");
                } else if (!add(&mytree, company_id)){
                    printf("error: this element already exists\n");
                };
            }
        } else if (strcmp(command, "rm") == 0) {
            char company[10];
            char invalid_input[2];
            int nmber_of_elmnt_entered = scanf("%s%s", company, invalid_input);
            if (nmber_of_elmnt_entered != 1) {
                clean_input();
                printf("error: invalid input format\n");
            } else {
                int company_id = get_enum_id(company);
                if (company_id == -1)
                {
                    printf("error: such a company does not exist or is not MAAMG\n");
                } else if (!delete(&mytree, company_id)){
                    printf("error: this element not exists in tree\n");
                };
            }
        } else if (strcmp(command, "print") == 0){
            draw_tree(mytree);
        } else if (strcmp(command, "count") == 0){
            char company[10];
            int nmber_of_elmnt_entered = scanf("%s", company);
            if ((nmber_of_elmnt_entered != 1) || (strcmp(company, "leaves") != 0)) {
                clean_input();
                printf("there is no such command: %s %s\n", command, company);
            } else {
                int cnt_leaves = count_leaves(mytree);
                printf("%d\n", cnt_leaves);
            }
        } else if (strcmp(command, "help") == 0) {
            print_manual();
        } else {
            clean_input();
            printf("there is no such command: %s\n", command);
        }
    }
    
    destroy(&mytree);

    return 0;
}
