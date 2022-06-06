
#include "parser.h"
#include <regex.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define WORD                                                                                       \
    "[^[:punct:][:space:]][A-Za-z'-]+[^[:punct:][:space:]]" // word cans have single,or multiple, ' or - but cant be '' --
char *lower_word(char *word) {
    char *lower = (char *) malloc(strlen(word));

    for (size_t i = 0; i < strlen(word); ++i) {
        lower[i] = tolower((unsigned char) word[i]);
    }
    return lower;
}

void delete_word(char **word) {
    if (word) {
        free(*word);
        *word = NULL;
    }
    return;
}

int main(void) {
    regex_t re;
    if (regcomp(&re, WORD, REG_EXTENDED)) {
        fprintf(stderr, "Failed to compile regex.\n");
        return 1;
    }

    char *word = NULL;
    while ((word = lower_word(next_word(stdin, &re))) != NULL) {
        printf("Word: %s\n", word);
    }

    delete_word(&word);
    regfree(&re);
    return 0;
}
