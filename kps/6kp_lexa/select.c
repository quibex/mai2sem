#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "data.h"


int main(int argc, char *argv[]){

    if (!strcmp(argv[1], (const char *)"--help")) {
        fprintf(stdout, "%s\n", HELPTEXT);
        exit(0);
    }
    
    char buf[LEN];
    Key key;
    int max_sum = 0;
    int min_sum = 600;
    
    init_key(&key); // пришлось добавить, чтобы определите все ключи на старте 0

    int num_count = 0;
    // обработка введенных полей
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], (const char *)"--rus")) {
            key.rus = true;
        } else if (!strcmp(argv[i], (const char *)"--math")) {
            key.math = true;
        } else if (!strcmp(argv[i], (const char *)"--inf")) {
            key.inf = true;
        } else if (!strcmp(argv[i], (const char *)"--all")) {
            key.all = true;
        } else if (!strcmp(argv[i], (const char *)"--ts")) {
            key.ts = true;
        } else if (!strcmp(argv[i], (const char *)"--max")) {
            key.max = true;
        } else if (!strcmp(argv[i], (const char *)"--min")) {
            key.min = true;
        } else if (!strcmp(argv[i], (const char *)"--help")) {
            fprintf(stdout, "%s\n", HELPTEXT);
            exit(0);
        } else if (argv[i][0] == argv[i][1] || argv[i][0] == '-') {
            fprintf(stderr, "\033[41mНеизвестный флаг \"%s\"!\033[m\n", argv[i]);
            exit(1);
        } else if (is_number(argv[i])) {
            num_count += 1;
        }
    }

    if (check_compatibility(&key)) {
        fprintf(stderr, "\033[41mВы ввели несовместимые параметры! Обратитесь к справке --help\033[m\n");
        exit(1);
    }

    if (check_count_of_numbers(&key, num_count)) {
        fprintf(stderr, "\033[41mКоличество передаваемых чисел не поддерживается вызываемым ключом!\033[m\n");
        exit(1);
    }

    FILE *input = fopen(argv[1], "rb");

    if (input == NULL) {
        fprintf(stderr, "\033[41mНе удалось окрыть файл!\033[m\n");
        exit(1);
    } else {
        fprintf(stdout, "\033[42mФайл успешно окрыт!\033[m\n");
    }

    printf("| id |    snils      | total sum | subj sum | math | inf | rus | + |  docs  | agree | commun |\n");

    while (1) {

        int num = fread(buf, sizeof(char), sizeof(database_line), input);
        if (num == 0) {
            break;
        }

        database_line *dbl = (database_line *)buf;
        /*
            В буфер записываются байты. Сама переменная буфер - это константный указатель.
            Константный указатель - это не меняющийся указатель. Теперь данные буфера это данные структуры
        */

        if (max_sum < dbl->total_sum) {
            max_sum = dbl->total_sum;
        }

        if (min_sum > dbl->total_sum) {
            min_sum = dbl->total_sum;
        }

        // Вызов фукций для вывода таблицы
        int from;
        int to;
        if (key.ts) {
            from = atoi(argv[argc - 2]);
            to = atoi(argv[argc - 1]);
        } else {
            from = atoi(argv[argc - 1]);
            to = 0;
        }
        int status = filter_table(dbl, &key, from, to);
        if (status && key.max == 0 && key.min == 0) {
            print_line(dbl);
        }
    }

    if (key.max) {
        printf("Максимальная сумма баллов: %d\n", max_sum);
    } else if (key.min) {
        printf("Минимальная сумма баллов: %d\n", min_sum);
    }
    
    fclose(input);
    fprintf(stdout, "\033[42mФайл успешно закрыт!\033[m\n");
    return 0;
}