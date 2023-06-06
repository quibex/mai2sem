#pragma once

#include "mylist.h"
#include <stdbool.h>


typedef struct {
    node* cur;
    list* list;
} iterator;

iterator iter_begin(list *list);
bool iter_not_end(iterator *iter);
void iter_next(iterator *iter);
void iter_prev(iterator *iter);
unsigned int iter_val(iterator *iter);
void iter_delete(iterator *iter);