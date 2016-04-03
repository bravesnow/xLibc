#include <stdlib.h>
#include <stdio.h>
#include "graph_matrix.h"
#include "queue.h"
#include "stack.h"
/* ************************************************ */ 
/* Breadth-First Search */ 
void graph_matrix_bfs(graph_t graph, int s)
{
    int *color = (int*)malloc(sizeof(int)*graph.V);
    for (int i = 0; i < graph.V; ++i) {
	color[i] = WHITE;
    }
    
    queue_t queue;
    queue_init(&queue, sizeof(int), graph.V);
    queue_in(&queue, &s);
    while (!queue_empty(queue)) {
	int v = *(int*)queue_out(&queue);
	//printf("out:%d\n",v);
	if (color[v] == WHITE) {
	    (void)printf("%d\n",v);
	    color[v] = GRAY;
	}
	for (int i = 0; i < graph.V; ++i) {
	    if (graph.matrix[v][i] == 1 && color[i] == WHITE) {
		printf("%d\n",i);
		color[i] = GRAY;
		queue_in(&queue, &i);
	    }
	}
    }
    (void)free(color);
    queue_destroy(&queue);
}

/* ************************************************ */
/* depth-first search */
void graph_matrix_dfs(graph_t graph, int s)
{
    int *color = (int*)malloc(sizeof(int)*graph.V);
    for (int i = 0; i < graph.V; ++i) {
	color[i] = WHITE;
    }

    stack_t stack;
    stack_init(&stack, sizeof(int));
    stack_push(&stack, &s);
    
    while (!stack_empty(stack)) {
	int v = *(int*)stack_top(stack);
	stack_pop(&stack);
	if (color[v] == WHITE) {
	    printf("%d\n",v);
	    color[v] = GRAY;
	}
	for (int i = 0; i < graph.V; ++i) {
	    if (color[i] == WHITE && graph.matrix[v][i] == 1) {
		stack_push(&stack, &i);
	    }
	}
    }
    stack_destroy(&stack);
}
