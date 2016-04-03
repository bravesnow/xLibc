/* 拓扑排序——基于深度优先遍历 */
#include "graph_list.h"
#include "stack.h"
void topo_visit_recursive(graph_t graph, int s, int *color, int *f)
{
    static int index = 0;
    color[s] = GRAY;
    schain_t *ptr = (graph.lists[s]).head->next;
    while (ptr){ 
	int w = index_key(ptr);
	if (color[w] == WHITE){
	    topo_visit_recursive(graph, w, color, f);
	}
	ptr = ptr->next; 
    }
    color[s] = BLACK;
    f[index++] = s;
}
void topo_visit(graph_t graph, int s, int *color, int *f)
{
    int index = 0;
    stack_t stack;
    stack_init(&stack, sizeof(int));
    stack_push(&stack, &s);
    while (!stack_empty(stack)) {
	int v = *(int*)stack_top(stack);
	if (color[v] == BLACK){
	    break;
	}
	color[v] = GRAY;
	schain_t *ptr = (graph.lists[v]).head->next;
	int flag = 0; /* finished mark */ 
	while (ptr) {	    
	    int w = index_key(ptr);
	    if (color[w] == WHITE) {
		color[w] = GRAY;
		stack_push(&stack, &w);
		flag = 1;
		break;
	    }
	    ptr = ptr->next;	
	}
	if (flag == 0) {
	    color[v] = BLACK;
	    f[index++] = v;
	    stack_pop(&stack);
	}	
    }
}
void graph_topology(graph_t graph)
{
    int *color = malloc(sizeof(int)*graph.V);
    int *f = malloc(sizeof(int)*graph.V); /* topology array */ 
    for (int i = 0; i < graph.V; ++i) {
	color[i] = WHITE;
	f[i] = 0;
    }
    for (int s = 0; s < graph.V; ++s){
	if (color[s] == WHITE) {
	    //topo_visit(graph, s, color, f);
	    topo_visit_recursive(graph, s, color, f);
	}
    }    
    for (int i = graph.V - 1; i >= 0; --i){
	gvisit(graph, f[i]);
    }
}
