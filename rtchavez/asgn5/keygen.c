//Reuben T. Chavez
//CSE 13s
// keygen.c

#include <errno.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#include "numtheory.h"
#include "randstate.h"
#include "rsa.h"

#define OPTIONS "b:i:n:d:s:vh"

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
//  - Attended Eugene's Lecture from 2/4/2022
//  - https://www.delftstack.com/howto/c/c-check-if-file-exists/#:~:text=file's%20full%20path.-,stat()%20Function%20to%20Check%20if%20a%20File%20Exists%20in,the%20file%20does%20not%20exist.
int main(int argc, char **argv) {
    int opt = 0;
    uint64_t bits;
    uint64_t iterations = 50;
    FILE *pbfile, *pvfile;
    pbfile = fopen("rsa.pub", "r");
    pvfile = fopen("rsa.priv", "r");
    uint64_t seed = time(NULL);
    srandom(seed);

    bool verbose = false;

    // Useing getopt to implement the various commands
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'b': bits = (uint64_t) strtoul(optarg, NULL, 10); break;
        case 'i': iterations = (uint64_t) strtol(optarg, NULL, 10); break;
        case 'n':

            if (access(optarg, F_OK) != 1) {
                pbfile = fopen(optarg, "w");
                break;
            }

            fprintf(stderr, "The public file you have chossen does not exist");
            return 0;
        case 'd':

            if (access(optarg, F_OK) != 1) {
                pvfile = fopen(optarg, "w");
                break;
            }

            fprintf(stderr, "The private file you have chossen does not exist");
            return 0;
        case 's':
            seed = (uint64_t) strtoul(optarg, NULL, 10); // Creates Seed at Determined point
            srandom(seed);
            break;
        case 'v': verbose = true;
        case 'h': usage(argv[0]); break;
        default: usage(argv[0]); return 0;
        } //end of switch
    }

    fchmod(fileno(pvfile), 0600);

    randstate_init(seed);

    mpz_t p, q, e, n, d, s;
    mpz_inits(p, q, e, n, d, s, NULL);

    rsa_make_pub(p, q, n, e, bits, iterations);
    rsa_make_priv(d, e, p, q);

    char *username = getenv("HOME");

    if (verbose) {
        gmp_printf("\n"
                   "Username: %s\n"
                   "Singnature(s): %d\n"
                   "First Prime p:%d\n"
                   "Second Prime q:%d\n"
                   "Public Modulus n:%d\n"
                   "Public Exponent e:%d\n"
                   "Private Key d:%d\n",
            username, s, p, q, n, e, d);
    }

    rsa_write_pub(n, e, s, username, pbfile);

    rsa_write_priv(n, d, pvfile);

    randstate_clear();
    mpz_clears(p, q, e, n, d, s, NULL);
    fclose(pbfile);
    fclose(pvfile);
    return 0;

} //end of main()
