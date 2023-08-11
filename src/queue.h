#ifndef QUEUE_H
#define QUEUE_H

#include <stdint.h>

struct queue_value {
    struct cube *cube;
    uint32_t state;
    uint8_t turn;
    uint8_t depth;
};

struct queue_node {
    struct queue_value value;
    struct queue_node *next;
};

struct queue {
    struct queue_node *head;
    struct queue_node *tail;
};

struct queue_node *init_node(struct queue_value);
struct queue *init_queue();
void enqueue(struct queue *, struct queue_value);
struct queue_value dequeue(struct queue *);

#endif
