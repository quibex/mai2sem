#include "manga.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int uint;

void help(){
    printf("Parameters:\n"
       " -p (print)\n"
       "   -y 2222 (all book of this year)\n"
       "   -a AAAA (all books by this author)\n"
       "   -n BBBB (book with this title)\n"
       " -lr 9.999 (number of books with rating less than this)\n"
       " -mr 1.111 (number of books with rating more than this)\n"
       " -avg (average rating of books)\n"
       " -uniq (number of unique authors)\n");
}

void print_header(){
    printf("%-4s\t%-30s\t%-20s\t%-10s\t%-6s\n", "ID", "Name", "Author", "Year", "Rating");
}

void print_manga(Manga * book){
    printf("%-4d\t%-30s\t%-20s\t%-10d\t%-6lf\n", book->id, book->name, book->author, book->year, book->rating);
}

void print_ender(){
    printf("%-4s\t%-30s\t%-20s\t%-10s\t%-6s\n", "-----", "------------------------------", "--------------------", "-------------", "--------");
}

void print_file(FILE * file) {
    Manga book;
    print_header();
    while(fread(&book, sizeof(Manga), 1, file)){
        print_manga(&book);
        
    }
    print_ender();

    fclose(file);
}

void search_year(int year, FILE * file){
    Manga book;
    print_header();
    while(fread(&book, sizeof(Manga), 1, file)){
        if(year == book.year){
            print_manga(&book);
        }
    }
    print_ender();

    fclose(file);
}

void search_author(char * author, FILE * file){
    Manga book;
    print_header();
    while(fread(&book, sizeof(Manga), 1, file)){
        if(strcmp(author, book.author) == 0 ){
            print_manga(&book);
        }
    }
    print_ender();

    fclose(file);
}

void search_name(char * name, FILE * file){
    Manga book;
    print_header();
    while(fread(&book, sizeof(Manga), 1, file)){
        if(strcmp(name, book.name) == 0 ){
            print_manga(&book);
        }
    }
    print_ender();

    fclose(file);
}

void less_rating(double rating, FILE * file){
    Manga book;
    int count = 0;
    
    while(fread(&book, sizeof(Manga), 1, file)){
        if(book.rating < rating){
            count++;
        }
    }
    
    printf("The number of books with rating less than %lf : %d\n", rating, count);

    fclose(file);

}

void more_rating(double rating, FILE * file){
    Manga book;
    int count = 0;
    
    while(fread(&book, sizeof(Manga), 1, file)){
        if(book.rating > rating){
            count++;
        }
    }
    
    printf("The number of books with rating more than %lf : %d\n", rating, count);

    fclose(file);

}

void average_rating( FILE * file){
    Manga book;
    double summ = 0;
    int count = 0;
    
    while(fread(&book, sizeof(Manga), 1, file)){
        summ += book.rating;
        count++;
    }
    
    printf("The average rating of books : %lf\n", summ/count);

    fclose(file);

}

uint code_string(char* str) {
    uint code = 0;
    int c;

    while ((c = *str++) != '\0') {
        code ^= c;
    }

    return code;
}

void unique_author( FILE * file){
    Manga book;
    int count = 0;
    int size = 100;
    
    char** table = malloc(size * sizeof(char*));

    while(fread(&book, sizeof(Manga), 1, file)) {
        int id = code_string(book.author) % size;
        while (table[id] != NULL && strcmp(table[id], book.author) != 0) {
            id = (id + 1) % size;
        }
        if (table[id] == NULL) {
            table[id] = strdup(book.author);
            count++;
        }
    }
    
    printf("The number of unique authors: %d\n", count);

    for (int i = 0; i < size; i++) {
        if (table[i] != NULL) {
            free(table[i]);
        }
    }
    free(table);

    fclose(file);

}

int main(int argc, char* argv[]) {
    
    FILE* file = fopen("manga_bin", "r");
    if (!file) {
        printf("Cannot open file\n");
        exit(1);
    }
    double rating;
    int year;
    if (argc == 1) {
        print_file(file);
        return 0;
    }
    else if (argc == 2){
        if (strcmp(argv[1], "-avg") == 0){
            average_rating(file);
        }
        else if (strcmp(argv[1], "-uniq") == 0){
            unique_author(file);
        }
        else if (strcmp(argv[1], "-help") == 0){
            help();
        }
        else{
            printf("Wrong parameter\n");
            exit(1);
        }
    }
    else if (argc == 3){
        if ((strcmp(argv[1], "-lr") == 0) && (sscanf(argv[2], "%lf", &rating) == 1 )){
            less_rating(rating, file);
        }
        else if ((strcmp(argv[1], "-mr") == 0) && (sscanf(argv[2], "%lf", &rating) == 1)){
            more_rating(rating, file);
        }
        else{
            printf("Wrong parameter\n");
            exit(1);
        }
    }
    else if (argc == 4){
        if (strcmp(argv[1], "-p") == 0){
            if ((strcmp(argv[2], "-y") == 0) && (sscanf(argv[3], "%d", &year) == 1)){
                search_year(year, file);
            }
            else if (strcmp(argv[2], "-a") == 0){
                search_author(argv[3], file);
            }
            else if (strcmp(argv[2], "-n") == 0){
                search_name(argv[3], file);
            }
            else{
                printf("Wrong parameter\n");
                exit(1);
            }
        }
        else{
            printf("Wrong parameter\n");
            exit(1);
        }
    }
    else{
        printf("Wrong number of parameters\n");
        exit(1);
    }
    return 0;
}