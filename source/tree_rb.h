#ifndef _RBTREE_H
#define _RBTREE_H

#include <stddef.h> /* for offsetof */ 
#define RED 1
#define BLACK 0

/* get struct pointer via a pointer of member of struct */
#define CHAIN_NODE_PTR(mptr,s,m) ((s*)((char*)(mptr)-offsetof(s,m)))

typedef struct rbtree_chain {
     int color;
     struct rbtree_chain *left;
     struct rbtree_chain *right;
     struct rbtree_chain *p;
} rbchain_t;

typedef struct rbtree {
     struct rbtree_chain *root;
     struct rbtree_chain *nil;
} rbtree_t;

/* ******************************** */
/* self-define some struct and function, not universal */ 
typedef struct rbtree_node {
     int key;
     struct rbtree_chain rbchain;
} rbnode_t;

/* ******************************** */
void rb_left_rotate(rbtree_t *ptree, rbchain_t *x);
void rb_right_rotate(rbtree_t *ptree, rbchain_t *x);
void rb_insert(rbtree_t *ptree, rbchain_t *z);
void rb_insert_fixup(rbtree_t *ptree, rbchain_t *z);
void rb_delete(rbtree_t *ptree, rbchain_t *z);
void rb_delete_fixup(rbtree_t *ptree, rbchain_t *x);
/* ******************************** */ 

#endif
