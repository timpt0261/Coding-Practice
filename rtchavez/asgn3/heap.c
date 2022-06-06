#include "stats.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

//Heap Maintenace

//Max Child
//Description:
//      Finds the second to max element within the array through iterating two elements at time
//      and comparing them
//
//Parameters:
//      *A: reference to array
//      first: refrence to first element in array A
//      last: last element in array A
//
//Return:
// - unsigned 32 bit interger that is the second to max element of the array A, or the max_child
//
int32_t max_child(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    uint32_t left = first << 1;
    uint32_t right = left + 1;
    if (right <= last && cmp(stats, A[right - 1], A[left - 1]) > 0) {
        return right;
    }
    return left;
}

//Fix Heap
//Description:
//      Is the second routine of the heapsort algorthim. In which the largest elements of the heap
//      are placed at the end of the  array folowed by it's two children than followed by thier two
//      two children
//
//Parameters:
//      *A: reference to array
//      first: refrence to first element in array A
//      last: last element in array A

void fix_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    bool found = false;
    uint32_t mother = first;
    uint32_t great = max_child(stats, A, mother, last);
    while (mother <= (last >> 1) && !found) {
        if (cmp(stats, A[mother - 1], A[great - 1]) < 0) {
            swap(stats, &A[mother - 1], &A[great - 1]);
            mother = great;
            great = max_child(stats, A, mother, last);
        } else {
            found = true;
        }
    }

    return;
}

//Parameters:
//      *A: reference to array
//      first: refrence to first element in array A
//      last: last element in array A
void build_heap(Stats *stats, uint32_t *A, uint32_t first, uint32_t last) {
    for (uint32_t father = (last >> 1); first <= father; father--) {
        fix_heap(stats, A, father, last);
    }

    return;
}

//The Heapsort Algorthim:
//Description:
//      Implementation of a Max Heap Data Structure, where the array is fomated into a
//      binary tree and each element is associated as a node. Where the parent node
//      has the greatest value with the array followed by two children nodes.
//      Where as for an index of k the left child node is 2k and the right child node
//      is 2k + 1. Additionally, the parent index of any index is k should be [k/2]
//
//                             Max Heap Example
//                                   {13}
//                                |        |
//                               {5}      {8}
//                              |   |    |   |
//                             {0} {1}  {2} {3}
//
//                               ______________
//                              |13|5|8|0|1|2|3|
//                               ~~~~~~~~~~~~~~
//      This program sorts the inputed array by doing the following:
//          1. Building the Heap: creates a duplicate of array and format it in max heap
//          2. Fixing the Heap: Sorts array following the heap
//
//Parameters:
//      *stats:referece to the stats.h table
//      *A: reference to array
//       n: array's length
//Return:
// -  Nothing since the function's return type is void
//
//Refrences:
// - Assigment 3 doc
//
void heap_sort(Stats *stats, uint32_t *A, uint32_t n) {
    uint32_t first = 1;
    uint32_t last = n;
    build_heap(stats, A, first, last);
    for (uint32_t leaf = last; first <= leaf; leaf--) {
        swap(stats, &A[first - 1], &A[leaf - 1]);
        fix_heap(stats, A, first, leaf - 1);
    }

    return;
}
