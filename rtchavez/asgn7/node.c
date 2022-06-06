//node.c

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node Node;

struct Node {
    char *word;
    uint32_t count;
};

Node *node_create(char *word) {
    // allocate memory for the Node
    Node *n = (Node *) malloc(sizeof(Node));

    // allocate memory for node word with string length
    n->word = (char *) malloc(sizeof(char) * strlen(word));

    // copy input to node word
    n->word = strdup(word);

    return n;
}

void node_delete(Node **n) {
    // checks if the node is null
    if (n) {
        free((*n)->word); // free word since space was allocated for it
        free(*n); // free contents in n
        *n = NULL; // setting pointer to node to null
    }
    return;
}

void node_print(Node *n) {
    if (n) {
        //prints *word and count in node
        printf("Node Word:[%s]\nNode Count: %u\n", n->word, n->count);
    }
    return;
}
