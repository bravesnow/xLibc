#ifndef _TREE_H
#define _TREE_H

#include <stdio.h>
#include <stddef.h> /* for offsetof */ 
/* 通过结构体成员指针获得结构体指针 */ 
#define CHAIN_NODE_PTR(mptr,s,m) ((s*)((char*)(mptr)-offsetof(s,m)))
#define TREE_INIT(tree) tree.root = NULL
#define TREE_GET(pchain) *(tree_t *)&(pchain)
#define TREE_GET_PTR(pchain) (tree_t *)&(pchain)

/* 链接两个结点的结构体 */ 
typedef struct chain {
     struct chain *first;
     struct chain *second;
} chain_t;
/* 树结构体 */ 
typedef struct tree {
     struct chain *root;
} tree_t;

/*******************/ 
/* 可扩展自定义数据结点 */ 
typedef struct node {
     void *value;
     struct chain chain;
} node_t;
/* 可扩展自定义通过链接结点访问数据 */ 
void visit(chain_t *pchain)
{
     node_t *pnode = CHAIN_NODE_PTR(pchain, node_t, chain);
     printf("%d\n",*(int*)pnode->value);
}
#endif
