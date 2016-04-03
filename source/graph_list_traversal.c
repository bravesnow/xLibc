#include "graph_list.h"
#include "stack.h"
#include "queue.h"
/* ************************************************ */ 
/* Breadth-First Search */ 
static void bfs_visit(graph_t graph, int s, int *color)
{
    queue_t queue;
    queue_init(&queue, sizeof(int), graph.V);
    queue_in(&queue, &s);
    
    while (!queue_empty(queue)) {
	int v = *(int*)queue_out(&queue);
	if (color[v] == WHITE) {
	    gvisit(graph, v);
	    color[v] = BLACK;
	}	
	schain_t *ptr = (graph.lists[v]).head->next;
	while (ptr) {	    
	    int w = index_key(ptr);
	    if (color[w] == WHITE) {
		queue_in(&queue, &w);
	    }	    
	    ptr = ptr->next;	
	}
    }
    queue_destroy(&queue);
}
void graph_bfs(graph_t graph)
{
    int *color = (int*)malloc(sizeof(int)*graph.V);
    for (int i = 0; i < graph.V; ++i) {
	color[i] = WHITE;
    }
    for (int i = 0; i < graph.V; ++i) {
	if (color[i] == WHITE) {
	    bfs_visit(graph, i, color);
	}
    }
    free(color);
}
/* ************************************************ */
/* depth-first search */ 
void dfs_visit_recursive(graph_t graph, int s, int *color)
{
    gvisit(graph, s);
    color[s] = BLACK;
    schain_t *ptr = (graph.lists[s]).head->next;
    while (ptr){
	int v = index_key(ptr);
	if (color[v] == WHITE){
	    dfs_visit_recursive(graph, v, color);
	}
	ptr = ptr->next; 
    }
}
void dfs_visit(graph_t graph, int s, int *color)
{
    stack_t stack;
    stack_init(&stack, sizeof(int));    
    stack_push(&stack, &s);
    
    while (!stack_empty(stack)) {
	int v = *(int*)stack_top(stack);	
	if (color[v] == WHITE){
	    gvisit(graph, v);
	    color[v] = BLACK;
	}
	stack_pop(&stack);
	schain_t *ptr = (graph.lists[v]).head->next;
	while (ptr) {	    
	    int w = index_key(ptr);
	    if (color[w] == WHITE) {
		stack_push(&stack, &w);
	    }
	    ptr = ptr->next;	
	}	
    }
    stack_destroy(&stack);
}
void graph_dfs(graph_t graph)
{
    int *color = malloc(sizeof(int)*graph.V);
    for (int i = 0; i < graph.V; ++i) {
	color[i] = WHITE;
    }
    for (int s = 0; s < graph.V; ++s){
	if (color[s] == WHITE) {
	    //dfs_visit(graph, s, color);
	    dfs_visit_recursive(graph, s, color);
	}
    }
    free(color);
}
