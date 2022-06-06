//author node.c

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Author_Node Author_Node;

struct Author_Node {
    char *author;
    double distance;
};

Author_Node *a_node_create(char *author) {
    // allocate memory for the Node
    Author_Node *an = (Author_Node *) malloc(sizeof(Author_Node));

    // allocate memory for node word with string length
    an->author = (char *) malloc(sizeof(char) * strlen(author));

    // copy input to node word
    an->author = strdup(author);

    return an;
}

void a_node_delete(Author_Node **an) {
    // checks if the node is null
    if (an) {
        free((*an)->author); // free word since space was allocated for it
        free(*an); // free contents in n
        *an = NULL; // setting pointer to node to null
    }
    return;
}

void node_print(Author_Node *an) {
    if (an) {
        //prints *word and count in node
        printf("Author :[%s]\n Distance: %Lf\n", an->author, an->distance);
    }
    return;
}
