// text.c

#include "metric.h"
#include "parser.h"
#include "bf.h"
#include "ht.h"

#include <ctype.h>
#include <math.h>
#include <regex.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE         1 << 19 // Hash size
#define BLOOM_FILTER_SIZE 1 << 21 //Bloom filter size

// word cans have single,or multiple, ' or - but cant be '' --
#define WORD "[^[:punct:][:space:]][A-Za-z'-]+[^[:punct:][:space:]]"

extern uint32_t noiselimit; // Number of noise words to filter out.

typedef struct Text Text;

struct Text {
    HashTable *ht;
    BloomFilter *bf;
    uint32_t word_count;
};
//converts word to lowercase
char *lower_word(char *word) {
    char *lower = (char *) malloc(sizeof(char) * strlen(word));

    for (size_t i = 0; i < strlen(word); ++i) {
        lower[i] = tolower((unsigned char) word[i]);
    }
    return lower;
}

// deletes word
void delete_word(char **word) {
    if (word) {
        free(*word);
        *word = NULL;
    }
    return;
}


double text_frequency(Text *text, char *word) {

    // checks if the word is within the text
    if (!text_contains(text, word)) {
        return 0;
    }
    // create temp for word look in hashtable
    Node *temp = ht_lookup(text->ht, word);

    // check temp null to determine to either count or 0
    return temp != NULL ? (double) temp->count : 0;
}


bool text_contains(Text *text, char *word) {
    //check is the word is in the text bloomfilter
    if (bf_probe(text->bf, word)) {
        return true;
    }
    // check if the word is in the hashtable
    else if (ht_lookup(text->ht, word)) {
        return true;
    }
    return false;
}

// when creating text noise noise input is null
Text *text_create(FILE *infile, Text *noise) {
    //Allocate memory for text struct
    Text *text = (Text *) malloc(sizeof(Text));

    //creat hashtable and bloom filter with specified size
    text->ht = ht_create(HASH_SIZE);
    text->bf = bf_create(BLOOM_FILTER_SIZE);

    regex_t re; // initilaize regex_t varible

    // add case if if reger_t is unable to be compiled
    if (regcomp(&re, WORD, REG_EXTEND)) {
        fprintf(stderr, "Failed to complete regex.\n");
    }

    // Initialize char pointer to null
    char *word = NULL;
    uint32_t count = 0; // intializse count to 0

    // parse through infile and remove word from noise
    while ((word = next_word(infile, &re)) != NULL) {
        word = tolower(word);


        // if noise is null
        if (noise == NULL) {
            // insert word in bloom filter
            bf_insert(text->bf,word);
            // insert word in hash table
            ht_insert(text->ht,word);
        }
        // else if noise not null and word not in noise
        else if (!text_contains(noise, word)) {
            //bf insert word
            bf_insert(text->bf,word);
            //ht insert word
            ht_insert(text->ht,word);
        }
        
        //if inserted word  == noise limit -> break
        if ( count == noiselimit) {
            break;
        }
        //increment count
        count += 1;
    }

    //total number of words in text
    text->word_count = count;
    delete_word(word);
    regfree(&re); // free regex
    return text; // return pointer to text
}

void text_delete(Text **text) {
    // if text null
    if (text) {

        //delete word
        // free text's ht
        ht_delete(&(*text)->ht);
        // free text's bf
        bf_delete(&(*text)->bf);
        // free text itself
        free(*text);
        // set to null
        *text = NULL;
    }
    return;
}

double text_dist(Text *text1, Text *text2, Metric metric) {

    // stores the total word count of the both texts
    uint32_t total_word_count = text1->word_count + text2->word_count;

    //initlize arrays to hold frequncies
    double u[total_word_count];
    double v[total_word_count];
    double result = 0;

    // Create hashtable itertor
    HashTableIterator *hti_1 = hti_create(text1->ht);
    HashTableIterator *hti_2 = hti_create(text1->ht);

    // for word in text1
    for (uint32_t i = 0; i < text1->word_count; i++) {

        // iterate to next node in ht to find word
        char *word = ht_iter(hti_1)->word;
        // find frequncy of that word in text1 and text2
        u[i] = text_frequency(text1, word);
        v[i] = text_frequency(text2, word);
    }

    // for word in text 2 where word in text 1
    for (uint32_t i = text1->word_count; i < total_word_count; i++) {
        //find next word in hash table
        char *word = ht_iter(hti_2)->word;
        // if word not in text1
        if (!text_contains(text1, word)) {
            // add frequency to vector
            u[i] = text_frequency(text1, word);
            v[i] = text_frequency(text2, word);
        }
    }

    // normalize the vectors
    for (int i = 0; i < (text1->word_count + text2->word_count); i++) {
        u[i] /= text1->word_count;
        v[i] /= text2->word_count;
    }

    // use swith case to  compute specfied equation
    switch (metric) {
    case EUCLIDEAN:
        for (int i = 0; i < total_word_count; i++) {
            result += pow((u[i] - v[i]),2);// (u - v )^2
        }

        return sqrt(result);// sqrt((u-v)^2)
    case MANHATTAN:
        for (int i = 0; i < total_word_count; i++) {
            result += fabs(u[i] - v[i]);
        }
        return result;
    case COSINE:
        for (int i = 0; i < total_word_count; i++) {
            result += u[i] * v[i];
        }
        result /= text1->word_count * text2->word_count;

        return result;
    }
}

void text_print(Text *text) {

    // print word count
    printf("Text Word Count:\n %u," text->word_count);

    printf("Bloom Filter in Text:\n");
    // prints each bit in a sequnce of bits
    BloomFilter *bf = text->bf;
    for (uint32_t i = 0; i < bf_size(bf); i++) {
        if (i % 4 == 0 && i < 0) {
            printf("%d\t", bv_get_bit(bf->filter, i) ? 1 : 0);
        }
        printf("%d", bv_get_bit(text->bf->filter, i) ? 1 : 0);
    }

    printf("Hash Table in Text:");
    // iterate theough hash table to print contents
    printf("[");
    for (uint32_t j = 0; j < ht_size(text->ht); j++) {
        Node *temp = text->ht->slots[j];
        temp ? printf("[%s, %u]", temp->word, temp->count) : printf("[NULL]");
    }
    printf("\n");
    printf("]\n");
}
