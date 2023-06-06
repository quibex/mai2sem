#include <stdbool.h>
#include "vector2.h"
#include <stdio.h>

int main()
{
    dbl_vector a;
    dbl_init(&a);
    dbl_set_size(&a, 10);
    for (int i = 0; i < 6; i++)
    {
        dbl_pop_front(&a);
    }
    for (int i = 0; i < 2; i++)
    {
        dbl_push_back(&a, 5);
    }
    dbl_set_size(&a, 10);
    for (int i = 0; i < 6; i++)
    {
        dbl_pop_front(&a);
    }
    int size = dbl_get_size(&a);
    for (int i = 0; i < size; i++)
    {
        double el = dbl_get_el(&a, i);
        printf("%lf \n", el);
    }
}