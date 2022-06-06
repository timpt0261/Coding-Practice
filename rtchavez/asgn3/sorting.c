//sorting.c
#include "batcher.h"
#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "set.h"
#include "stats.h"

#include <errno.h>
#include <float.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define OPTIONS "ahbiqr:n:p:H"

typedef enum { INSERT, BATCHER, HEAP, QUICK } ALGORITHM;

void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSIS\n"
        "   Program with Various Sorting Algorithms\n"
        "\n"
        "USAGE\n"
        "%s [-ahbiqr:n:p:H] [-r: seed] [-n: size] [-p: elements] \n"
        "OPTIONS\n"
        "-a : Employs all sorting functions\n"
        "-h : Employs all Heap sort \n"
        "-b : Enables Batch Sort\n"
        "-i : Enables Insertion Sort\n"
        "-q : Enables Quicksort\n"
        "-r seed : Set the random seed to seed (Default seed is 13371453) \n"
        "-n size : Sets the array size to size (Default size is 100)\n"
        "-p elements: Prints out the number of elements from the array (Default elements is 100,"
        "\n and if size < elements then the array is printed and nothing more) \n"
        "-H : Displays the program’s usage and synopsis\n",
        exec);
}

void print_array(uint32_t *A, uint32_t size, uint32_t elements) {
    if (size < elements) {
        for (uint32_t i = 0; i < size; i++) {
            if (A[i] == A[size - 1]) {
                printf("%13" PRIu32 "\n", A[i]);
            } else if ((i % 5) == 0 && i > 0) {
                printf("\n%13" PRIu32 "\t", A[i]);

            } else {
                printf("%13" PRIu32 "\t", A[i]);
            }
        }
    } else {
        for (uint32_t i = 0; i < elements; i++) {
            if (A[i] == A[size - 1]) {
                printf("\n%13" PRIu32 "\n", A[i]);
            } else if ((i % 5) == 0 && i > 0) {
                printf("\n%13" PRIu32 "\t", A[i]);

            } else {
                printf("%13" PRIu32 "\t", A[i]);
            }
        }
    }
}

void populate_array(uint32_t *A, uint32_t size, uint32_t seed) {
    srandom(seed);
    for (uint32_t t = 0; t < size; t++) {
        // setting num to random and bit masking
        uint32_t num = random() & ((3 << 30) - 1);
        A[t] = num;
    }
    return;
}

//References:
//  - Attended Eugene's Lecture from 1/22/2022
//  - Collatz.c from assigment 1 to make seed
//  - Attended Brian Zhous ofice hours on 1/25/2022
//  -https://discordapp.com/channels/926211705766305842/926211706559004715/935614065106124810

int main(int argc, char **argv) {
    int opt = 0;
    uint32_t seed = 13371453;
    uint32_t size = 100;
    uint32_t elements = 100;
    //createing universal set for algorithm
    Set s = empty_set();

    // Useing getopt to implement the various commands
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a': s = complement_set(empty_set()); break;
        case 'h': s = insert_set(HEAP, s); break;
        case 'b': s = insert_set(BATCHER, s); break;
        case 'i': s = insert_set(INSERT, s); break;
        case 'q': s = insert_set(QUICK, s); break;
        case 'r': seed = (uint32_t) strtol(optarg, NULL, 10); break;
        case 'n': size = (uint32_t) strtol(optarg, NULL, 10); break;
        case 'p': elements = (uint32_t) strtol(optarg, NULL, 10); break;
        case 'H': usage(argv[0]); break;
        default: usage(argv[0]); return 0;
        } //end of switch

    } //end of while loop

    // create array of random nunmbers

    Stats st;
    st.moves = 0;
    st.compares = 0;
    uint32_t *A;

    for (ALGORITHM sel = INSERT; sel <= QUICK; sel += 1) {
        if (member_set(sel, s)) {
            switch (sel) {
            case INSERT:
                A = (uint32_t *) calloc(size, sizeof(uint32_t));
                populate_array(A, size, seed);
                insertion_sort(&st, A, size);
                printf("Insertion Sort, Elements: %" PRIu32 ", Moves: %" PRIu64
                       ", Compares: %" PRIu64 "\n",
                    size, st.moves, st.compares);
                print_array(A, size, (uint32_t) elements);
                reset(&st);
                free(A);
                break;

            case BATCHER:
                A = (uint32_t *) calloc(size, sizeof(uint32_t));
                populate_array(A, size, seed);
                batcher_sort(&st, A, size);
                printf("Batcher Sort, Elements: %" PRIu32 ", Moves: %" PRIu64 ", Compares: %" PRIu64
                       "\n",
                    size, st.moves, st.compares);
                print_array(A, size, (uint32_t) elements);
                reset(&st);
                free(A);
                break;

            case HEAP:
                A = (uint32_t *) calloc(size, sizeof(uint32_t));
                populate_array(A, size, seed);
                heap_sort(&st, A, size);
                printf("Heap Sort, Elements: %" PRIu32 ", Moves: %" PRIu64 ", Compares: %" PRIu64
                       "\n",
                    size, st.moves, st.compares);
                print_array(A, size, (uint32_t) elements);
                reset(&st);
                free(A);
                break;

            case QUICK:
                A = (uint32_t *) calloc(size, sizeof(uint32_t));
                populate_array(A, size, seed);
                quick_sort(&st, A, size);
                printf("Quick Sort, Elements: %" PRIu32 ", Moves: %" PRIu64 ", Compares: %" PRIu64
                       "\n",
                    size, st.moves, st.compares);
                print_array(A, size, (uint32_t) elements);
                reset(&st);
                free(A);
                break;
            }
        }
    }
    return 0;

} //end of main()

