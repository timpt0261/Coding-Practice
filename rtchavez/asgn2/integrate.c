//integrate.c

#include "functions.h"
#include "mathlib.h"

#include <errno.h>
#include <float.h>
#include <inttypes.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define OPTIONS "abcdefghijn:p:q:H"

void table() {
    fprintf(stderr, "------------------------------------------------------------------\n"
                    "                     Table of Approximated  Values                \n"
                    "------------------------------------------------------------------\n"
                    "    Integral                    Low     High         Value        \n"
                    "------------------------------------------------------------------\n"
                    "sqrt(1-x^4)                      0       1       0.87401918476405 \n"
                    "1/log(x)                         2       3       1.118424814549702\n"
                    "e^-x^2                         -10      10       1.772453850905508\n"
                    "sin(x^2)                        -π       π       1.545303425380133\n"
                    "cos(x^2)                        -π       π       1.131387027213366\n"
                    "log(log(x))                      2      10       3.952914142858876\n"
                    "sin(x)/x                       -4π      4π       2.984322451168924\n"
                    "e^-x/x                           1      10       0.2193797774265986\n"
                    "e^e^x                            0       1       6.316563839027766\n"
                    "sqrt(sin^2(x) + cos^2(x))        0       π       3.141592653589797\n"
                    "------------------------------------------------------------------\n");
}
// The usage function:
//Description: Prints the Integrate Functions SYNOPSIS, USAGE, and OPTIONS when called
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
        "   Library Containing Math functions\n"
        "\n"
        "USAGE\n"
        "%s [-a:b:c:d:e:f:g:h:j:H] [-p: low bound] [-q: high bound] [-n: partitions] \n"
        "OPTIONS\n"
        "-a : Sets the function to integrate to sqrt(1 − x^4)\n"
        "-b : Sets the function to integrate to 1/log(x)\n"
        "-c : Sets the function to integrate to e^−x^ 2\n"
        "-d : Sets the function to integrate to sin(x^ 2)\n"
        "-e : Sets the function to integrate to cos(x^ 2)\n"
        "-f : Sets the function to integrate to log(log(x))\n"
        "-g : Sets the function to integrate to sin(x)/x\n"
        "-h : Sets the function to integrate to e^−x /x \n"
        "-i : Sets the function to integrate to e ^ e ^ x\n"
        "-j : Sets the function to integrate to√sin^2(x) +cos^2(x)\n"
        "-n partitions : Sets the upper limit of partitions to use in the composite"
        "\n\tSimpson’s rule to\n"
        "-n partitions; default value of 100\n"
        "-p low : Sets the low end of the interval to integrate over to low\n"
        "\n\t(Does not have a default value and must be specified each time the program is to "
        "run)\n"
        "-q high : Sets the high end of the interval to integrate over to high\n"
        "\n\tDoes not have a default value and must be specified each time"
        "the program is to run)\n"
        "-H : Displays the program’s usage and synopsis\n",
        exec);
    table();
}

//The Main Function:
//Description: Takes the user input and depending on which commands are called the intergrate
//             is for a specfied functions form the funtions.h is called
//             Prints Integrate of <function> from <low> to <high> bounds to the  the 1e-14 degree for
//             every even <partition>, 2,4,..., n-2,n
//
//Parameters:
//      argc: argument count
//      argv: argument values
//
//Return:
//      Return 0 after it's finished intergrating the function
//
//Sources I used to create function:
//-https://canvas.ucsc.edu/courses/49882/external_tools/4171
//-https://www.codegrepper.com/code-examples/c/c+modify+char+array
//-https://discordapp.com/channels/926211705766305842/926211706559004718/930963923270774844
//-https://www.gnu.org/software/libc/manual/html_node/Example-of-Getopt.html
//-https://www.gnu.org/software/libc/manual/html_node/Using-Getopt.html
//-https://git.ucsc.edu/cse13s/winter2022/rtchavez/-/blob/master/asgn1/collatz.c
//-https://www.eskimo.com/~scs/cclass/int/sx10a.html
//-https://www.tutorialspoint.com/What-does-int-argc-char-argv-mean-in-C-Cplusplus
//-https://hilalmorrar.com/ucsc-guide/docs/
//-collatz.c
//The Programing Language by Brian W.Kernighan & Dennis M. Ritchie

