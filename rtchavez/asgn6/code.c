//code.c

#include "defines.h"
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>

typedef struct {
    uint32_t top;
    uint8_t bits[MAX_CODE_SIZE];
} Code;

//Refrences:
//  https://stackoverflow.com/questions/5636070/zero-an-array-in-c-code

Code code_init(void) {
    Code *c;
    c->top = 0; // setting top to zero
    c->bits = { 0 }; //zeroing bits
    return c;
}

uint32_t code_size(Code *c) {
    return c->top;
}

bool code_empty(Code *c) {
    if (c) {
        return c->top == 0:
    }
    return false;
}

bool code_full(Code *c) {
    if (c) {
        return c->top == MAX_CODE_SIZE;
    }
    return false;
}

bool code_set_bit(Code *c, uint32_t i) {
    //check if i is within range
    if (i > MAX_CODE_SIZE * 8) {
        return false;
    }
    uint8_t temp[MAX_CODE_SIZE] = c->bits;

    c->bits[c->top / 8] |= i << (c->top % 8); // sets index in bits to index

    assert(temp != c->bits);
    return true;
}

bool code_clr_bit(Code *c, uint32_t i) {

    //check if i is within range
    if (i > MAX_CODE_SIZE * 8) {
        return false;
    }
    uint8_t temp[MAX_CODE_SIZE] = c->bits;

    uint8_t index;
    index = i << (c->top % 8); // left-shift to index  i
    index ^= index; // not result
    c->bits[c->top / 8] &= index; // sets index in bits to index

    assert(temp != c->bits);
    return true;
}

bool code_get_bit(Code *c, uint32_t i) {
    //check if i is within range
    if (i > MAX_CODE_SIZE * 8) {
        return false;
    }
    uint8_t temp[MAX_CODE_SIZE] = c->bits; // make bit equal to bits in code c

    c->bits[c->top / 8] = byte; //get top byte from c bits
    uint8_t bit = byte >> (c->top % 8); //shift to right most index
    bit &= 0x0f; //clear rest of bits except bit at first index

    assert(temp != c->bits);
    return bit == 1;
}

bool code_push_bit(Code *c, uint8_t bit) {
    //checks if code is full
    if (code_full(c)) {
        return false;
    }
    c->top++; // add top
    code_set_bit(c, bit); //push bit in code bits
    return true;
}

bool code_pop_bit(Code *c, uint8_t *bit) {
    //check if code is empty
    if (code_empty(c)) {
        return false;
    }
    c->top--; // subtraction top
    code_clr_bit(c, bit); //clear the designanted bit

    return true;
}

void code_print(Code *c) {
    printf("Code current top: %d\n"
           "Code bits: %x\n ",
        c->top, c->bits);
}
