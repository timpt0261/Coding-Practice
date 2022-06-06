//ht.c

#include "salts.h"
#include "node.h"
#include "speck.h"

#include <assert.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct HashTable HashTable;

typedef struct HashTableIterator HashTableIterator;

struct HashTable {
    uint64_t salt[2]; // The salt to use for the hash function.
    uint32_t size; // The number of slots in the hash table.
    Node **slots; // The array of hash table items.
};

struct HashTableIterator {
    HashTable *table; // The hash table to iterate over.
    uint32_t slot; // The current slot the iterator is on.
};

HashTable *ht_create(uint32_t size) {
    //allocate space for the Hashtable
    HashTable *ht = (HashTable *) malloc(size * sizeof(HashTable));
    ht->size = size; // initialize ht size

    // initilize ht salt
    ht->salt[0] = SALT_HASHTABLE_LO;
    ht->salt[1] = SALT_HASHTABLE_HI;

    return ht;
}

void ht_delete(HashTable **ht) {
    // checks if given ht is null or not
    if (ht) {

        //delete ht slots first
        node_delete((*ht)->slots);

        //free allocated memory for the hashtable
        free(*ht);

        // set ht to null
        *ht = NULL;
    }
    return;
}

uint32_t ht_size(HashTable *ht) {
    return ht->size; // returns size of the ht
}

Node *ht_lookup(HashTable *ht, char *word) {

    // initialize count and starting index in hash
    uint32_t index = hash(ht->salt, word) % ht->size;

    //iterate through hash table until given word is matched
    for (uint32_t i = index; i < ht->size; i++) {
        Node *lookup = ht->slots[index];
        // if the current slot is not null and continas look up word
        if (lookup && strcmp(lookup->word, word) == 0) {
            return lookup; // return current node
        }

        // linear probing implemtation
        index++;
        index = index % ht->size;
    }
    // case not in hash table retun NULL
    return NULL;
}

Node *ht_insert(HashTable *ht, char *word) {
    // initialize count and starting index in hash
    uint32_t index = hash(ht->salt, word) % ht->size;

    // iterate through entire hash table
    for (uint32_t i = index; i < ht->size; i += 1) {

        Node *inserted = ht->slots[index]; // create temp to store returned node
        // if word in slot increment count
        if (inserted) {
            //create node at spefied index
            *(inserted) = *node_create(word);
            //initialize count to 1
            inserted->count = 1;
            // copy current slot
            return inserted; // return current slot
        }
        // else if check slot contins word
        else if (strcmp(inserted->word, word) == 0) {
            //increment current slot's node count
            inserted->count += 1;
            // copy current slot
            return inserted; // return  current slot
        }
        // linear probing implemtation
        index++;
        index = index % ht->size;
    }
    // case word is unable to be inserste in hash table return null
    fprintf(stderr, "Hash Table Over Flow");
    return NULL;
}

void ht_print(HashTable *ht) {
    // prints all the contents of the hash table
    printf("Hash Table contents:\n"
           "Hash size: %u\n"
           "Hash Salt:[%" PRIu64 ", %" PRIu64 "]\n",
        ht->size, ht->salt[0], ht->salt[1]);
    printf("Hash Table:");
    // iterate theough hash table to print contents
    printf("[");
    for (uint32_t i = 0; i < ht_size(ht); i += 1) {
        Node *temp = ht->slots[i];
        temp ? printf("[%s, %u]", temp->word, temp->count) : printf("[NULL]");
        if (i > 0 && (i % 4) == 0) {
            printf("\n");
        }
    }
    printf("]\n");
    return;
}

HashTableIterator *hti_create(HashTable *ht) {
    // allocate memory for the Hash Table Iterator
    HashTableIterator *hti = (HashTableIterator *) malloc(sizeof(HashTableIterator));
    hti->slot = 0;
    hti->table = ht;
    return hti;
}

void hti_delete(HashTableIterator **hti) {
    if (hti) {
        ht_delete(&(*hti)->table);
        free(*hti);
    }
    return;
}

// use to find distance
Node *ht_iter(HashTableIterator *hti) {
    HashTable table = *hti->table; // create temp table for easier access

    // iterate through nodes
    while (hti->slot < ht_size(hti->table)) {
        // create temp of current slot
        Node *avilable = table.slots[hti->slot];
        // if curret slot in ht is not null return
        if (avilable) {
            return avilable; // return coppied slot
        }
        hti->slot++;
    }

    return NULL;
}
