#include <stdio.h>
#include <stdbool.h>
#include "data.h"
#include <string.h>

static bool in_range(int i, int start, int end) {
    return i >= start && i <= end;
}

static bool ge(int i, int a) {
    return i >= a;
}

static bool g(int i, int a) {
    return i > a;
}

static bool le(int i, int a) {
    return i <= a;
}

static bool l(int i, int a) {
    return i < a;
}

bool is_number(char *arg) {
    for (int i = 0; arg[i] != '\0'; i++) {
        if (arg[i] < '0' || arg[i] > '9') {
            return false;
        }
    }
    return true;
}

// проверяем на совместимость ключи
bool check_compatibility(Key *key) {
    return ((key->rus || key->math || key->inf) && (key->ts || key->min || key->max || key->all)) || (key->ts && (key->min || key->max || key->all)) || (key->min && (key->max || key->all)) || key->max && key->all;
}

// проверяем, что кол-во параметров введено правильно
bool check_count_of_numbers(Key *key, int num_count) {
    return ((key->rus || key->math || key->inf) && num_count != 1) || (key->ts && num_count != 2) || (key->all && num_count != 0) || (key->max && num_count != 0) || (key->min && num_count != 0);
}

void print_line(database_line *line) {
    printf("|%4d|", line->id);
    printf("%14s|", line->snils);
    printf("%11d|", line->total_sum);
    printf("%10d|", line->subj_sum);
    printf("%6d|", line->math);
    printf("%5d|", line->inf);
    printf("%5d|", line->rus);
    printf("%3d|", line->ind_adv);
    printf(line->docs ? "Оригинал|" : "   Копия|");
    printf(line->agree ? "     Да|" : "    Нет|");
    printf(line->commun ? "      Да|\n" : "     Нет|\n");
}

// булевая фнкнкция -> проверяет подходит ли эта строка
bool filter_table(database_line *line, Key *key, int from, int to) {
    return (!key->rus || ge(line->rus, from)) && (!key->math || ge(line->math, from)) && (!key->inf || ge(line->inf, from)) && (!key->ts || in_range(line->total_sum, from, to)) || key->all;
}

void init_key(Key *key) {
    key->all = false;
    key->inf = false;
    key->math = false;
    key->max = false;
    key->min = false;
    key->rus = false;
    key->ts = false;
    key->help = false;
}