#pragma once
#include "borders_stack.h"
#include "stdlib.h"


typedef struct
{
    int key;
    int number;
} elem;

borders hoar_partition(elem *arr, int l, int r, elem b);
void hoar_sort(elem *arr, int size);