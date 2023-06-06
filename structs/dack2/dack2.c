#include <stdbool.h>
#include <malloc.h>
#include "dack2.h"

#define MIN_CAP 6

void dbl_dk_init(dbl_dk *dk){
    dk->cap=MIN_CAP;
    dk->buff = malloc(dk->cap * sizeof(double));
    dk->count=0;
    dk->head=0;
}

// bool dbl_dk_resize(dbl_dk *dk, int new_cap){
//     if (new_cap < dk->count){
//         return false;
//     }
//     if (new_cap < MIN_CAP){
//         new_cap = MIN_CAP;
//     }
//     if (dk->head + dk->count > dk->cap){
//         if ((dk->cap - dk->head) > (dk->cap / 2)){
//             double *tmp = realloc(dk->buff, new_cap * sizeof(double));
//             if (tmp == NULL){
//                 return false;
//             }
//             int old_cap = dk->cap;
//             dk->buff = tmp; 
//             dk->cap = new_cap; 
//             for (int i = 0; i < (dk->head + dk->count) % old_cap; i++){
//                 dk->buff[dk->head + old_cap - ((dk->head + dk->count) % old_cap) - 1] = dk->buff[i + old_cap];
//             }
//         } else {
//             double *tmp = realloc(dk->buff, new_cap * sizeof(double));
//             if (tmp == NULL){
//                 return false;
//             }
//              int old_cap = dk->cap;
//             dk->buff = tmp; 
//             dk->cap = new_cap;  
//             for (int i = dk->cap - (old_cap - dk->head); i < dk->cap; i++){
//                 dk->buff[i] = dk->buff[i - old_cap];
//             }
//             dk->head = dk->cap - (old_cap - dk->head);
//         }
//     } else {
//         double *tmp = realloc(dk->buff, new_cap * sizeof(double));
//         if (tmp == NULL){
//             return false;
//         }
//         dk->buff = tmp;
//         dk->cap = new_cap;
//     }
    
//     return true;
// }

static bool increase(dbl_dk *dk){
    int new_cap = 2 * dk->cap;
    double *tmp = realloc(dk->buff, new_cap * sizeof(double));
    if (tmp == NULL){
        return false;
    }
    if (dk->head + dk->count > dk->cap){
        if ((dk->cap - dk->head) > (dk->cap / 2)){
            int old_cap = dk->cap;
            dk->buff = tmp; 
            dk->cap = new_cap; 
            for (int i = 0; i < (dk->head + dk->count) % old_cap; i++){
                dk->buff[dk->head + old_cap - ((dk->head + dk->count) % old_cap) - 1] = dk->buff[i + old_cap];
            }
        } else {
            int old_cap = dk->cap;
            dk->buff = tmp; 
            dk->cap = new_cap;  
            for (int i = dk->cap - (old_cap - dk->head); i < dk->cap; i++){
                dk->buff[i] = dk->buff[i - old_cap];
            }
            dk->head = dk->cap - (old_cap - dk->head);
        }
    } else {
        dk->buff = tmp;
        dk->cap = new_cap;
    }
    
    return true;
}

bool dbl_dk_push_back(dbl_dk *dk, double val){
    if (dk->count == dk->cap){
        if(!increase(dk)) return false;
    }
    dk->buff[(dk->count + dk->head)%dk->cap] = val;
    dk->count++;
    return true;
}

bool dbl_dk_push_front(dbl_dk *dk, double val){
    if (dk->count == dk->cap){
        if(!increase(dk)) return false;
    }
    dk->buff[(dk->head-1+dk->cap)%dk->cap] = val;
    dk->head = (dk->head-1+dk->cap)%dk->cap;
    dk->count++;
    return true;
}

static void decrease_if_possible(dbl_dk *dk){
    if (dk->count < dk->cap/4){
        int new_cap = dk->cap/2;
        if (new_cap < MIN_CAP){
            new_cap = MIN_CAP;
        }
        if (new_cap >= dk->cap){
            return ;
        }
        if ((dk->head + dk->count) > new_cap){
            if ( dk->head > (dk->cap / 2)){
                for (int i = new_cap - (dk->cap - dk->head); i < new_cap; i++){
                    dk->buff[i] = dk->buff[i + new_cap];
                }
                dk->head = new_cap - (dk->cap - dk->head);
            } else {
                for (int i = 0; i < new_cap; i++){
                    dk->buff[i] = dk->buff[new_cap + i];
                }  
            }
        } 
        double *tmp = realloc(dk->buff, new_cap * sizeof(double));
        dk->buff = tmp;
        dk->cap = new_cap;
    }
}

double dbl_dk_pop_back(dbl_dk *dk){
    double res = dk->buff[(dk->head+dk->count-1)%dk->cap];
    dk->count--;
    return res;  
}

double dbl_dk_pop_front(dbl_dk *dk){
    double res = dk->buff[dk->head];
    dk->head = (dk->head+1)%dk->cap;
    dk->count--;
    decrease_if_possible(dk);
    return res; 
}

bool dbl_dk_is_empty(dbl_dk *dk){
    if (dk->count==0){
        return true;
    }
    return false;
}

void dbl_dk_destr(dbl_dk *dk){
    dk->count=0;
}



