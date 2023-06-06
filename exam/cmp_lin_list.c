
#define NULL (void*)0

typedef struct node
{
    int val;
    node *next;
} node ;


typedef struct list
{
   int size;
   node *head;
} list;


int cmp_list(list *l1, list *l2)
{
    while ((l1 != NULL) && (l2 != NULL) && (l1->val == l2->val))
    {
        l1 = l1->next;
        l2 = l2->next;
    }
    return l1->val - l2->val;
}