#include <stdio.h>
#include "TEST.h"
int main(int argc, char *argv[])
{
    test_list();
}
/************************************************************************/
/* 动态数组array													    */
/************************************************************************/
void test_array()
{
	array_t darray; /* 动态数组 */
	array_init(&darray, sizeof(int)); /* 初始化整型动态数组 */

	int a[] = { 3, 4, 9, 2 };
	for (int i = 0; i < 4; ++i) {
		array_insert(&darray, 0, &a[i]); /* 在头部插入元素 */
	}

	int len = array_len(darray);
	printf("array length: %d\n", len);
	array_delete(&darray, 2); /* 删除索引2位置的元素 */
	len = array_len(darray);
	printf("array length after del: %d\n", len);

	int v = *(int*)array_value(darray, 2); /* 获得索引2位置的值 */
	printf("v: %d\n", v);
	int new = 5;
	array_set(&darray, 2, &new);
	v = *(int*)array_value(darray, 2);
	printf("new v: %d\n", v);

	array_destroy(&darray); /* 释放数组 */
}

/************************************************************************/
/*	链表list                                                              */
/************************************************************************/
void test_list()
{
    list_t alist;
    list_init(&alist);

    node_t anode;
    anode.value = 3;
    printf("insert list value = %d\n", anode.value);
    list_add_head(&alist, &anode.chain);
    node_t bnode;
    bnode.value = 5;
    list_insert_index(&alist, 1, &bnode.chain);
    list_travel(alist, list_visit_data);
}

/************************************************************************/
/*	堆heap                                                              */
/************************************************************************/
#if 0
/*heap比较函数*/
int cmp(void *f, void *s)
{
	return *(int*)f - *(int*)s;
}
void test_heap()
{
	heap_t heap; /* 堆结构 */
	heap_init(&heap, sizeof(int)); /* 初始化整型空堆 */
	heap.cmp = cmp; /* 堆元素的比较函数 */
	int a[7] = { 3, 4, 1, 2, 6, 9, 7 }; /* insert heap one-by-one*/
	for (int i = 0; i < 7; i++) {
		heap_add(&heap, (a + i));
	}
	int max_val = *(int*)heap_top(heap);
	printf("%d\n", max_val);
	(void)heap_destroy(&heap);
}
#define N 5 /* the number of vertices */
#define M 4 /* teh number of edges */

int test_list(int argc, char *argv[])
{
    vertex_t varray[N];
    for (int i = 0; i < N; ++i) {
        varray[i].value = 'A' + i;
    }
    edge_t earray[M] = { { 0, 1 }, { 0, 2 }, { 0, 4 }, { 1, 3 } };

    graph_t graph;
    graph_init(&graph, 1, varray, N, earray, M);
    //    graph_dfs(graph);
    graph_connected(graph);

    graph_destroy(&graph);

    /*    graph_t xgraph;
    graph_init_simple(&xgraph, 0, varray, N);
    edge_t x = {1, 3};
    graph_add_edge(&xgraph, x);
    printf("%d\n",xgraph.E);
    graph_destroy(&xgraph); */
}
void graph_print(graph_t graph)
{
    for (int i = 0; i < graph.V; ++i) {
        for (int j = 0; j < graph.V; ++j) {
            printf("%d ", graph.matrix[i][j]);
        }
        printf("\n");
    }
}
int test_matrix(int argc, char *argv[])
{
    vertex_t varray[N];
    for (int i = 0; i < N; ++i) {
        varray[i].value = 'A' + i;
    }
    edge_t earray[M] = { { 0, 1 }, { 0, 2 }, { 0, 4 }, { 1, 3 }, { 2, 3 } };

    graph_t graph;
    graph_init(&graph, 0, varray, N, earray, M);

    graph_dfs(graph, 0);

    graph_destroy(&graph);
    return 0;
}

#endif
