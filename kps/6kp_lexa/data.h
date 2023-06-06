#include <stdbool.h>

#define LEN 1000
#define HELPTEXT "\
Добро пожаловать в программу. Данная программа поможет получить данные из таблицы с данными поступающих!\n\
Для получения желаемого результата нужно ввести команду.\n\
Основные ключи:\n\
    \033[46m--help\033[m, получить справку по программе\n\
    \033[46m--rus\033[m, получить баллы по русскому языку и число\n\
    \033[46m--math\033[m, получить баллы по математике и число\n\
    \033[46m--inf\033[m, получить баллы по информатике и число\n\
    \033[46m--max\033[m, максимальная сумма баллов и число\n\
    \033[46m--min\033[m, минимальная сумма балов и число\n\
    \033[46m--all\033[m, распечатать всю таблицу и число\n\
    \033[46m--ts\033[m, вывести данные таблицы от одной суммы до другой, вводим ключ и через пробел два числа от и до\n\
    \n\
    Параметры --rus, --math, --inf можно использовать вместе!!! Остальные поотдельности!\n\
    Чтобы запустить программу, Вам необходимо написать: \033[46m./kp6 --help\033[m и вы получите данное сообщение.\n\
    Программа работает с бинарными файлами!\n\
Для получения данные из таблицы используйте ключи, например: \033[46m./kp6 test.bin --rus 90\033[m и Вам распечатает скрипт все строки таблицы, где есть 90 баллов по русскому языку\n\
"

typedef struct{
    int id;
    char snils[15];
    int total_sum;
    int subj_sum;
    int math;
    int inf;
    int rus;
    int ind_adv;
    bool docs;
    bool agree;
    bool commun;
} database_line;

typedef struct {
    bool rus;
    bool math;
    bool inf;
    bool all;
    bool max;
    bool min;
    bool ts;
    bool help;
} Key;

void print_line(database_line *line);
bool filter_table(database_line *line, Key *key, int from, int to);
void init_key(Key *key);
bool is_number(char *arg);
bool check_compatibility(Key *key);
bool check_count_of_numbers(Key *key, int num_count);