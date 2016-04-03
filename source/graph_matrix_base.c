#include <stdlib.h>
#include "graph_matrix.h"

void graph_matrix_init(graph_t *pg, int direct, vertex_t *pvex,
		int vn, edge_t *pedge, int en)
{
    pg->direct = direct;
    pg->vset = pvex;
    pg->V = vn;
    pg->E = en;
    
    pg->matrix = malloc(sizeof(int*)*vn);
    for (int i = 0; i < vn; ++i) {
	pg->matrix[i] = malloc(sizeof(int)*vn);
    }
    for (int i = 0; i < en; ++i) {
	int v = pedge[i].v;
	int w = pedge[i].w;
	pg->matrix[v][w] = 1;
	if (direct == 0) {
	    pg->matrix[w][v] = 1;
	}
    }
}
void graph_matrix_destroy(graph_t *pg)
{
    for (int i = 0; i < pg->V; ++i) {
	free(pg->matrix[i]);
    }
    free(pg->matrix);
}
