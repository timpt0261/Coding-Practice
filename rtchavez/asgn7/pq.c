// pq.c

#include "nodes.h"
#include <inttypes.h>
#include <string.h>
#include <stdio.h>
#include <stdlibs.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct PriorityQueue PriorityQueue;

typedef struct PriorityQueueEntry PriorityQueueEntry;

struct PriorityQueueEntry {
    char *author;
    double distance;
    PriorityQueueEntry next;

} PriorityQueueEntry;

struct PriorityQueue {
    uint32_t head;
    uint32_t tail;
    uint32_t capacity;
    PQENTRY *ad; // contains {author, distance}
};
static uint32_t pred(PriorityQueue *pq, uint32_t head){
    return (head - 1) % 

}

static succ;

PriorityQueueEntry *pqe_create(char *author) {

    PriorityQueueEntry *pqe = (PriorityQueueEntry) malloc(sizeof(PriorityQueueEntry));
    pqe->author = (char *) malloc(sizeof(char) * strlen(author));
    pqe->author = strdup(author);
    return *pqe;
}

void pqe_delete(PriorityQueueEntry **pqe) {
    if (pqe) {
        free(&(*pqe)->word);
        free(*pqe);
        *pqe = NULL;
    }
    return;
}

PriorityQueue *pq_create(uint32_t capacity) {

    // allocate memory of Priority Queue
    PriorityQueue *pq = (PriorityQueue *) malloc(sizeof(PriorityQueue));

    // set pq capcity to input
    pq->capacity = capacity;

    //Initilize head and tail to zero
    pq->head = 0;
    pq->tail = 0;

    //return pq
    return pq;
}

void pq_delete(PriorityQueue **q) {
    if (q) {
        pqe_delete(&(*q)->ad);
        free(*q);
        *q = NULL;
    }
    return;
}

bool pq_empty(PriorityQueue *q) {
    // return weather the head and tail of the queue are equal
    if (q) {
        return q->head == q->tail;
    }
    return false;
}

bool pq_full(PriorityQueue *q) {
    // return weather the head and capacity of the queue are equal
    if (q) {
        return q->head + 1 == q->capacity;
    }
}

uint32_t pq_size(PriorityQueue *q) {
    // returns queue size
    return q->head + 1;
}

bool enqueue(PriorityQueue *q, char *author, double dist) {
    // check is queue is full
    if (pq_full(q)) {
        return false;
    }
    //create entry with author name and distance stored
    PriorityQueueEntry *pqe = pqe_create(author);
    pqe->distance = dist;

    //add entry to current end of pq
    pq->ad[pq->head] = pqe;
    pq->head = succ(pq->head);

    return true;
}

bool dequeue(PriorityQueue *q, char **author, double *dist) {
    if (pq_empty(q)) {
        return false;
    }
    //iterate through pq until author is found
    int i = pq->tail;
    for (int i = pq->tail; i < pq->head; i++) {
        if (strcmp(pq->ad[i]->author == author)) {
        }
    }

    pq->ad[pq->head] = pqe;
    pq->head = succ(pq->head);
    return true;
}

void pq_print(PriorityQueue *q) {
    //prints everything but queue from pq
    printf("PriorityQueue :\n"
           "Capacity: %" PRIu32 "\n"
           "++++++++++\n"
           "Head: %" PRIu32 "\n"
           "Tail: %" PRIu32 "\n"
           "+++++++++++\n",
        q->capacity, q->head, q->tail);

    //prints queue
    for (uint32_t i = 0; i < pq_capacity(q); i++) {
        printf();
    }
    return;
}
