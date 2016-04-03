/* circular queue */ 
#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "queue.h"
/* 初始化容量n的空队 */ 
void queue_init(queue_t *pqueue, size_t width, int n)
{
    array_init_n(&pqueue->array, width, n+1);
    pqueue->capacity = n+1;
    pqueue->front = 0;
    pqueue->rear = 0;
}
/* 释放队列 */ 
void queue_destroy(queue_t *p)
{
    array_destroy(&p->array);
}
/* 入队 */ 
void queue_in(queue_t *p,  void *value)
{
    if (queue_full(*p)){
	printf("Full Queue\n");
	exit(1);
    }
    array_set(&p->array, p->rear, value);
    p->rear = (p->rear + 1)%(p->capacity);
     
}
/* 出队 */ 
void* queue_out(queue_t *p)
{
    if (queue_empty(*p)){
	printf("Empty Queue\n");
	exit(1);
    }
    void *result = array_value(p->array, p->front);
    p->front = (p->front + 1)%(p->capacity);
    return result;
}
/* 队列判断是否为空 */ 
int queue_empty(queue_t queue)
{
    return (queue.front == queue.rear) ? 1 : 0;
}
/* 队列判断是否为满 */
int queue_full(queue_t queue)
{
    return (queue.rear + 1)%(queue.capacity) == queue.front ? 1 : 0;
}
