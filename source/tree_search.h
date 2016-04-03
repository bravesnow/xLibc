/* search binary tree */ 
#ifndef _STREE_H
#define _STREE_H

#include <stdio.h>
#include <stddef.h> /* for offsetof */

/* 通过结构体成员指针获得结构体指针 */ 
#define NODE_GET_PTR(mptr,s,m) ((s*)((char*)(mptr)-offsetof(s,m)))

#define TREE_INIT(stree) stree.root = NULL
#define TREE_GET(pchain) *(stree_t *)&(pchain)
#define TREE_GET_PTR(pchain) (stree_t *)&(pchain)

/* 链接两个结点的结构体 */ 
typedef struct chain {
     struct chain *parent;
     struct chain *left;
     struct chain *right;
} chain_t;
/* 树结构体 */ 
typedef struct search_tree {
     struct chain *root;
} stree_t;


/**********************************/ 
/* 可扩展自定义数据结点 */ 
typedef struct node {
     int key;
     struct chain chain;
} node_t;


/* ********************************* */
chain_t *stree_maximum(stree_t stree);
chain_t *stree_minimum(stree_t stree);
void stree_travel(stree_t stree, void (*visit)(chain_t*));
int stree_search(stree_t stree, chain_t *pchain,
		 int (*compare)(chain_t*,chain_t*));
void stree_insert(stree_t *pstree, chain_t *pchain,
		       int (*compare)(chain_t*,chain_t*));
void stree_delete(stree_t *pstree, chain_t *pdel,
		       int (*compare)(chain_t*,chain_t*),
		       void (*exchange)(chain_t*, chain_t*));
chain_t *stree_successor(chain_t *pcur);


#endif
