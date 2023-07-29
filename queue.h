#ifndef QUEUE_H
#define QUEUE_H

#include <stdint.h>

struct value {
    struct cube *cube;
    uint32_t state;
    uint8_t last;
    uint8_t depth;
};

struct node {
    struct value value;
    struct node *next;
};

struct queue {
    struct node *head;
    struct node *tail;
};

struct node *init_node(struct value);
struct queue *init_queue();
void enqueue(struct queue *, struct value);
struct value dequeue(struct queue *);

#endif
