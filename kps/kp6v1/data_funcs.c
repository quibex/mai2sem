#include <stdio.h>
#include <string.h>
#include "data_funcs.h"
#include "hoar_sort.h"

// Найти абитуриентов с средной оценкой в указанном диапозоне с правом на общежитие 
// Сортировка по значениям

void print_header(){
    printf("%-2s\t%-12s\t%-10s\t%-9s\t%-9s\t%-12s\t%-14s\t%-16s\t%-25s\t%-17s\n", 
    "№", "ID", "Общий балл", "Химия ДВИ", "Химия ЕГЭ", "Биология ЕГЭ", "Математика ЕГЭ", "Русский язык ЕГЭ", "Индивидуальные достижения", "Право на общежитие");
}

void print_db_line(database_line* db_line){
    char dormitory_rights[20] = "Нет"; // Право на общежитие

    if (db_line->dormitory_rights) strcpy(dormitory_rights, "Да");

    printf("%-2d\t%-12ld\t%-10d\t%-9d\t%-9d\t%-12d\t%-14d\t%-16d\t%-25d\t%-17s\n", 
    db_line->idx, db_line->id, db_line->total_sum, db_line->chemistry_dvi, db_line->chemistry_ege, db_line->bio, db_line->math, db_line->rus, db_line->ind_adv, dormitory_rights);
}

void print_end_table(){
    printf("%-2s\t%-12s\t%-10s\t%-9s\t%-9s\t%-12s\t%-14s\t%-16s\t%-25s\t%-17s\n", 
    "--", "------------", "----------", "---------", "---------", "------------", "-------------", "---------------", "------------------------", "----------------");
}

void print_table(FILE* database){
    
    fseek(database, 0, SEEK_SET);

    print_header();

    database_line cur_db_line;

    while (fread(&cur_db_line, sizeof(database_line), 1, database)){
        print_db_line(&cur_db_line);
    }
    print_end_table();
}

void print_dorm_eligible_students_by_avg_grade_in_range(FILE* database, int a, int b){
    bool found = false;
    
    fseek(database, 0, SEEK_SET);
    
    database_line cur_db_line;
    
    while (fread(&cur_db_line, sizeof(database_line), 1, database)){
        int avg_grade = cur_db_line.total_sum / 5;

        if ((avg_grade >= a) && (avg_grade <= b) && (cur_db_line.dormitory_rights)) {
            print_db_line(&cur_db_line);
            if(!found) found = true; // возможно лучше убрать if?
        }
    }
    if (!found) printf("Таких не найдено\n");
}

void print_database_by_arr(FILE* database, elem* arr, int len_arr){
    
    print_header();
    database_line cur_db_line;
    elem cur_elem;

    for (int i = 0; i < len_arr; i++){
        cur_elem = arr[i];

        // printf("###%d - %d\n", cur_elem.number, cur_elem.key);

        int target_rows_number = cur_elem.number - 1;

        // Перемещаем указатель файла к нужной позиции
        fseek(database, target_rows_number * sizeof(database_line), SEEK_SET);

        // Считываем число из файла
        fread(&cur_db_line, sizeof(database_line), 1, database);
        print_db_line(&cur_db_line);
    }
    print_end_table();
}

int count_rows_in_file(FILE* file, size_t record_size) {
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);
    
    int count = file_size / record_size;
    return count;
}

void print_arr_elem(elem *arr, int len_arr){
    elem cur_elem;

    for (int i = 0; i < len_arr; i++){
        cur_elem = arr[i];

        printf("N%-2d - %-2d\n", cur_elem.number, cur_elem.key);
    }
}


void print_sorted_by_math(FILE* database)
{
    fseek(database, 0, SEEK_SET);

    elem arr_elem[count_rows_in_file(database, sizeof(database_line))];
    int len_arr = 0;

    database_line cur_db_line;
    elem cur_elem;

    while (fread(&cur_db_line, sizeof(database_line), 1, database)){
        cur_elem = (elem){cur_db_line.math ,cur_db_line.idx};
        arr_elem[len_arr] = cur_elem;
        len_arr++;
    }
    
    hoar_sort(arr_elem, len_arr);

    print_database_by_arr(database, arr_elem, len_arr);
}

void print_sorted_by_rus(FILE* database)
{
    fseek(database, 0, SEEK_SET);

    elem arr_elem[count_rows_in_file(database, sizeof(database_line))];
    int len_arr = 0;

    database_line cur_db_line;
    elem cur_elem;

    while (fread(&cur_db_line, sizeof(database_line), 1, database)){
        cur_elem = (elem){cur_db_line.rus ,cur_db_line.idx};
        arr_elem[len_arr] = cur_elem;
        len_arr++;
    }
    
    hoar_sort(arr_elem, len_arr);

    print_database_by_arr(database, arr_elem, len_arr);
}

void print_sorted_by_him_dvi(FILE* database)
{
    fseek(database, 0, SEEK_SET);

    elem arr_elem[count_rows_in_file(database, sizeof(database_line))];
    int len_arr = 0;

    database_line cur_db_line;
    elem cur_elem;

    while (fread(&cur_db_line, sizeof(database_line), 1, database)){
        cur_elem = (elem){cur_db_line.chemistry_dvi ,cur_db_line.idx};
        arr_elem[len_arr] = cur_elem;
        len_arr++;
    }
    
    hoar_sort(arr_elem, len_arr);

    print_database_by_arr(database, arr_elem, len_arr);
}

void print_sorted_by_him_ege(FILE* database)
{
    fseek(database, 0, SEEK_SET);

    elem arr_elem[count_rows_in_file(database, sizeof(database_line))];
    int len_arr = 0;

    database_line cur_db_line;
    elem cur_elem;

    while (fread(&cur_db_line, sizeof(database_line), 1, database)){
        cur_elem = (elem){cur_db_line.chemistry_ege ,cur_db_line.idx};
        arr_elem[len_arr] = cur_elem;
        len_arr++;
    }
    
    hoar_sort(arr_elem, len_arr);

    print_database_by_arr(database, arr_elem, len_arr);
}

void print_sorted_by_bio(FILE* database)
{
    fseek(database, 0, SEEK_SET);

    elem arr_elem[count_rows_in_file(database, sizeof(database_line))];
    int len_arr = 0;

    database_line cur_db_line;
    elem cur_elem;

    while (fread(&cur_db_line, sizeof(database_line), 1, database)){
        cur_elem = (elem){cur_db_line.bio ,cur_db_line.idx};
        arr_elem[len_arr] = cur_elem;
        len_arr++;
    }
    
    hoar_sort(arr_elem, len_arr);

    print_database_by_arr(database, arr_elem, len_arr);
}
