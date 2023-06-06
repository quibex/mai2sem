#include <stdlib.h>
// On C++
// for (auto it = vec.begin(); it != vec.end(); it++){
//     printf("%lf\n", *it);
// }


typedef struct node node;

struct node
{
    node *next;
    double val;
};

typedef struct {
    node *first;
    node *last;
    int size;
} list;

typedef struct {
    node *prev;
    list *list;
} iter;

iter iter_begin(list *e){
    iter it;
    it.prev = NULL;
    it.list = e;
    return it;
}

iter iter_end(list *e){
    iter it;
    it.prev = e->last;
    it.list = e;
    return it;
}
 
void iter_inc(iter *it){
    if (it->prev == NULL){
        it->prev = it->list->first;
    } else {
        it->prev = it->prev->next;
    }
}

double iter_get_val(iter *it){
    if (it->prev == NULL){
        return it->list->first->val;
    }
    return it->prev->next->val;
}

void iter_remove(iter *it){
    node * elem;
    if (it->prev = NULL){
        elem = it->list->first;
        it->list->first = it->list->first->next;
        if (it->list->first == NULL){
            it->list->last = NULL;
        }
    } else if (it->prev->next->next == NULL){
        elem = it->prev->next;
        it->prev->next = NULL;
        it->list->last = it->prev;
    } else {
        elem = it->prev->next;
        it->prev->next = it->prev->next->next;
    }
    free(elem);
    it->list->size--;
}

void iter_add(iter *it, double val){
    node *elem = malloc(sizeof(node));
    elem->val = val;
    if (it->prev == NULL){
        elem->next =it->list->first;
        it->list->first = elem;
        if (it->list->last == NULL){
            it->list->last = elem;
        }
    } else if (it->prev->next == NULL){
        elem->next == NULL;
        it->list->last = elem;
        it->prev->next = elem;
    } else {
        elem->next = it->prev->next;
        it->prev->next = elem;
    }
    it->prev = elem;
    it->list->size++;
}

void list_init(list *e){
    e->first = NULL;
    e->last = NULL;
    e->size = 0;
}

void list_destroy(list *e){

}
