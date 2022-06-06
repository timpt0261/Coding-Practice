
#include "node.h"
#include "bf.h"
#include "bv.h"
#include "ht.h"
#include "pq.h"
#include "parser.h"
#include "speck.h"
#include "text.c"
#include "metric.h"
#include "salts.h"

#include <inttypes.h>
#include <regex.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#define enum                                                                                       \
    { E, M, C }
#define OPTIONS "d:n:k:l:e:m:c:h"

// The usage function:
//Description: Prints SYNOPSIS, USAGE, and OPTIONS when called
//
//Parameters:
//      exec: The File that's being run on the command line
//Return:
//      Nothing

void usage(char *exec) {
    fprintf(stderr,
        "SYNOPSIS\n"
        "   Program that identifyies Author Identifcation\n"
        "\n"
        "USAGE\n"
        "%s [-d:n:k:l:e:m:c:h] [-d: path to database] [-n: path to noise file] [-k: mathches] "
        "[-l: limit of word to filter] [-e: Euclidean distance] [-m: Manhattan distance] [-c: "
        "Cosine "
        "Distance] [-h: help and ussage]\n"
        "OPTIONS\n"
        "-d : Specify path to database of authors and texts(Default lib.db)\n"
        "-n : Specify path to file of noise words to filter out(Default noise.txt)\n"
        "-k : Specify the number of matches(Default is 5)\n"
        "-l : Specify the number of noise words to filter out(Default is 100)\n"
        "-e : Set the distance metric to use as the Euclidean distance\n"
        "-m : Set the distance metric to use as the Euclidean distance\n"
        "-c : Set the distance metric to use as the cosine distance"
        "-h : Displays the program’s usage and synopsis\n",
        exec);
}

int main(int argc, char **argv) {
    int opt = 0;
    FILE db, noise;

    int matches = 5;
    int filter = 100;
    enum Metric metric = EUCLIDEAN;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'd': break;
        case 'n':
            // checks if noise file exists
            if () {
                //sets noise to argument
                return;
            }
            fprintf(stderr, "Noise file does not exist");
            return -1;
        case 'k': break;
        case 'l': matches = (int) optarg; break;
        case 'e': metric = EUCLIDEAN; break;
        case 'm': metric = MANHATTAN; break;
        case 'c': metric = COSINE; break;
        case 'h': usage(argv[0]); break;
        default: usage(argv[0]); return 1;
        } //end of switch

    } //end of while loop

    //create noise text objext
    Text *noise_text = text_create(noise, NULL);

    // Create new text file w/ noise text
    Text *text = *text_create(stdin, noise_text);
    
    // open up db file

    //create pq
    return 0;
} //end of main
