#ifndef _HEAP_H
#define _HEAP_H
#include "array.h"

#define left(i) (2*(i+1)-1) /* the left child */ 
#define right(i) 2*(i+1) /* the right child */ 
#define parent(i) (i-1)/2 /* parent of i */ 

typedef struct heap {
    array_t array;
    size_t width;
    size_t len;
    int (*cmp)(void *,void *); /* the compare-function */
} heap_t;


void heap_init(heap_t *ph, size_t width);
void heap_add(heap_t *ph, void *value);
void *heap_top(heap_t heap);
void *heap_value(heap_t heap, int index);

void heap_build_max(heap_t *ph);
void heap_heapify(heap_t *ph, int i);

#endif
