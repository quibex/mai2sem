#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_funcs.h"

void file_to_bin(const char* input_file, const char* output_file)
{
    FILE *input = fopen(input_file, "rb");
    FILE *output = fopen(output_file, "wb");

    if ((input == NULL) || (output == NULL)) // Ошибка открытия
    {
        printf("Error open\n");
        exit(1);
    }

    database_line db_line;
    char dormitory_rights[20]; // Право на общежитие

    while (fscanf(input, "%d  %ld  %d  %d  %d  %d  %d  %d  %d  %s\n",
     &db_line.idx, &db_line.id, &db_line.total_sum, &db_line.chemistry_dvi, &db_line.chemistry_ege, 
     &db_line.bio, &db_line.math, &db_line.rus, &db_line.ind_adv, dormitory_rights) != EOF){

        db_line.dormitory_rights = false;
        if (strcmp(dormitory_rights, "Да") == 0){
            db_line.dormitory_rights = true;
        } 

        int count_successfully_written = fwrite(&db_line, sizeof(database_line), 1, output);
        if (count_successfully_written != 1) {
            printf("Error writing\n");
            exit(2);
        }
    }

    fclose(input);
    fclose(output);
    
}