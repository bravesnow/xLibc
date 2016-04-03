#ifndef _TREE_H
#define _TREE_H

#include <stdio.h>
#include <stddef.h> /* for offsetof */ 
/* ͨ���ṹ���Աָ���ýṹ��ָ�� */ 
#define CHAIN_NODE_PTR(mptr,s,m) ((s*)((char*)(mptr)-offsetof(s,m)))
#define TREE_INIT(tree) tree.root = NULL
#define TREE_GET(pchain) *(tree_t *)&(pchain)
#define TREE_GET_PTR(pchain) (tree_t *)&(pchain)

/* �����������Ľṹ�� */ 
typedef struct chain {
     struct chain *first;
     struct chain *second;
} chain_t;
/* ���ṹ�� */ 
typedef struct tree {
     struct chain *root;
} tree_t;

/*******************/ 
/* ����չ�Զ������ݽ�� */ 
typedef struct node {
     void *value;
     struct chain chain;
} node_t;
/* ����չ�Զ���ͨ�����ӽ��������� */ 
void visit(chain_t *pchain)
{
     node_t *pnode = CHAIN_NODE_PTR(pchain, node_t, chain);
     printf("%d\n",*(int*)pnode->value);
}
#endif
