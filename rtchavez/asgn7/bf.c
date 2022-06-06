//bf.c

#include "speck.h"
#include "bv.h"
#include "salts.h"

#include <inttypes.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
typedef struct BloomFilter BloomFilter;

struct BloomFilter {
    uint64_t primary[2]; // Primary hash function salt.
    uint64_t secondary[2]; // Secondary hash function salt.
    uint64_t tertiary[2]; // Tertiary hash function salt.
    BitVector *filter;
};

BloomFilter *bf_create(uint32_t size) {
    // Allocate Memory for the Bloom Filter
    BloomFilter *bf = (BloomFilter *) malloc(sizeof(BloomFilter));

    //Create Bit Vector with size
    bf->filter = bv_create(size);

    //set primary, secondary, and tertiary to MACROS in salts.h
    bf->primary[0] = SALT_PRIMARY_LO;
    bf->primary[1] = SALT_PRIMARY_HI;

    bf->secondary[0] = SALT_SECONDARY_LO;
    bf->secondary[1] = SALT_SECONDARY_HI;

    bf->tertiary[0] = SALT_TERTIARY_LO;
    bf->tertiary[1] = SALT_TERTIARY_HI;

    return bf;
}

void bf_delete(BloomFilter **bf) {
    // checks if the filter is null
    if (*bf) {
        // delte bf filter
        bv_delete(&(*bf)->filter);

        // free bf
        free(bf);

        // set to null
        *bf = NULL;
    }
    return;
}

uint32_t bf_size(BloomFilter *bf) {
    return bv_length(bf->filter);
}

void bf_insert(BloomFilter *bf, char *word) {

    uint32_t curr; // intilize varible to store hash
    // check that bf and it's filter is not null
    if (bf && bf->filter) {

        //hash given word with first salt;
        curr = hash(bf->primary, word) % bf_size(bf);
        bv_set_bit(bf->filter, curr); // set hash in to bf filter

        //hash given word with second salt;
        curr = hash(bf->secondary, word) % bf_size(bf);
        bv_set_bit(bf->filter, curr);

        //hash given word with third salt;
        curr = hash(bf->tertiary, word) % bf_size(bf);

        bv_set_bit(bf->filter, curr);
    }
    return;
}

bool bf_probe(BloomFilter *bf, char *word) {

    bool set_one, set_two, set_three; //  bools to check if word in set
    uint32_t curr; // intilize varible to store hash
    // check that bf and it's filter is not null
    if (bf && bf->filter) {

        //hash given word with first salt;
        curr = hash(bf->primary, word) % bf_size(bf);

        set_one = bv_get_bit(bf->filter, curr); // set hash in to bf filter

        //hash given word with second salt;
        curr = hash(bf->secondary, word) % bf_size(bf);

        set_two = bv_get_bit(bf->filter, curr);

        //hash given word with third salt;
        curr = hash(bf->tertiary, word) % bf_size(bf);

        set_three = bv_get_bit(bf->filter, curr);
    }
    return set_one && set_two && set_three;
}

void bf_print(BloomFilter *bf) {
    // print salts in bf
    printf("Primary: [%" PRIu64 ", %" PRIu64 "]\n Secondary: [%" PRIu64 ", %" PRIu64
           "]\n Ternary: [%" PRIu64 ", %" PRIu64 "]\n",
        bf->primary[0], bf->primary[1], bf->secondary[0], bf->secondary[1], bf->tertiary[0],
        bf->tertiary[1]);

    printf("Bloom Filter Bits:\n");
    // prints each bit in a sequnce of bits
    for (uint32_t i = 0; i < bf_size(bf); i++) {
        if (i % 4 == 0 && i < 0) {
            printf("%d\t", bv_get_bit(bf->filter, i) ? 1 : 0);
        }
        printf("%d", bv_get_bit(bf->filter, i) ? 1 : 0);
    }
    return;
}
