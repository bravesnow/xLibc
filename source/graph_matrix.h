#ifndef _GRAPH_MATRIX_H
#define _GRAPH_MATRIX_H

#define WHITE 0
#define GRAY 1
#define BLACK 2

typedef struct vertex {
    char value;
} vertex_t;

typedef struct edge {
    int v;
    int w;
} edge_t;

typedef struct graph {
    vertex_t *vset;
    int V;
    int E;
    int direct;
    int **matrix;
} graph_t;

#endif
