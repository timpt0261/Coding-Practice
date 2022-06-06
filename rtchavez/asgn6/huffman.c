//huffman.c

#include "node.h"
#include "code.h"
#include "defines.h"
#include "pq.h"

#include <stdio.h>
#include <unistd.h>
#include <stdint.h>


// traverses through tree

//Refrence Euguen's Office Hours
//  
void traverse(Node *root){
    Node *temp = root;
    // go to left
    temp = root->left;

    //go right 
    temp = root->right;

    //go to root
    temp = root;
}


Node *build_tree(uint64_t hist[static ALPHABET]) {
    //Iniitalize empty Priortiy Queue
    PriorityQueue *pq = pq_create(ALPHABET);
    //Initilize nodes
    Node *left, *right, *parent, *root;

    //while len(pq) > 1
    while ( pq->head > 0 ){

        // left = dequeue(pq) and right = dequeue(pq)
        if (dequeue(pq, &left) && dequeue(pq, &right)) {

            //parent = node_join
            parent = node_join(left, right);

            // parent = enqueue(parent)
            if (enqueue(pq, parent)) {
                continue;
            }
        }
    }
    if (dequeue(pq,&root)) {
        return root;
    }
}

void build_codes(Node *root, Code table[static ALPHABET]) {
    Code c = code_init();

    if (root) {
        if (!root->left && !root->right) {
            table->symbol = c;
        }
        code_push_bit(&c, 0);
        build_code(root->left, table);
        code_pop_bit(&c, 0);

        code_push_bit(&c, 1);
        build_code(root->right, table);
        code_pop_bit(&c, 1);
    }
    return;
}

void dump_tree(int outfile, Node *root) {
    //Performs Post Order traversal to print out tree
    if (root) {
        dump_tree(outfile, root->left);
        dump_tree(outfile, root->right);

        if (!root->left && !root->right) {
            //write leaf node
            fwrite('L',1, sizeof(str),outfile);

        } else {
            // write interior node
            fwrite(outfile, 'I', 1);
        }
    }

    return;
}

Node *rebuild_tree(uint16_t nbytes, uint8_t tree[static nbytes]) {
    Node *current;
    Node *root;
    Stack stack = stack_create();
    //Use post order to rebuild tree

    //for i in range of 0 to nybytes
    for(uint16_t i =  0; i < nbytes; i += 2){
        if(tree[i] == 'L'){
            current = node_create(tree[i++], 0);
            stack_push( , current);

            
        }
        else(tree[i] == 'I'){ 
            stack_pop();
        }
    }
    return root;
}

//References:
//  Lecture 18 Trees and Tries
void delete_tree(Node **root) {
    //Performs Post_Order Traversal to deletes entire tree

    if (*root) {
        delete_tree(&(*root)->left);
        delete_tree(&(*root)->right);
        node_delete(root);
    }
    return;
}
