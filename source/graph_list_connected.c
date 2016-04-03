#include "graph_list.h"

/* transposition */ 
void graph_transposition(graph_t *dgraph, graph_t *sgraph)
{
    graph_init_simple(dgraph, sgraph->direct, sgraph->vset, sgraph->V);
    for (int i = 0; i < sgraph->V; ++i){
	schain_t *ptr = (sgraph->lists[i]).head->next;
	while (ptr) {	    
	    int w = index_key(ptr);
	    index_t *vnode = malloc(sizeof(index_t));
	    vnode->key = w;
	    slist_insert(dgraph->lists+i, 0, &vnode->chain);
	    ptr = ptr->next;	
	}
    }	
}
/* get tht topology sort list */ 
void visit_recursive(graph_t graph, int s, int *color, int *f)
{
    static int index = 0;
    color[s] = BLACK;
    schain_t *ptr = (graph.lists[s]).head->next;
    while (ptr){
	int v = index_key(ptr);
	if (color[v] == WHITE) {
	    visit_recursive(graph, v, color, f);
	}
	ptr = ptr->next; 
    }
    f[graph.V - (++index)] = s;
}
/* error: ¿¼ÂÇÓÃ¶Ñ*/ 
void special_visit(graph_t graph, int s, int *color, int *f)
{
    color[s] = BLACK;
    schain_t *ptr = (graph.lists[s]).head->next;
    while (ptr){
	int v = index_key(ptr);
	if (color[v] == WHITE) {
	    visit_recursive(graph, v, color, f);
	}
	ptr = ptr->next; 
    }
    
}
void special_dfs(graph_t graph, int *f)
{
    int *color = malloc(sizeof(int)*graph.V);
    for (int i = 0; i < graph.V; ++i) {
	special_visit(graph, i, color, f);
    }
}
void graph_connected(graph_t graph)
{
    int *color = malloc(sizeof(int)*graph.V);
    int *f = malloc(sizeof(int)*graph.V); /* ÍØÆËÅÅÐòÊý×é */ 
    for (int i = 0; i < graph.V; ++i) {
	color[i] = WHITE;
    }    
    for (int s = 0; s < graph.V; ++s){
	if (color[s] == WHITE) {
	    visit_recursive(graph, s, color, f);
	}
    }
    for (int i = 0; i < graph.V; ++i) {
	printf("%d\n", f[i]);
    }
    graph_t rgraph;
    graph_transposition(&rgraph, &graph);

    //special_dfs(rgraph);
}
