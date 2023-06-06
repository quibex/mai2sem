
#include <stdio.h>
#include "borders_stack.h"
#include "hoar_sort.h"

int mid(int a, int b, int c) {
    if ((a < b && b < c) || (c < b && b < a)) {
        return b;
    } else if ((b < a && a < c) || (c < a && a < b)) {
        return a;
    } else {
        return c;
    }
}

void check_correct_int(char* a){
    
}

static elem calc_pivot(elem *arr, int i, int j)
{
    int random = rand() % 3; // генерируем случайное число от 0 до 2

    elem i_j_hoarult;
    switch (random)
    {
    case 0:
        i_j_hoarult = arr[i];
        break;
    case 1:
        i_j_hoarult = arr[(i + j) / 2];
        break;
    case 2:
        i_j_hoarult = arr[j];
        break;
    }
    return i_j_hoarult;
}

static void swap(elem *arr, int i, int j)
{
    elem c = arr[i];
    arr[i] = arr[j];
    arr[j] = c;
}

borders hoar_partition(elem *arr, int l, int r, elem b)
{
    int i = l, j = r;
    do
    {
        while (arr[i].key > b.key) // сортировка в обратном порядке
            i++;
        while (arr[j].key < b.key) // сортировка в обратном порядке
            j--;
        if (i <= j)
        {
            swap(arr, i, j);
            i++;
            if (j > 0)
                j--;
        }
    } while (i <= j);
    borders i_j_hoar = {i, j};

    return i_j_hoar;
}

void hoar_sort(elem *arr, int size)
{
    borders_stack st;
    borders_stack_init(&st);

    // borders brdr = {0, size-1};
    // borders_stack_push(&st, brdr);
    borders_stack_push(&st, (borders){0, size - 1});

    while (!borders_stack_is_empty(&st))
    {
        // printf("aefse");
        borders cur_border = borders_stack_pop(&st);
        while (cur_border.R > cur_border.L)
        {

            elem pivot = calc_pivot(arr, cur_border.L, cur_border.R);

            borders i_j_hoar = hoar_partition(arr, cur_border.L, cur_border.R, pivot);

            if (i_j_hoar.L < cur_border.R)
            {
                borders r_half = {i_j_hoar.L, cur_border.R};
                borders_stack_push(&st, r_half);
            }
            cur_border.R = i_j_hoar.R;
        }
    }
}