double z(double x) {
    return sin(x) / x;
}

int main(int argc, char **argv) {
    int opt = 0;
    double (*fun)(double);
    char function[100] = "";
    double low, high;
    float mid = NAN, low_x, max_x;

    uint32_t n = 100;

    // Useing getopt to implement the various commands
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':

            low_x = -1 - 1e-5;
            max_x = 1 + 1e-5;

            strcpy(function, "sqrt(1 - x^4)");
            fun = a;
            break;
        case 'b':

            mid = 1.0;
            low_x = -1e-16;
            max_x = INFINITY;

            strcpy(function, "1/log(x)");
            fun = b;
            break;
        case 'c':

            low_x = -INFINITY;
            max_x = INFINITY;

            strcpy(function, "e^-x^2");
            fun = c;
            break;
        case 'd':

            low_x = -INFINITY;
            max_x = INFINITY;
            strcpy(function, "sin(x^2)");
            fun = d;
            break;
        case 'e':

            low_x = -INFINITY;
            max_x = INFINITY;

            strcpy(function, "cos(x^2)");
            fun = e;
            break;
        case 'f':

            low_x = 1.0;
            max_x = INFINITY;

            strcpy(function, "log(log(x))");
            fun = f;
            break;
        case 'g':

            mid = 0.0;
            low_x = -INFINITY;
            max_x = INFINITY;

            strcpy(function, "sin(x)/x");
            fun = g;
            break;
        case 'h':

            mid = 0.0;
            low = -11.0;
            max_x = INFINITY;

            strcpy(function, "(e^-x)/x");
            fun = h;
            break;
        case 'i':

            low_x = -INFINITY;
            max_x = 2.0;

            strcpy(function, "e^e^x");
            fun = i;
            break;
        case 'j':

            low_x = -INFINITY;
            max_x = INFINITY;

            strcpy(function, "sqrt(sin^2(x) + cos^2(x))");
            fun = j;
            break;
        case 'n': n = (uint32_t) strtol(optarg, NULL, 10); break;
        case 'p': low = (double) strtol(optarg, NULL, 10); break;
        case 'q': high = (double) strtol(optarg, NULL, 10); break;
        case 'H': usage(argv[0]); break;
        default: usage(argv[0]); return EXIT_FAILURE;
        } //end of switch

    } //end of while loop

    //for integrate that don't have mid
    if (low_x < (float) low && low < high && (float) high < max_x && mid == NAN) {

        for (int t = 2; t < ((int) n + 1); t += 2) {
            printf("%d, %3.15f\n", t, integrate(fun, low, high, t));
        }

    }// if it has a mid
    else if (mid != NAN && low < mid && mid < high) {
        for (int t = 2; t < ((int)n + 1); t += 2) {
            double sum = integrate(fun, -4*M_PI, (double) mid - 1e-16  , t);
            sum += integrate(fun,(double) mid + 1e-16,4 *M_PI, t);
            printf("%d, %3.15f\n", t,sum);
        }
    }
    //mid is out of bounds
    else if (mid != NAN && ((mid < low &&  mid < high) || (mid > high && mid > low)) ){

        for (int t = 2; t < ((int) n + 1); t += 2) {
            printf("%d, %3.15f\n", t, integrate(fun, low, high, t));
        }

    } else {
        fprintf(stderr,
            "The bounds -p and/or -q are out of range for the integrate"
            "of the function = %s \n",
            function);
        table();
        return EXIT_FAILURE;
    }
    return 0;

} //end of main()
