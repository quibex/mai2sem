#pragma once 
#include <stdbool.h> 

typedef struct{
    int idx;//номер строки таблицы
    __int64_t id;//id абитуриента
    __int64_t SNILS; //СНИЛС
    int id2; //доп номер для СНИЛСа
    int year; //год рождения
    bool citizenship; //гражданство
    int math; //баллы ЕГЭ по математике
    int inf_or_physics; //баллы ЕГЭ по информатике или физике
    int rus; //баллы ЕГЭ по русскому
    int additional_p; //доп баллы
    int total_sum; //общая сумма баллов ЕГЭ
} database_line;

void print_db_line(database_line* b); //печать строки таблицы
void print_table(FILE* database); //печать таблицы
void print_abiturients_with_p_total_sum(FILE* database, int a); //печать строк таблицы, удовлетворяющих условию равенстсва введенному значению

