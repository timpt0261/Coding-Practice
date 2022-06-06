//node.c

#include <inttypes.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
typedef struct Node Node;

struct Node {
    Node *left;
    Node *right;
    uint8_t symbol;
    uint64_t frequency;
};

Node *node_create(uint8_t symbol, uint64_t frequency) {
    Node *n = (Node *) malloc(sizeof(Node));

    n->symbol = symbol;
    n->frequency = frequency;

    return n;
}

void node_delete(Node **n) {
    if (*n) {
        free((*n)->left);
        free(*n);
        *n = NULL;
    }

    return;
}

Node *node_join(Node *left, Node *right) {
    uint8_t symbol = '$'; // parent's symbol to $
    uint64_t frequency
        = left->frequency + right->frequency; // parent frequency = left and right freq.

    //createing and initilizing node
    Node *parent = node_create(symbol, frequency);

    parent->left = left->left; //parent's left node to left child node
    parent->right = right->right; //parent's left node to left child node

    return parent;
}

void node_print(Node *n) {

   fprintf(stderr,
        "Frequency: %"PRIu64"\n"
        "Left Node: %s\n"
        "Right Node: %s\n"
         ,n->symbol, n->frequency);
}
