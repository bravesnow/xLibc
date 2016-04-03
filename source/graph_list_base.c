#include <stdio.h>
#include <stdlib.h>
#include "graph_list.h"
#include "list_single.h"
/* ---------------------------------------------- */
/* 访问图实际顶点的实际值 */ 
void gvisit(graph_t graph, int key)
{
    printf("%c\n", graph.vset[key].value);
}
/* ---------------------------------------------- */
/* 图的索引获得键值即实际图的顶点的存储位置 */ 
int index_key(schain_t *pchain)
{
    index_t *pindex = chain_get_node(pchain, index_t, chain);
    return pindex->key;
}
/* ---------------------------------------------- */
/* 初始化图的结构 */ 
void graph_init(graph_t *pgraph, int direct, vertex_t *pvex,
		int vn, edge_t *pedge, int en)
{
    pgraph->direct = direct;
    pgraph->vset = pvex;
    pgraph->V = vn;
    pgraph->E = en;
    pgraph->lists = (slist_t*)malloc(sizeof(slist_t)*vn);
    
    for (int i = 0; i < vn; ++i) {
	index_t *inode = (index_t*)malloc(sizeof(index_t));
	inode->key = i;
	slist_init(pgraph->lists + i);
	//slist_add_head(pgraph->lists+i, &inode->chain);
    }
    for (int i = 0; i < en; ++i) {
	index_t *vnode = malloc(sizeof(index_t));
	vnode->key = pedge[i].v;
	index_t *wnode = malloc(sizeof(index_t));
	wnode->key = pedge[i].w;
	slist_insert(pgraph->lists+vnode->key, 0, &wnode->chain);
	if (direct == 0){ /* undirected graph */ 
	    slist_insert(pgraph->lists+wnode->key, 0, &vnode->chain);
	}
    }
}
/* ---------------------------------------------- */
/* 简单初始化，不初始化边集，动态添加 */ 
void graph_init_simple(graph_t *pg, int direct, vertex_t *pvex, int vn)
{
    pg->direct = direct; /* direct or undirect */ 
    pg->vset = pvex;
    pg->V = vn;
    pg->E = 0;
    pg->lists = malloc(sizeof(slist_t)*vn);
    
    for (int i = 0; i < vn; ++i) {
	index_t *inode = (index_t*)malloc(sizeof(index_t));
	inode->key = i;
	slist_init(pg->lists + i);
    }
}
/* 向图添加边 */
void graph_add_edge(graph_t *pg, edge_t edge)
{
    index_t *vnode = (index_t*)malloc(sizeof(index_t));
    vnode->key = edge.v;
    index_t *wnode = (index_t*)malloc(sizeof(index_t));
    wnode->key = edge.w;
    slist_insert(pg->lists + vnode->key, 0, &wnode->chain);
    if (pg->direct == 0){ /* undirected graph */ 
	slist_insert(pg->lists + wnode->key, 0, &vnode->chain);
    }
    ++pg->E;
}
/* ---------------------------------------------- */
/* 对应于简单初始化的简单释放(添加边之后就不起作用了) */ 
void graph_destroy_simple(graph_t *pg)
{
    for (int i = 0; i < pg->V; ++i){
	slist_destroy(pg->lists + i);
    }
    (void)free(pg->lists);
}
/* ---------------------------------------------- */
/* 释放图的结构 */ 
void graph_destroy(graph_t *pgraph)
{
    for (int i = 0; i < pgraph->V; ++i) {
	schain_t *p = pgraph->lists[i].head->next;
	schain_t *q;
	while (p) {
	    q = p;
	    p = p->next;
	    index_t *inode = chain_get_node(q, index_t, chain);
	    free(inode);
	}
	slist_destroy(pgraph->lists + i);
    }
    free(pgraph->lists);
}
