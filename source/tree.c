#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

/* ����ǰ����չ�����б�ݹ鹹�������� */ 
void tree_create(tree_t *ptree, void *values_array)
{
     static int offset = 0;
     void **values = (void**)values_array; /* (void*)ǿ��ת��(void**) */ 
     void *value = *(values + offset);
     ++offset;
     if (value == NULL) {
	  ptree->root = NULL;
     } else {
	  node_t *pnode = malloc(sizeof(node_t));
	  if (pnode == NULL) {
	       exit(1);
	  }
	  pnode->value = value;
	  ptree->root = &(pnode->chain);
	  tree_t *ptree_left = TREE_GET_PTR(ptree->root->first);
	  tree_t *ptree_right = TREE_GET_PTR(ptree->root->second);
	  	  
	  tree_create(ptree_left, values);
	  tree_create(ptree_right, values);
     }
}
static void tree_travel_chain(chain_t *pchain)
{
      if (pchain != NULL) {	  
	  visit(pchain);
	  tree_travel_chain(pchain->first);
	  tree_travel_chain(pchain->second);
      }
}
void tree_travel(tree_t tree)
{
     tree_travel_chain(tree.root);
}



