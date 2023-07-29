#include <stdlib.h>

#include "queue.h"

struct queue *init_queue() {
    struct queue *queue = (struct queue *)malloc(sizeof(struct queue));
    queue->head = NULL;
    queue->tail = NULL;

    return queue;
}

struct node *init_node(struct value value) {
    struct node *node = (struct node *)malloc(sizeof(struct node));
    node->value = value;
    node->next = NULL;

    return node;
}

void enqueue(struct queue *queue, struct value value) {
    struct node *node = init_node(value);

    if (queue->tail == NULL) {
        queue->head = node;
        queue->tail = node;
    } else {
        queue->tail->next = node;
        queue->tail = node;
    }
}

struct value dequeue(struct queue *queue) {
    struct value value = queue->head->value;
    struct node *new_head = queue->head->next;

    free(queue->head); 

    queue->head = new_head;
    if (queue->head == NULL)
        queue->tail = NULL;

    return value;
}
