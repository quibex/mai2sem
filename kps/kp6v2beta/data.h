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

typedef struct {
    bool help;
    bool min_math;
    bool min_rus;
    bool min_bio;
    bool min_him_dvi;
    bool min_him_ege;
    bool max_math;
    bool max_rus;
    bool max_bio;
    bool max_him_dvi;
    bool max_him_ege;
    bool avg_in_range;
    bool tobin;
    bool data_have;
} key;

void init_key(key* k);
void print_header();
void print_db_line(database_line* db_line);
void print_end_table();
void print_table(FILE* database);
void print_dorm_eligible_students_by_avg_grade_in_range(FILE* database, int a, int b);