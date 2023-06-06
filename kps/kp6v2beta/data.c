#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

// Найти абитуриентов с средной оценкой в указанном диапозоне с правом на общежитие 
// Min и Max по значениям

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
    if (!found) printf("Не найдено\n");
}

void init_key(key* k){
    k->help = false;
    k->avg_in_range = false;
    k->tobin = false;
    k->data_have = false;
    k->max_bio = false;
    k->max_rus = false;
    k->max_math = false;
    k->max_him_dvi = false;
    k->max_him_ege = false;
    k->min_bio = false;
    k->min_rus = false;
    k->min_math = false;
    k->min_him_dvi = false;
    k->min_him_ege = false;
}