//bv.c

#include "bv.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct BitVector BitVector;

struct BitVector {
    uint32_t length;
    uint8_t *vector;
};

// Refrences:
// - https://www.geeksforgeeks.org/find-ceil-ab-without-using-ceil-function/
BitVector *bv_create(uint32_t length) {

    // Allocate memory for the BitVector
    BitVector *bv = (BitVector *) malloc(sizeof(BitVector));
    // compute ceil of length/ 8 to get numre of bytes in vector
    uint8_t bit_length = (length / 8) + ((length % 8) != 0);
    // Allocate vector to have array with zero bytes
    bv->vector = (uint8_t *) calloc(bit_length, sizeof(uint8_t));
    bv->length = length; // set bv length to input

    return bv;
}

void bv_delete(BitVector **bv) {
    // check if bv is null
    if (bv) {
        // free memory for the vector pointer
        free((*bv)->vector);

        // free bv
        free(*bv);

        // set to null
        *bv = NULL;
    }
    return;
}

uint32_t bv_length(BitVector *bv) {
    // return length of bv
    return bv->length;
}

bool bv_set_bit(BitVector *bv, uint32_t i) {
    // checks if bv is null
    if (bv) {
        // checks if i within range
        if (i < bv->length) {
            return false;
        }
        // sets the i-th bit in the vector
        bv->vector[i / 8] |= 0x1 << (i % 8);
    }
    return true;
}

bool bv_clr_bit(BitVector *bv, uint32_t i) {
    // checks if bv is null
    if (bv) {
        // check if i is in range
        if (i < bv->length) {
            return false;
        }
        // clears i-th bit in vector
        bv->vector[i / 8] &= ~(0x1 << (i % 8));
    }
    return true;
}

bool bv_get_bit(BitVector *bv, uint32_t i) {
    uint8_t bit;

    // checks if bv is null
    if (bv) {
        // checks if i is in range
        if (i > bv->length) {
            return false;
        }

        // create temp to i-th bit
        bit = (uint8_t) bv->vector[i / 8] >> (i % 8);
        bit &= 0x1;
    }
    // return bit
    return bit ? true : false;
}

void bv_print(BitVector *bv) {
    //print length
    printf("Bit Vector Length : %u\n", bv->length);
    printf("Bit Vector :\n[");

    // iterates through vecto in bv to print each bit
    for (uint32_t i = 0; i < bv->length; i++) {
        if ((i % 4) == 0 || i == (bv->length - 1)) {
            printf("%u\n", bv->vector[i]);
        } else {
            printf("%u,", bv->vector[i]);
        }
    }
    printf("]\n");
    return;
}
