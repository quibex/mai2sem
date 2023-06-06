// Реализация цепного представления внутри массива
// Индекс == адрес

#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

#define MIN_CAP 10
 
typedef struct {
    int next_idx;
    double val;
} node;
 
 
typedef struct {
    int first_idx;
    int last_idx;
    int cap;
    node * buf;
    int size;
    int first_empty_idx;
 
} list;
 
typedef struct {
    list * lst;
    int prev_idx;
} iter;
 
void init_list(list * list){
    list->size = 0;
    list->first_idx = 0;
    list->last_idx = 0;
    list->buf = malloc(list->cap * sizeof(node));
} 
 
// статик, тк юзер не видит эту функцию, аналог alloc()
static int alloc_node(list * lst) {
    if(lst->first_empty_idx == -1) {
        increase_buff(lst);
    } 
 
    int new_elem_idx = lst->first_empty_idx;
    lst->first_empty_idx = lst->buf[lst->first_empty_idx].next_idx;
 
    return new_elem_idx;
}
 
 
void increase_buff(list * lst) {
    int old_cap = lst->cap;
    lst->cap *= 2;
    if(lst->cap < MIN_CAP) {
        lst->cap = MIN_CAP;
    }
    lst->buf = realloc(lst->buf, lst->cap * sizeof(node));  // Тут возможна утечка памяти, если реаллок не смогет выделить память => он вернет NULL, поэтому надо было бы обработать этот случай отдельно, но это долго
 
    for(int i = old_cap; i < lst->cap; i++) {   // Связываем новые ячейки между собой
        lst->buf[i].next_idx = i + 1;
    }
 
    lst->buf[lst->cap - 1].next_idx = lst->first_empty_idx;  // Ссылаем последнюю выделенную на какую-то из оставшихся
    lst->first_empty_idx = old_cap;
}
 
 
// Аналог free()
void free_node(list * lst, int idx) {
    lst->buf[idx].next_idx = lst->first_empty_idx;
    lst->first_empty_idx = idx;
}
