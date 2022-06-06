#pragma once

typedef struct Author_Node Author_Node;

struct Author_Node {
    char *author;
    double distance;
};

Author_Node *a_node_create(char *author);

void a_node_delete(Author_Node **an);

void a_node_print(Author_Node *an);
