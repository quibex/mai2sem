
#include <stdio.h>
#include <stdlib.h>
#include "mylist.h"
#include "iterator.h"


void init(list *list) {
    list->terminator = malloc(sizeof(node));
    list->terminator->next = list->terminator->prev = list->terminator;
    list->last = list->terminator;
    list->len = 0;
}


void insert(list *list, unsigned int val) {
    node *new_node = malloc(sizeof(node));
    new_node->val = val;

    new_node->prev = list->last;
    new_node->next = list->terminator;

    list->terminator->prev = new_node;
    list->last->next = new_node;

    list->last = new_node;
    list->len++;
}

void delete_by_val(list *list, unsigned int val) {
    if (list->len == 0) return; // если список пустой 

    node* elem = NULL;
    // поиск нужного элемента
    for (iterator iter = iter_begin(list); iter_not_end(&iter); iter_next(&iter)){
        if (iter_val(&iter) == val){
            elem = iter.cur;
            break;
        }
    };

    if (elem == NULL) return; // если элемент не найден

    elem->prev->next = elem->next; 
    elem->next->prev = elem->prev;
    free(elem);
    list->len--;
}

void delete_node(node* node) {

    node->prev->next = node->next; 
    node->next->prev = node->prev;
    free(node);
}

void print_list(list *list) {
    for (iterator iter = iter_begin(list); iter_not_end(&iter); iter_next(&iter)) {
        printf("%u ", iter_val(&iter));
    }
    printf("\n");
}

int length(list *list) {
    return list->len;
}

void delete_range(list *list, unsigned int min, unsigned int max) {
    for (iterator iter = iter_begin(list); iter_not_end(&iter); iter_next(&iter)) {
        unsigned int elem_val = iter_val(&iter);
        if (( elem_val >= min) && (elem_val <= max)) {
            iter_delete(&iter);
        }
    }
}

void destroy(list *list){
    
    for (iterator iter = iter_begin(list); iter_not_end(&iter); iter_next(&iter)) {
        iter_delete(&iter);
    }
    free(list->terminator); 
}





