#include <stdlib.h>

#include "queue.h"

struct queue_node *init_node(struct queue_value value) {
    struct queue_node *node = (struct queue_node *)malloc(sizeof(struct queue_node));
    node->value = value;
    node->next = NULL;

    return node;
}

struct queue *init_queue() {
    struct queue *queue = (struct queue *)malloc(sizeof(struct queue));
    queue->head = NULL;
    queue->tail = NULL;

    return queue;
}

void enqueue(struct queue *queue, struct queue_value value) {
    struct queue_node *node = init_node(value);

    if (queue->tail == NULL) {
        queue->head = node;
        queue->tail = node;
    } else {
        queue->tail->next = node;
        queue->tail = node;
    }
}

struct queue_value dequeue(struct queue *queue) {
    struct queue_value value = queue->head->value;
    struct queue_node *new_head = queue->head->next;

    free(queue->head); 

    queue->head = new_head;
    if (queue->head == NULL)
        queue->tail = NULL;

    return value;
}
