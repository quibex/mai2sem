#include <stdio.h>
#include <stdbool.h>
#include "data.h"

int main(int argc, char *argv[]){
    FILE *input = fopen(argv[1], "rb");
    FILE *output = fopen(argv[2], "wb");
    database_line db;
    char buf1[20];
    char buf2[20];
    char buf3[20];
    char copy_word[] = "Копия";
    char yes_word[] = "Да";

    while (fscanf(input, "%d  %15[0123456789- ]  %d  %d  %d  %d  %d  %d  %s  %s  %s\n",
     &db.id, db.snils, &db.total_sum, &db.subj_sum, &db.math, &db.inf, &db.rus, &db.ind_adv, buf1, buf2, buf3) != EOF){
        db.docs = false;
        for (int i = 0; buf1[i] != '\0' && copy_word[i] != '\0'; i++) {
            if (buf1[i] != copy_word[i]) {
                db.docs = true;
                break;
            }
        }
        db.agree = true;
        for (int i = 0; buf2[i] != '\0' && yes_word[i] != '\0'; i++) {
            if (buf2[i] != yes_word[i]) {
                db.agree = false;
                break;
            }
        }
        db.commun = true;
        for (int i = 0; buf3[i] != '\0' && yes_word[i] != '\0'; i++) {
            if (buf3[i] != yes_word[i]) {
                db.commun = false;
                break;
            }
        }

        fwrite(&db, 1, sizeof(database_line), output);
    }

    fclose(input);
    fclose(output);

    return 0;
}