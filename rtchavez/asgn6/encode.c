//Reuben T. Chavez
//CSE 13s
// encode.c
#include "pq.h"
#include "huffman.h"

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define OPTIONS "hi:o:v"

// The usage function:
//Description: Prints  SYNOPSIS, USAGE, and OPTIONS when called
//
//Parameters:
//      exec: The File that's being run on the command line
//Return:
//      Nothing

void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSIS\n"
        "   Program that implements Huffmans encoder\n"
        "\n"
        "USAGE\n"
        "%s [-hi:o:v] [-i: input] [-o: output]\n"
        "OPTIONS\n"
        "-h : Displays the program’s usage and synopsis\n",
        "-i : Input File (Defualt is stdin)\n"
        "-o : Output File (Defualt is stdiout)\n"
        "-v : Prints compression statistics to stderr\n" exec);
}

int main(int argc, char **argv) {
    int opt = 0;
    FILE *input = stdin, *output = stdout;
    bool com_stat = false;

    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'h': usage(argv[0]); break;
        case 'i':
            if (access(optarg, F_OK) != 1) { //checks if inputed file does exist
                input = fopen(optarg, "r");
                break;
            }
            fprintf(stderr, "The file you have entered does not exist");
            break;
        case 'o':
            if (access(optarg, F_OK) != 1) { //checks if inputed file does exist
                output = fopen(optarg, "w");
                break;
            }
            fprintf(stderr, "The file you have entered does not exist");
            break;
        case 'v': com_stat = true;
        } //end of switch
    } //end of while loop

    //Read through infile
    read_bytes(input, uint8_t * buf, int nbytes);

    //Increment count of element 0 and element 255

    //Construct Huffman tree
    build_tree();

    //Construct code table
    build_codes();

    //Construct Heder

    fclose(input);
    fclose(output);
    return 0;
} //end of main
