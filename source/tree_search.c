#include <stdio.h>
#include <stdlib.h>
#include "tree_search.h"

/* 可扩展自定义通过链接结点访问数据 */
static void visit(chain_t *pchain)
{
	node_t *pnode = NODE_GET_PTR(pchain, node_t, chain);
	printf("%d\n", pnode->key);
}
/* 链数据比较函数 */
static int compare(chain_t *pfirst, chain_t *psecond)
{
	node_t *snf = NODE_GET_PTR(pfirst, node_t, chain);
	node_t *sns = NODE_GET_PTR(psecond, node_t, chain);
	if (snf->key == sns->key) {
		return 0;
	}
	else {
		return snf->key < sns->key ? -1 : 1;
	}
}
/* 交换链结点数据项 */
static void exchange(chain_t *pfirst, chain_t *psecond)
{
	node_t *snf = NODE_GET_PTR(pfirst, node_t, chain);
	node_t *sns = NODE_GET_PTR(psecond, node_t, chain);
	int temp = snf->key;
	snf->key = sns->key;
	sns->key = temp;
}

/* **************************************** */ 
/* 递归遍历树-中序 */ 
static void stree_travel_chain(chain_t *ptr, void (*visit)(chain_t*))
{
     if (ptr != NULL) {	  
	  stree_travel_chain(ptr->left, visit);
	  visit(ptr);
	  stree_travel_chain(ptr->right, visit);
     }
}
void stree_travel(stree_t stree, void (*visit)(chain_t*))
{
     stree_travel_chain(stree.root, visit);
}
/* **************************************** */ 
/* 递归查找树链 */ 
int stree_search_chain_recur(chain_t *pstart, chain_t *psearch,
			     int (*compare)(chain_t*,chain_t*))
{
     if (pstart != NULL) {
	  if (compare(pstart, psearch) == 0) {
	       return 1;
	  } else if (compare(pstart, psearch) < 0) {
	       return stree_search_chain_recur(pstart->left,
					       psearch, compare);
	  } else {
	       return stree_search_chain_recur(pstart->right,
					       psearch, compare);
	  }
     }
     return 0;
}
/* 迭代查找树链 */ 
static int stree_search_chain_iter(chain_t *pstart, chain_t *psearch,
				   int (*compare)(chain_t*,chain_t*))
{
     int ret_compare = compare(pstart, psearch);
     while (pstart != NULL) {
	  if (ret_compare == 0) {
	       return 1; /* find the key */ 
	  } else if ( ret_compare < 0) {
	       pstart = pstart->left;
	  } else {
	       pstart = pstart->right;
	  }
	  ret_compare = compare(pstart, psearch);
     }
     /* donot find the key */ 
     return 0;     
}
/* 查找树 */ 
int stree_search(stree_t stree, chain_t *pchain,
		 int (*compare)(chain_t*,chain_t*))
{
     return stree_search_chain_iter(stree.root, pchain, compare);
}
/* ********************************************** */
/* 最小值结点 */
chain_t *stree_minimum(stree_t stree)
{
     chain_t *pcur = stree.root;
     if (pcur == NULL) {
	  printf("the search tree is null\n");
	  exit(1);
     }
     while (pcur->left != NULL) {
	  pcur = pcur->left;
     }
     return pcur;
}
/* 最大值结点 */
chain_t *stree_maximum(stree_t stree)
{
     chain_t *pcur = stree.root;
     if (pcur == NULL) {
	  printf("the search tree is null\n");
	  exit(1);
     }
     while (pcur->right != NULL) {
	  pcur = pcur->right;
     }
     return pcur;
}
/* ********************************************** */
/* 后继链结点 */
chain_t *stree_successor(chain_t *pcur)
{
     if (pcur->right != NULL) {
	  pcur = pcur->right;
	  while (pcur->left != NULL) {
	       pcur = pcur->left;
	  }
	  return pcur;
     }
     while (pcur->parent != NULL && pcur == pcur->parent->right) {
	  pcur = pcur->parent;
     }
     return pcur->parent;
}
/* 前驱链结点 */
chain_t *stree_predecessor(chain_t *pcur)
{
     if (pcur->left == NULL) {
	  return pcur->parent;
     }
     while (pcur->left != NULL) {
	  pcur = pcur->left;
     }
     return pcur;
}

/* ********************************************** */
/* 插入结点 */
void stree_insert(stree_t *pstree, chain_t *pchain,
		       int (*compare)(chain_t*,chain_t*))
{
     pchain->parent = NULL;
     pchain->left = NULL;
     pchain->right = NULL;
     chain_t *prevptr = NULL;
     chain_t *ptr = pstree->root;
     while (ptr != NULL) {
	  prevptr = ptr;
	  if (compare(pchain, ptr) < 0) {
	       ptr = ptr->left;
	  } else {
	       ptr = ptr->right;
	  }
     }
     if (prevptr == NULL) {
	  pstree->root = pchain;
     } else if (compare(pchain, prevptr) < 0) {
	  prevptr->left = pchain;
	  pchain->parent = prevptr;	  
     } else {
	  prevptr->right = pchain;
	  pchain->parent = prevptr;
     }    
}
/* 删除结点 */ 
void stree_delete(stree_t *pstree, chain_t *pdel,
		  int (*compare)(chain_t*,chain_t*),
		  void (*exchange)(chain_t*, chain_t*))
{
     chain_t *real_pdel, *temp_pdel;
     if (pdel->left == NULL || pdel->right == NULL) {
	  real_pdel = pdel;
     } else {
	  real_pdel = stree_successor(pdel);
     }
     if (real_pdel->left != NULL) {
	  temp_pdel = real_pdel->left;
     } else {
	  temp_pdel = real_pdel->right;
     }
     if (temp_pdel != NULL) {
	  temp_pdel->parent = real_pdel->parent;
     }
     if (real_pdel->parent == NULL) {
	  pstree->root = temp_pdel;
     } else if (real_pdel == real_pdel->parent->left) {
	  real_pdel->parent->left = temp_pdel;
     } else {
	  real_pdel->parent->right = temp_pdel;
     }
     if (real_pdel != pdel) {
	  exchange(real_pdel, pdel);
     }
}
