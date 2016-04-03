/* circular queue */ 
#ifndef _QUEUE_H
#define _QUEUE_H
#include <stddef.h>
#include "array.h"
typedef struct queue{
    array_t array;
    size_t width;
    int capacity;
    int front, rear;
} queue_t;

void queue_init(queue_t *p, size_t width, int n);
void queue_destroy(queue_t *p);

void queue_in(queue_t *p,  void *value);
void* queue_out(queue_t *p);

int queue_empty(queue_t queue);
int queue_full(queue_t queue);


#endif



 
