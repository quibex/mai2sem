#include <stdbool.h>
#include "vector2.h"
#include <stdio.h>

// typedef struct
// {
//     double key;
//     char data[100];
// } elem ;

void merge(dbl_vec *p1, dbl_vec *p2, dbl_vec *p3, dbl_vec *p4)
{

    dbl_vec *cur_arr = p1;
    // printf("=1= p1: %d ; p2: %d; p3: %d; p4: %d\n", p1->size, p2->size,  p3->size,  p4->size);

    while (!dbl_vec_is_empty(p3) && !dbl_vec_is_empty(p4))
    {
        // printf("%lf <= %lf == %lf\n", dbl_vec_head(p3).key, dbl_vec_head(p4).key, dbl_vec_tail(cur_arr).key);
        if (dbl_vec_head(p3).key <= dbl_vec_head(p4).key)
        {
            dbl_vec_push_back(cur_arr, dbl_vec_pop_front(p3));
        }
        else
        {
            dbl_vec_push_back(cur_arr, dbl_vec_pop_front(p4));
        }
        if ((dbl_vec_tail(cur_arr).key > dbl_vec_head(p3).key) && (dbl_vec_tail(cur_arr).key > dbl_vec_head(p4).key))
        {
            if (cur_arr == p2)
            {
                cur_arr = p1;
            }
            else
            {
                cur_arr = p2;
            }
        }
    }
    while (!dbl_vec_is_empty(p3))
    {
        dbl_vec_push_back(cur_arr, dbl_vec_pop_front(p3));
        if ((dbl_vec_tail(cur_arr).key > dbl_vec_head(p3).key))
        {
            if (cur_arr == p2)
            {
                cur_arr = p1;
            }
            else
            {
                cur_arr = p2;
            }
        }
    }
    while (!dbl_vec_is_empty(p4))
    {
        dbl_vec_push_back(cur_arr, dbl_vec_pop_front(p4));
        if ((dbl_vec_tail(cur_arr).key > dbl_vec_head(p4).key))
        {
            if (cur_arr == p2)
            {
                cur_arr = p1;
            }
            else
            {
                cur_arr = p2;
            }
        }
    }

    // printf("=2= p1: %d ; p2: %d; p3: %d; p4: %d\n\n", p1->size, p2->size,  p3->size,  p4->size);
}

void merge_sort(dbl_vec *p1)
{
    dbl_vec p2, p3, p4;
    dbl_vec_init(&p2);
    dbl_vec_init(&p3);
    dbl_vec_init(&p4);
    dbl_vec *cur_arr = &p3;

    dbl_vec_push_back(cur_arr, dbl_vec_pop_front(p1));

    while (!dbl_vec_is_empty(p1))
    {
        if (dbl_vec_head(p1).key >= dbl_vec_tail(cur_arr).key)
        {
            dbl_vec_push_back(cur_arr, dbl_vec_pop_front(p1));
        }
        else
        {
            if (cur_arr == &p3)
                cur_arr = &p4;
            else
                cur_arr = &p3;
            dbl_vec_push_back(cur_arr, dbl_vec_pop_front(p1));
        }
    }

    while ((!dbl_vec_is_empty(&p2) || !dbl_vec_is_empty(&p3) || !dbl_vec_is_empty(&p4))) // пока не отсортирован
    {
        merge(&p3, &p4, p1, &p2);
        merge(p1, &p2, &p3, &p4);
    }
}

double key_cmp(elem el1, elem el2)
{
    return el1.key - el2.key;
}

int lower_bound(dbl_vec *elem_vec, elem x)
{
    int i = 0, j = dbl_vec_get_size(elem_vec) - 1;

    bool found = false;
    int found_el_idx = -1;
    while (i <= j)
    {
        int mid_idx = i + (j - i) / 2;

        if (dbl_vec_get_el(elem_vec, mid_idx).key == x.key)
        {
            found = true;
            found_el_idx = mid_idx;
            j = mid_idx - 1;
        }

        if (dbl_vec_get_el(elem_vec, mid_idx).key > x.key)
            j = mid_idx - 1;

        if (dbl_vec_get_el(elem_vec, mid_idx).key < x.key)
            i = mid_idx + 1;
    }
    return found_el_idx;
}

void clean_input()
{
    char s;
    while (s != '\n')
        s = getchar();
    fflush(stdin);
}

int main()
{
    dbl_vec vec_elem;
    dbl_vec_init(&vec_elem);

    int n;
    printf("Введите кол-во элементов: ");
    if (scanf("%d", &n) != 1){
        printf("ban\n");
        exit(2);
    }
    printf("Введите нормальные элементы (example: 4 aboba): ");
    while (n != 0)
    {
        elem current;
        if(scanf("%lf %s", &current.key, current.data) != 2){ 
            printf("Вы ввели говно элемент!!!\n");
            continue;
        };
        dbl_vec_push_back(&vec_elem, current);
        n--;
    }

    merge_sort(&vec_elem);

    // for (int i = 0; i < dbl_vec_get_size(&vec_elem); i++)
    // {
    //     elem ELL = dbl_vec_get_el(&vec_elem, i);
    //     printf("key: %lf, value: %s\n", ELL.key, ELL.data);
    // }

    while (1)
    {
        printf("Введите ключ искомого элемента(вещественное число):\n");
        elem cur;
        scanf("%lf", &cur.key);
        int lower_bound_result = lower_bound(&vec_elem, cur);
        if (lower_bound_result != -1)
        {
            printf("Надейнный элемент имеет индекс %d и значение %s\n", lower_bound_result, cur.data);
        }
        else
        {
            printf("Элемент не найден!\n");
        }
        // sleep(1);
    }
    return 0;
}