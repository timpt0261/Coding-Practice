#include "universe.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//used to keep track of which direction of the given coordinate to check
typedef enum {
    TOP,
    TOP_RIGHT,
    RIGHT,
    BOTTOM_RIGHT,
    BOTTOM,
    BOTTOM_LEFT,
    LEFT,
    TOP_LEFT
} DIRECTIONS;

//Structure that contains all the varibles that make up the
//Universe struct

// rows: Total number of rows within the grid
// cols: Total number of columns within the grid
// **grid: A double pointer that is a lot like a matrix of [rows * cols]
// toroidal: Determine if edges should 'wrap areoud' or not
struct Universe {
    uint32_t rows;
    uint32_t cols;
    bool **grid;
    bool toroidal;
};

//Universe Creator
// Brief Description:
//      Creates a universe object
//
//Parameter:
//      rows: A unsigned 32 bit integer that reprsents the number of rows in the Universe u
//      cols: A unsigned 32 bit integer that reprsents the number of rows in the Universe u
//      toroidal: A boolean that dtermines if the points 'wrap-around' whwnever touching the edge
//
//Return:
//      A universe pointer that is refrence to a created unviverse
//
//Refrences:
// - Dynamic Memory slides
Universe *uv_create(uint32_t rows, uint32_t cols, bool toroidal) {
    Universe *u = (Universe *) malloc(sizeof(Universe));

    u->toroidal = toroidal;
    u->rows = rows;
    u->cols = cols;

    u->grid = (bool **) calloc(rows, sizeof(bool *));
    assert(u->grid);
    for (uint32_t r = 0; r < rows; r += 1) {
        u->grid[r] = (bool *) calloc(cols, sizeof(bool));
        assert(u->grid[r]);
    }
    return u;
}

//Universe Deleter
// Brief Description:
//      Deletes a universe object
//
//Parameter:
//      *u: A universe pointer the is refered to be deleted
//
//Return:
//      Nothing since the function is void
//
//Refrences
// - https://stackoverflow.com/questions/11015360/free-a-double-pointer/11015432
void uv_delete(Universe *u) {
    for (uint32_t i = 0; i < uv_rows(u); i += 1) {
        free(u->grid[i]);
        u->grid[i] = NULL;
    }
    free(u->grid);
    u->grid = NULL;
    free(u);
    return;
}

//Universe Rows
// Brief Description:
//      Gives the total number of rows with the universe object
//
//Parameter:
//      *u: A universe pointer the is universe to be refered
//
//Return:
//      An unsigned 32 bit integer
//
uint32_t uv_rows(Universe *u) {
    return u->rows;
}

//Universe Columns
// Brief Description:
//      Gives the total number of columns with the universe object
//
//Parameter:
//      *u: A universe pointer that is the universe to be refered to
//
//Return:
//      An unsigned 32 bit integer
//
uint32_t uv_cols(Universe *u) {
    return u->cols;
}

//Universe Live Cell
// Brief Description:
//      Converts specified coordinate in the universe object to true
//
//Parameter:
//      *u: A universe pointer to the Universe object it's going to change
//      r: A unsigned 32 bit integer that reprsents the specified row in the Universe u
//      c: A unsigned 32 bit integer that reprsents the specified row in the Universe u
//Return:
//      Nothing since the function is void
//
void uv_live_cell(Universe *u, uint32_t r, uint32_t c) {
    u->grid[r][c] = true;
    return;
}

//Universe Dead Cell
// Brief Description:
//      Converts specified coordinate in the universe object to false
//
//Parameter
//      *u: A universe pointer to the Universe object it's going to change
//      r: A unsigned 32 bit integer that reprsents the specified row in the Universe u
//      c: A unsigned 32 bit integer that reprsents the specified row in the Universe u
//Return:
//      Nothing since the function is void
//
void uv_dead_cell(Universe *u, uint32_t r, uint32_t c) {
    u->grid[r][c] = false;
    return;
}

//Universe Get Cell
// Brief Description:
//      Returns the specied boolean value within the Universe
//
//Parameter
//      *u: A universe pointer to the Universe object it's going to change
//      r: A unsigned 32 bit integer that reprsents the specified row in the Universe u
//      c: A unsigned 32 bit integer that reprsents the specified row in the Universe u
//
//Return:
//      Returns false if the coordinate is out of bounds of the u->grid
//      Returns the value of the specified coordinate in u->grid
//
bool uv_get_cell(Universe *u, uint32_t r, uint32_t c) {
    bool bounds = 0 <= r && r < uv_rows(u) && 0 <= c && c < uv_cols(u);
    if (bounds) {
        return u->grid[r][c];
    } else {
        return false;
    }
}

//Universe Populate
// Brief Description:
//      Populates a universe object grid by scanning a specific formated files with
//      coordinates on where each 'o' is suppose to be on the grid
//
//Parameter
//      *u: A universe pointer that is refered to which Universe object to be populated
//      *infile: File object that is refered to be taken as refence to
//
//Return:
//     Returns False if a coordinate within the graph is out of bounds of the u->grid
//     Returns True if the graph was succesfully able to be populated
//
bool uv_populate(Universe *u, FILE *infile) {
    uint32_t r;
    uint32_t c;
    bool bounds;

    while (fscanf(infile, "%" SCNd32 " %" SCNd32 "\n", &r, &c) != EOF) {
        //if eithier the row or column is out of bounds return false
        bounds = 0 <= r && r < uv_rows(u) && 0 <= c && c < uv_cols(u);
        if (!bounds) {
            return false;
        }
        uv_live_cell(u, r, c);
    }
    return true;
}

