#ifndef _GRAPH_LIST_H
#define _GRAPH_LIST_H

#include "list_single.h"
#define WHITE 0
#define GRAY 1
#define BLACK 2
typedef struct vertex_node{
    char value; /* data element */
} vertex_t;

typedef struct index_node {
    int key; /* index value */
    schain_t chain; /* index chain */
} index_t;

typedef struct edge_node {
    int v; /* edge start-vertex */
    int w; /* edge end-vertex */
} edge_t;

typedef struct graph {
    int direct; /* graph attribute */ 
    vertex_t *vset; /* the vertex set */ 
    int V, E; /* the number of vertex and edge */ 
    slist_t *lists; /* vertex list */ 
} graph_t;

#endif
