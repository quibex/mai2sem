
#include "mylist.h"
#include "iterator.h"
#include "stdlib.h"
#include "stdbool.h"

iterator iter_begin(list *list) {
    iterator iter;
    iter.cur = list->terminator->next;
    iter.list = list;
    return iter;
}

unsigned int iter_val(iterator *iter){
    return iter->cur->val;
}

bool iter_not_end(iterator *iter) {
    if (iter->cur == iter->list->terminator) return false;
    return true;
}

void iter_next(iterator *iter) {
    iter->cur = iter->cur->next;
}

void iter_prev(iterator *iter) {
    iter->cur = iter->cur->prev;
}

void iter_delete(iterator *iter){
    node* node = iter->cur;
    iter_prev(iter);
    delete_node(node);
    iter->list->len--;
}