//Universe Census
// Brief Description:
//      Counts the number of live neighbors around a specified coordinate in a clock-wise rotation
//      Depending if the given universe is tordial or not it  will check the nighbors diffrently
//
//Parameter
//      *u: A universe pointer the is refered to be deleted
//      r: A unsigned 32 bit integer that reprsents the specified row in the Universe u
//      c: A unsigned 32 bit integer that reprsents the specified row in the Universe u
//Return:
//      Nothing since the function is void
//
// Refrence:
// - Assignment 3
uint32_t uv_census(Universe *u, uint32_t r, uint32_t c) {
    uint32_t neighbors = 0;
    for (DIRECTIONS dir = TOP; dir <= TOP_LEFT; dir += 1) {
        bool plane_bounds, toroidal_bounds;
        uint32_t tr, tc;
        switch (dir) {
        case TOP:
            tc = ((c + 1) % uv_cols(u));
            plane_bounds = uv_get_cell(u, r, c + 1);
            toroidal_bounds = u->toroidal && uv_get_cell(u, r, tc);
            if (plane_bounds) {
                neighbors += 1;

            } else if (toroidal_bounds) {
                neighbors += 1;
            }
            break;
        case TOP_RIGHT:
            tr = ((r + 1) % uv_rows(u));
            tc = ((c + 1) % uv_cols(u));
            plane_bounds = uv_get_cell(u, r + 1, c + 1);
            toroidal_bounds = u->toroidal && uv_get_cell(u, tr, tc);
            if (plane_bounds) {
                neighbors += 1;

            } else if (toroidal_bounds) {
                neighbors += 1;
            }
            break;
        case RIGHT:
            tr = ((r + 1) % uv_rows(u));
            plane_bounds = uv_get_cell(u, r + 1, c);
            toroidal_bounds = u->toroidal && uv_get_cell(u, tr, c);
            if (plane_bounds) {
                neighbors += 1;

            } else if (toroidal_bounds) {
                neighbors += 1;
            }
            break;
        case BOTTOM_RIGHT:
            tr = ((r + 1) % uv_rows(u));
            tc = ((c - 1) % uv_cols(u));
            plane_bounds = uv_get_cell(u, r + 1, c - 1);
            toroidal_bounds = u->toroidal && uv_get_cell(u, tr, tc);
            if (plane_bounds) {
                neighbors += 1;

            } else if (toroidal_bounds) {
                neighbors += 1;
            }
            break;
        case BOTTOM:
            tc = ((c - 1) % uv_cols(u));
            plane_bounds = uv_get_cell(u, r, c - 1);
            toroidal_bounds = u->toroidal && uv_get_cell(u, r, tc);
            if (plane_bounds) {
                neighbors += 1;

            } else if (toroidal_bounds) {
                neighbors += 1;
            }
            break;
        case BOTTOM_LEFT:
            tr = ((r - 1) % uv_rows(u));
            tc = ((c - 1) % uv_cols(u));
            plane_bounds = uv_get_cell(u, r - 1, c - 1);
            toroidal_bounds = u->toroidal && uv_get_cell(u, tr, tc);
            if (plane_bounds) {
                neighbors += 1;

            } else if (toroidal_bounds) {
                neighbors += 1;
            }
            break;
        case LEFT:
            tr = ((r - 1) % uv_rows(u));
            plane_bounds = uv_get_cell(u, r - 1, c);
            toroidal_bounds = u->toroidal && uv_get_cell(u, tr, c);
            if (plane_bounds) {
                neighbors += 1;

            } else if (toroidal_bounds) {
                neighbors += 1;
            }
            break;
        case TOP_LEFT:
            tr = ((r - 1) % uv_rows(u));
            tc = ((c + 1) % uv_cols(u));
            plane_bounds = uv_get_cell(u, r - 1, c + 1);
            toroidal_bounds = u->toroidal && uv_get_cell(u, tr, tc);
            if (plane_bounds) {
                neighbors += 1;

            } else if (toroidal_bounds) {
                neighbors += 1;
            }
            break;
        }
    }
    return neighbors;
}

//Universe Printer
// Brief Description:
//      Prints the Universe object's u->grid
//
//Parameter
//      *u: A universe pointer that is refrenced to the actual Universe object it's changing
//      *outfile: A File object in where the u-grid is going to be printed out to
//
//Return:
//      Nothing since the function is void
//
void uv_print(Universe *u, FILE *outfile) {
    for (uint32_t i = 0; i < uv_rows(u); i += 1) {
        for (uint32_t j = 0; j < uv_cols(u); j += 1) {
            uv_get_cell(u, i, j) ? fprintf(outfile, "o") : fprintf(outfile, ".");
        }
        fprintf(outfile, "\n");
    }
    return;
}
