//pq.c
#include "node.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct PriorityQueue PriorityQueue;

//References:
//  Lecture 10 Stacks
struct PriotityQueue {
    uint32_t head;
    uint32_t tail;
    uint32_t capacity;
    Node *Q;
};


PriorityQueue *pq_create(uint32_t capacity) {
    PriorityQueue *pq = (PriorityQueue *) malloc(sizeof(PriorityQueue));

    if (pq != NULL){
        pq->head = 0;
        pq->tail = 0;
        pq->capacity = capacity;
        pq->Q = (Node **) calloc(capacity, sizeof(PriorityQueue *));
        if (pq->Q){
            return pq;
        }
        free(pq);
    }
    return pq;
}

void insertion_sort(PriorityQueue *pq, Node **n) {
    for (uint32_t i = pq->tail; i <  pq->head; i++) {
        uint32_t j = i;
        Node temp = pq->Q[i];
        while (j > 0 && temp < pq->Q[j - i]) {
            pq->Q[j] = pq->Q[j - i];
            j -= 1;
        }
        pq->Q[j] = temp
    }
    return;
}

void pq_delete(PriorityQueue **q) {
    if (q) {
        free((*q)->Q);
        free(*q);
        *q->*Q = NULL;
        free(q);
    }
    return;
}

bool pq_empty(PriorityQueue *q) {
    // if q is not NULL return if the head is equal to tail
    return q ? q->head == q->tail : false;
}

bool pq_full(PriorityQueue *q) {
    return q ? q->head == q->capacity - 1 : false;
}

uint32_t pq_size(PriorityQueue *q) {
    return q ? q->top : 0;
}

bool enqueue(PriorityQueue *q, Node *n) {
    if (q) {
        if (pq_full(q)) {
            return false;
        }

        q->Q[q->head] = *n;
        q->head = insertion_sort(q, q->head);
        return true;
    }
    return false;
}

bool dequeue(PriorityQueue *q, Node **n) {

    if (q) {
        if (pq_empty(q)) {
            return false;
        }
        *n = q->Q[q->tail];
        q->tail = insertion_sort(q, q->tail);
    }
    return false;
}

void pq_print(PriorityQueue *q) {
    printf(stderr,
        "Queue: %s\n"
        "Top: %d\n"
        "Tail: %d\n"
        "Captivity: %d\n",
        q->Q, q->top, q->tail, q->captivity);
}
