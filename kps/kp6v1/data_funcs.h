#pragma once 
#include <stdbool.h> 


typedef struct{
    int idx;
    __int64_t id;
    int total_sum;
    int chemistry_dvi;
    int chemistry_ege;
    int bio;
    int math;
    int rus;
    int ind_adv;
    bool dormitory_rights;
} database_line;

void print_header();
void print_db_line(database_line* db_line);
void print_end_table();
void print_table(FILE* database);
void print_dorm_eligible_students_by_avg_grade_in_range(FILE* database, int a, int b);
void print_sorted_by_math(FILE* database);
void print_sorted_by_rus(FILE* database);
void print_sorted_by_him_dvi(FILE* database);
void print_sorted_by_him_ege(FILE* database);
void print_sorted_by_bio(FILE* database);