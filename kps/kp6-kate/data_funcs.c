#include <stdio.h>
#include <string.h>
#include "data_funcs.h"

void print_db_line(database_line* b){ //вывести строку таблицы
    char citizenship[100] = "Гражданин РФ"; 
    if (b->citizenship) strcpy(citizenship, "Гражданка РФ"); //копирование "Гражданка РФ" в citizenship
        printf("%-10d\t%-10ld\t%-10ld\t%-2d\t%-9d\t%-15s\t%-15d\t%-15d\t%-15d\t%-10d\t%-10d\n",
    b->idx, b->id, b->SNILS, b->id2, b->year, citizenship, b->math, b->inf_or_physics, b->rus, b->additional_p, b->total_sum);
}//передаем ссылку на объект

void print_table(FILE* database){
    
    fseek(database, 0, SEEK_SET); //перемещения позиции указателя файла в начало (SEEK_SET)

    printf("%-10s\t%-10s\t%-10s\t%-2s\t%-9s\t%-15s\t%-15s\t%-15s\t%-15s\t%-10s\t%-10s\n", 
    "№", "Рег.номер", "СНИЛС/УКП","idСНИЛС", "Год рождения", "Гражданство", "Математика", "Инф/физика", "Русский язык ЕГЭ", "Индивидуальные достижения", "Общая сумма баллов");

    database_line b;
    while (fread(&b, sizeof(database_line), 1, database)){
       print_db_line(&b);
    }
    
}


void print_abiturients_with_p_total_sum(FILE* database, int a){
    bool found = false;
    fseek(database, 0, SEEK_SET);
    database_line b;
    while (fread(&b, sizeof(database_line), 1, database)){
        int total = b.total_sum;
        if (total == a) {
            print_db_line(&b);
            found = true;
        }
    }
    if (!found) printf("Не найдено абитуриентов с такой суммой баллов\n");
}
