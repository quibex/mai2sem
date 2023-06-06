 #include <stdlib.h>
#include <stdbool.h>


typedef struct node node;

struct node
{
    node* next;
    double val;
};

typedef struct 
{
    node *first;
    node *last;
    int len;
    // int version; //Для того, чтобы один из двух итераторов, 
    // применяемых к одному списку не поломал другой
} list;

typedef struct iter
{
    list *lst;
    node *prev;
    // int list_version;
} iter;

iter iter_begin(list* l)
{
    iter it;
    it.prev = NULL;
    it.lst = l;
    return it;
}

iter iter_end(list *l)
{
    iter it;
}

bool iter_eq(iter it1, iter it2)
{
    return (it1.prev->next == it2.prev->next) && (it1.lst == it2.lst);
}

iter inc(iter *it)
{
    if(it->prev==NULL)
    {
        it->prev=it->lst->first;
        return;
    }
    it->prev = it->prev->next;
}

double iter_getval(const iter it)
{
    if(it.prev==NULL)
    {
        return it.lst->first->val;
    }
    return it.prev->next->val;
}


void iter_setval(iter *it, double value)
{
    if(it->prev==NULL)
    {
        it->lst->first->val = value;
        return;
    }
    it->prev->next->val = value;
}

void iter_remove(iter *it)
{
 
    node *to_remove = it->prev->next;
    if(it->prev==NULL)
    {
        to_remove = it->lst->first;
        it->lst->first = it->lst->first->next;
        if(it->lst->first == NULL)
        {
            it->lst->last = NULL;
        }
    }
    else if(it->prev->next->next == NULL)
    {
        to_remove = it->prev->next;
        it->prev->next = NULL;
        it->lst->last = it->prev;
    }
    else
    {
        to_remove = it->prev->next;
        it->prev->next = it->prev->next->next;
    }
    free(to_remove);
    it->lst->len--;
    
}


void iter_add(iter *it, double value)
{
    node *new_elem = malloc(sizeof(node));
    new_elem->val = value;
    if(it->prev == NULL) //Ситуация добавления в начало
    {
        new_elem->next = it->lst->first;
        it->lst->first = new_elem;
        if(it->lst->last == NULL) //Если список пустой, изменим указатель на конец
        {
            it->lst->last = new_elem;
        }
    }
    else if(it->prev->next == NULL)
    {
        new_elem->next = NULL;
        it->lst->last = new_elem;
        it->prev->next = new_elem;
    }
    else
    {
        new_elem->next = it->prev->next;
        it->prev->next = new_elem;
    }
    it->lst->len++;
}

/*
for(auto it=vec.begin();it!=vec.end();it++)
{

}
*/

void list_init(list *l)
{
    l->first = NULL;
    l->last = NULL;
    l->len = 0;
}


