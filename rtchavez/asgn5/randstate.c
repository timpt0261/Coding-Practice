//Reuben T. Chavez
//CSE 13s
//randstate.h

#include <stdlib.h>

#include "randstate.h"

extern gmp_randstate_t state;

void randstate_init(uint64_t seed) {
    srandom(seed);
    gmp_randinit_mt(state);
    gmp_randseed_ui(state, seed);
    return;
}

void randstate_clear(void) {
    gmp_randclear(state);
    return;
}
