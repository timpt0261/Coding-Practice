//life.c
#include "universe.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>

#define OPTIONS "tsn:i:o:H"
#define DELAY   50000

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
//  - Attended Eugene's Lecture from 1/28/2022
//  - Attended Brian Zhou's office hours 1/31/2022
int main(int argc, char **argv) {
    int opt = 0;
    bool toroidal = false;
    bool silence = false;
    uint32_t gen = 100;
    FILE *input = stdin, *output = stdout;

    // Useing getopt to implement the various commands
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 't': toroidal = true; break;
        case 's': silence = true; break;
        case 'n': gen = (uint32_t) strtoul(optarg, NULL, 10); break;
        case 'i': input = fopen(optarg, "r"); break;
        case 'o': output = fopen(optarg, "w"); break;
        case 'H': usage(argv[0]); break;
        default: usage(argv[0]); return 0;
        } //end of switch
    }

    //initaiting universes
    uint32_t rows;
    uint32_t cols;
    Universe *uni_a, *uni_b;

    //scan doc
    fscanf(input, "%" SCNd32 " %" SCNd32 "\n", &rows, &cols);

    //creating two universes
    uni_a = uv_create(rows, cols, toroidal);
    uni_b = uv_create(rows, cols, toroidal);

    if (uv_populate(uni_a, input)) {

        for (uint32_t g = 0; g < gen; g += 1) {
            if (!silence) {
                initscr(); // Initialize the screen.
                curs_set(FALSE); // Hide the cursor.
                clear(); // Clear the window.
                for (uint32_t r = 0; r < uv_rows(uni_a); r += 1) {
                    for (uint32_t c = 0; c < uv_cols(uni_a); c += 1) {
                        if (uv_get_cell(uni_a, r, c)) {
                            mvprintw(r, c, "o"); // Displays "o".
                        }
                    }
                }
                refresh(); // Refresh the window.
                usleep(DELAY); // Sleep for 50000 microseconds.
            }

            for (uint32_t r = 0; r < uv_rows(uni_a); r += 1) {
                for (uint32_t c = 0; c < uv_cols(uni_a); c += 1) {
                    if (uv_get_cell(uni_a, r, c)
                        && (uv_census(uni_a, r, c) == 2 || uv_census(uni_a, r, c) == 3)) {
                        uv_live_cell(uni_b, r, c);
                    } else if (!uv_get_cell(uni_a, r, c) && uv_census(uni_a, r, c) == 3) {
                        uv_live_cell(uni_b, r, c);
                    } else {
                        uv_dead_cell(uni_b, r, c);
                    }
                }
            }
            Universe *temp = uni_a;
            uni_a = uni_b;
            uni_b = temp;
        }

        endwin(); // Close the screen.
    } else if (!uv_populate(uni_a, input)) {
        fprintf(stderr, "The input file has a coordinate that is out of bounds");
    }
    //print final generation
    uv_print(uni_a, output);

    uv_delete(uni_b);
    uv_delete(uni_a);
    fclose(input);
    fclose(output);
    return 0;

} //end of main()
