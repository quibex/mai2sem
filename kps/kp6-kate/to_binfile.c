#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_funcs.h"

void file_bin(const char* input_file, const char* output_file){ //создаем бинарный файл
    FILE *input = fopen(input_file, "rb"); //открыть для чтения
    FILE *output = fopen(output_file, "wb"); //открыть для записи
    database_line b;
    if ((input == NULL) || (output == NULL)) //ошибка, не удалось открыть файл
    {
        printf("Error open\n");
        exit(1);
    }
    char citizenship[100];
    
    while (fscanf(input, "%d  %ld  %ld  %d  %d  %s  %d  %d  %d  %d  %d\n",
     &b.idx, &b.id, &b.SNILS, &b.id2, &b.year, citizenship, &b.math, &b.inf_or_physics, &b.rus, &b.additional_p, &b.total_sum) != EOF){
    //считываем значения из поступающего файла
        b.citizenship = false;
        if (strcmp(citizenship, "гражданкаРФ") == 0){
            b.citizenship = true;
        } 

        int successfully_written = fwrite(&b, sizeof(database_line), 1, output);
        if (successfully_written != 1) { //если запись удалась, то ошибки не будет
            printf("Error writing\n");
            exit(2);
        }
    }
    fclose(input); fclose(output);
    //закрываем файлы
}
