#include "stats.h"

#include <stdint.h>
#include <stdio.h>

//Insert Sort Program
//Description:
//      Sorting Algorithm that considers one element at a time where it places them in their
//      correct ordered postion as it passe throught the array.
//
//Parameters:
//      *stats: reference to the stats.c functions in "stats.h"
//      *A: refrence to array to accomplish sort
//       n: the length of the array
//Returns
//  - Is void so it doesn't return anything
//
//Refrences:
//  - Assigment 3 document
void insertion_sort(Stats *stats, uint32_t *A, uint32_t n) {
    for (uint32_t i = 1; i < n; i += 1) {
        uint32_t j = i;
        uint32_t temp = A[i];
        move(stats, A[i]);
        while (j > 0 && cmp(stats, temp, A[j - 1]) < 0) {
            move(stats, A[j]);
            A[j] = A[j - 1];
            j -= 1;
        }
        move(stats, A[j]);
        A[j] = temp;
    }
    return;
}
