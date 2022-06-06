//Reuben T. Chavez
//CSE 13s
// decrypt.c
#include "numtheory.h"
#include "randstate.h"
#include "rsa.h"

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

#define OPTIONS "i:o:n:vh"

gmp_randstate_t state;

// The usage function:
//Description: Prints life's SYNOPSIS, USAGE, and OPTIONS when called
//
//Parameters:
//      exec: The File that's being run on the command line
//Return:
//      Nothing
//Sources I used as reference:
//-collatz.c
//The Programing Language by Brian W.Kernighan & Dennis M. Ritchie
//

void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSIS\n"
        "   Program That Incorporates the Game of Life\n"
        "\n"
        "USAGE\n"
        "%s [-tsn:i:o:H] [-n: generations] [-i: input] [-o: output] \n"
        "OPTIONS\n"
        "-t : Specifies that the Game of Life to be played on tordial universe\n"
        "-s : Silences ncurses \n"
        "-n : Specifies the number of Generations that the Universe goes through(Default is one "
        "hundred)\n"
        "-i : Input File (Defualt is stdin)\n"
        "-o : Output File (Defualt is stdiout)\n"
        "-H : Displays the program’s usage and synopsis\n",
        exec);
}

//The Main Program
//
//Brief Description:
//      Depending on what is taken as input, two Universe object will be initalized to a
//      specified row and column size where it then for itertions of specified number of
//      generation it, create the next universe that follows, and then finnaly print the
//      the final result of the universe to the specified output
//
//Parameters:
//      argc: argument count
//      **argv: argument vector
//
//Returns:
//      Returns 0 when the program is done
//
//References:
//  - Attended Eugene's Lecture from 2/11/2022
//  - Attended Brian Zhou's office hours 2/10/2022
int main(int argc, char **argv) {
    int opt = 0;
    FILE *input = stdin, *output = stdout, *priv_file = fopen("rsa.priv", "r");
    bool verbose = false;

    // Useing getopt to implement the various commands
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'i':
            if (access(optarg, F_OK) != 1) { // Check if pbfile exists in repo.
                input = fopen(optarg, "r");
                break;
            }
            fprintf(stderr, "The input file you have entered does not exist");
            return 0;
        case 'o':
            if (access(optarg, F_OK) != 1) {
                output = fopen(optarg, "w");
                break;
            }
            fprintf(stderr, "The output file you have entered does not exist");
            return 0;
        case 'n':
            if (access(optarg, F_OK) != 1) {
                priv_file = fopen(optarg, "r");
                break;
            }
            fprintf(stderr, "The public file you have entered does not exist");
            return 0;
        case 'v': verbose = true; break;
        case 'h': usage(argv[0]); break;
        default: usage(argv[0]); return 0;
        } //end of switch
    }

    mpz_t n, d, e;
    mpz_inits(n, d, e);

    rsa_read_priv(n, d, priv_file);

    if (verbose) {
        gmp_printf("Public Modulus n:%d\n"
                   "Public Exponent e:%d\n",
            n, e);
    }

    rsa_decrypt_file(input, output, n, e);

    mpz_clears(n, d, e);
    fclose(input);
    fclose(output);
    fclose(priv_file);
    return 0;

} //end of main()
