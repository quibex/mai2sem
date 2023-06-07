#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_funcs.h"
#include "to_binfile.h"

#define db "db.bin"

int main(int argc, char* argv[]){
    
    if ((argc <= 1) || (argc > 4)){
        printf("Нет необходимого количества аргументов, ознакомьтесь с инструкцией c помощью ключа -h");
        exit(1);
    } else if (strcmp(argv[1], "-h") == 0)
    {
        printf("Вам необходимо ввести название обрабатываемого файла,\n а также ключи: \n");
        printf("--tobin   перевод файла в бинарный, при этом укажите после ключа название будущего бинарного файла \n");
        printf("--ptest и число p, чтобы определить какие абитуриенды набрали суммарное число баллов равное p, указав небинарный файл (или --ptestbin в противном случае)\n ");
        printf("-h    получить инструкцию\n");
        exit(0); //завершение работы программы без ошибок
    }
    
    if  ((strcmp(argv[2], "--tobin") == 0) && (argc < 5)){
        
        file_bin(argv[1], argv[3]);
        exit(0); 
    }
    
    if (argv[3]!=NULL){
        if ((strcmp(argv[2], "--ptest") == 0) || (strcmp(argv[2], "--ptestbin") == 0)){
            
            FILE* database = NULL; //database
            if (strcmp(argv[2], "--ptest") == 0){
                file_bin(argv[1], db); //
                database = fopen(db, "rb"); //fopen() возвращает указатель на структуру типа FILE
            }//функция возвращает ненулевой указатель, если открытие прошло успешно; и возвращает NULL, если произошла ошибка
            
            if (strcmp(argv[2], "--ptestbin") == 0){
            database = fopen(argv[1], "rb");//открываем бинарный файл для чтения
            }
            
            if (database == NULL) { //проверка на ошибку открытия файла
                printf("Cannot open database file\n");
                fclose(database);
                exit(2);
            }
            print_table(database); 
            printf("\n\n");
            print_abiturients_with_p_total_sum(database, atoi(argv[3])); //+преобразование строки в число типа int
            
        } 
    } else {
        printf("Error: No such parameters keys --ptest or --ptestbin\n"); 
        exit(1);
    }
    
    
    return 0;
}
