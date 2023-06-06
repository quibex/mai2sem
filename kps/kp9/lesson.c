#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct key
{
    char k1[10];
    int k2;
} key;

int compare(key* a, key* b)
{
    int cmp = strcmp(a->k1, b->k1);
    if (cmp != 0){
        return cmp;
    }
    return a->k2-b->k2;
}




