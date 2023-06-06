#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_funcs.h"
#include "to_binfile.h"

#define HELPTEXT "\
Данная программа работает с данными из таблицы с данными поступающих.\n\
Для получения желаемого результата нужно запускать с ключом.\n\
Основные ключи:\n\
    \033[35m--help\033[m, получить справку по программе\n\
    \033[35m--tobin binfilepath+name\033[m, преобразовать файл в бинарный\n\
    \033[35m--sort math\033[m, получить сортированный список по баллам математика ЕГЭ\n\
    \033[35m       him dvi\033[m,                            по баллам химия ДВИ\n\
    \033[35m       him ege\033[m,                            по баллам химия ЕГЭ\n\
    \033[35m       bio\033[m,                                по баллам биология ЕГЭ\n\
    \033[35m       rus\033[m,                                по баллам русский язык ЕГЭ\n\
    \033[35m--range a b\033[m, вывести список абитуриентов с правом на общежитие, средний балл которых находиться в [a;b].\n\
            a b - задаваемые числа числа\n\
    \n\
    Все ключи используются по отдельности\n\
    Передаваемый файл может быть тектовым или бинарным. Если файл не бинарный, то создатся бинарный в рабочей директории.\n\
    Чтобы запустить программу, Вам необходимо написать: \033[35m./kp6 --help\033[m и вы получите данное сообщение.\n\
    Чтобы просто преобразовать файл в бинарный без взаимодейтвия с данными, используйте ключ --tobin, например: \033[35m./kp6 data.txt --tobin data.bin\033[m\n\
    Для работы с данными из таблицы используйте ключи, например: \033[35m./kp6 data.txt --sort math\033[m\n\
    \n\
    Формат таблицы: \"№\" \"ID\" \"Общий балл\" \"Химия ДВИ\" \"Химия ЕГЭ\" \"Биология ЕГЭ\" \"Математика ЕГЭ\" \"Русский язык ЕГЭ\" \"Индивидуальные достижения\" \"Право на общежитие(\"Да\"/\"Нет\")\"\n\
"

#define tmp_database_name "database.bin" 

bool is_binary_file(const char* file_path);

int main(int argc, char* argv[]) {

    if ((argc <= 1) || (argc > 5))
    {
        printf("Ошибка запуска, используйте ключ --help, чтобы получить справку о программе\n");
        exit(1);
    }
    
    else if (strcmp(argv[1], "--help") == 0)
    {
        printf(HELPTEXT);
        exit(0);
    }

    if ((argv[2]) == NULL)// чтобы не было дальнейшех сравнений, при котором будет Segmentation fault
    {
        printf("Ошибка запуска, используйте ключ --help или запустите без ключей, чтобы получить справку о программе\n");
        exit(1);
    }

    else if (strcmp(argv[2], "--tobin") == 0)
    {
        if (argc > 4) {
            printf("Ошибка запуска, используйте ключ --help или запустите без ключей, чтобы получить справку о программе\n");
            exit(1);
        }
        file_to_bin(argv[1], argv[3]);
        exit(0);
    }

    else if ((strcmp(argv[2], "--range") == 0) || (strcmp(argv[2], "--sort") == 0))
    {
        
        FILE* database = NULL;


        if (!is_binary_file(argv[1])) {
            file_to_bin(argv[1], tmp_database_name);
            database = fopen(tmp_database_name, "rb");
        }
        else {
            database = fopen(argv[1], "rb");
        }

        if (database == NULL) {
            printf("Cannot open database file\n");
            fclose(database);
            exit(2);
        }

        print_table(database); 

        if (strcmp(argv[2], "--range") == 0)
        {

            if (argv[3] == NULL || argv[4] == NULL){
                printf("Error: No such parameters keys --range\n"); 
                exit(3);
            } 

            printf("Результат работы программы:\n");

            print_dorm_eligible_students_by_avg_grade_in_range(database, atoi(argv[3]), atoi(argv[4]));

        }
        else 
        {
            if (argv[3] == NULL){
                printf("Error: No such parameters keys --sort\n"); 
                exit(4);
            } 

            printf("Результат сортировки:\n");
        
            if(strcmp(argv[3], "math") == 0){
                print_sorted_by_math(database);
            } 
            else if (strcmp(argv[3], "rus") == 0){
                print_sorted_by_rus(database);
            }
            else if (strcmp(argv[3], "bio") == 0){
                print_sorted_by_bio(database);
            }
            else if (strcmp(argv[3], "him") == 0){
                if (strcmp(argv[4], "dvi") == 0){
                    print_sorted_by_him_dvi(database);
                }
                else if (strcmp(argv[4], "ege") == 0) print_sorted_by_him_ege(database);
                else {
                    printf("Error: No such parameters keys --sort\n"); 
                    exit(4);
                }
            }
            else {
                printf("Error: No such parameters keys --sort\n"); 
                exit(4);
            }
        }

        fclose(database);
    }
    else 
    {
        printf("Ошибка запуска, используйте ключ --help или запустите без ключей, чтобы получить справку о программе\n");
        exit(0);
    }
    
    return 0;
}

bool is_binary_file(const char* file_path) {
    FILE* file = fopen(file_path, "rb");
    if (file == NULL) {
        printf("Error open %s\n", file_path);
        exit(1);
    }

    bool is_binary = false;
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\0') {
            is_binary = true;
            break;
        }
    }


    fclose(file);
    return is_binary;
}


