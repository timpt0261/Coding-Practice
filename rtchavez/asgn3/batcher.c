#include "stats.h"

#include <inttypes.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

//Reference:
//  -The C Programming Languange - ch 5 section 5.2 pg 95
void comparator(Stats *stats, uint32_t *A, uint32_t x, uint32_t y) {
    if (cmp(stats, A[x], A[y]) > 0) {
        swap(stats, &A[y], &A[x]);
    }
    return;
}

//References:
// - https://www.gatevidyalay.com/converting-base-10-to-base-2-decimal-to-binary/
// - I attended Eugenes' Lecture on January 22, 2022
void batcher_sort(Stats *stats, uint32_t *A, uint32_t n) {
    if (n == 0) {
        return;
    }
    uint32_t t;
    // bit count n
    uint32_t size = n;
    for (uint32_t tc = 1; size > 0; size = size >> 1) {
        t = tc;
        tc++;
    }
    uint32_t p = 1 << (t - 1);
    while (p > 0) {
        uint32_t q = 1 << (t - 1);
        uint32_t r = 0;
        uint32_t d = p;

        while (d > 0) {
            for (uint32_t i = 0; i < (n - d); i++) {
                if ((i & p) == r) {
                    comparator(stats, A, i, i + d);
                }
            }
            d = q - p;
            q = q >> 1;
            r = p;
        }
        p = p >> 1;
    }
    return;
}
