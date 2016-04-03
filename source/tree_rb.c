#include "tree_rb.h"

static int compare(rbchain_t *rb_ptr_f, rbchain_t *rb_ptr_s)
{
rbnode_t *struct_ptr_f = CHAIN_NODE_PTR(rb_ptr_f, rbnode_t, rbchain);
rbnode_t *struct_ptr_s = CHAIN_NODE_PTR(rb_ptr_s, rbnode_t, rbchain);
if (struct_ptr_f->key == struct_ptr_s->key) {
return 0;
} else {
return struct_ptr_f->key < struct_ptr_s->key ? -1 : 1;
}
}

/* 左旋二叉树 */ 
void rb_left_rotate(rbtree_t *ptree, rbchain_t *x)
{
     rbchain_t *y = x->right;
     x->right = y->left;
     if (y->left != ptree->nil) {
	  y->left->p = x;
     }
     y->p = x->p;
     if (x->p == ptree->nil) {
	  ptree->root = y;
     } else if (x == x->p->left){
	  x->p->left = y;
     } else {
	  x->p->right = y;
     }
     y->left = x;
     x->p = y;
}
/* 右旋二叉树 */ 
void rb_right_rotate(rbtree_t *ptree, rbchain_t *x)
{
     rbchain_t *y = x->left;
     x->left = y->right;
     if (y->right != ptree->nil) {
	  x = y->right->p;
     }
     x->p = y->p;
     if (x->p == ptree->nil) {
	  ptree->root = y;
     } else if (x->p->left == x) {
	  x->p->left = y;
     } else {
	  x->p->right = y;
     }
     y->right = x;
     x->p = y;
}
/* 红黑树插入结点 */ 	 
void rb_insert(rbtree_t *ptree, rbchain_t *z)
{
     rbchain_t *y = ptree->nil, *x = ptree->root;
     while (x != ptree->nil) {
	  y = x;
	  if (compare(z, x) < 0) {
	       x = x->left;
	  } else {
	       x = x->right;
	  }
     }
     z->p = y;
     if (y == ptree->nil) {
	  ptree->root = z;
     } else if (compare(z, y) < 0) {
	  y->left = z;
     } else {
	  y->right = z;
     }
     z->left = ptree->nil;
     z->right = ptree->nil;
     z->color = RED;
     rb_insert_fixup(ptree, z);
}
/* 红黑树插入结点，调整结点红黑属性 */ 
void rb_insert_fixup(rbtree_t *ptree, rbchain_t *z)
{
     while (z->p->color == RED) {
	  if (z->p->p->left == z->p) {
	       if (z->p->p->right->color == RED) {
		    z->p->color = BLACK;
		    z->p->p->color = RED;
		    z->p->p->right->color = BLACK;
		    z = z->p->p;
	       } else if (z == z->p->right) {
		    z = z->p;
		    rb_left_rotate(ptree, z);
	       }
	       z->p->color = BLACK;
	       z->p->p->color = RED;
	       rb_right_rotate(ptree, z);
	  }
	  else { /* change right and left */ 
	       if (z->p->p->right->color == RED) {
		    z->p->color = BLACK;
		    z->p->p->color = RED;
		    z->p->p->right->color = BLACK;
		    z = z->p->p;
	       } else if (z == z->p->right) {
		    z = z->p;
		    rb_right_rotate(ptree, z);
	       }
	       z->p->color = BLACK;
	       z->p->p->color = RED;
	       rb_left_rotate(ptree, z);
	  }
     }
}
/* 交换两个 */
void exchange(rbchain_t *pfirst, rbchain_t *psecond)
{
     rbnode_t *snf = CHAIN_NODE_PTR(pfirst, rbnode_t, rbchain);
     rbnode_t *sns = CHAIN_NODE_PTR(psecond, rbnode_t, rbchain);
     int temp = snf->key;
     snf->key = sns->key;
     sns->key = temp;
}
/* 结点删除 */ 
void rb_delete(rbtree_t *ptree, rbchain_t *z)
{
     rbchain_t *x, *y;
     /* find delete node - y */ 
     if (z->p->left == ptree->nil || z->p->right == ptree->nil) {
	  y = z;
     } else {
	  y = stree_successor(z);
     }
     /* find the single child of y - x */
     if (y->left != ptree->nil) {
	  x = y->left;
     } else {
	  x = y->right;
     }
     x->p = y->p;
     
     if (y->p == ptree->nil) { /* y is the root */
	  ptree->root = x;
     } else if (y == y->p->left) { /* y is the left child */ 
	  y->p->left = x;
     } else { /* y is the right child */ 
	  y->p->right = x;
     }
     /* y is the successor of z */ 
     if (y != z) {
exchange(z, y);
     }
     /* if y is black, then fixup the red-black property */ 
     if (y->color == BLACK) {
	  rb_delete_fixup(ptree, x);
     }
}
void rb_delete_fixup(rbtree_t *ptree, rbchain_t *x)
{
     rbchain_t *w;
     while (x != ptree->root && x->color == BLACK) {
	  if (x == x->p->left) { /* x is the left child */ 
	       w = x->p->right;
	       if (w->color == RED) {
		    w->color = BLACK;
		    x->p->color = RED;
		    rb_left_rotate(ptree, x->p);
		    w = x->p->right;
	       }
	       if (w->left->color == BLACK && w->right->color == BLACK) {
		    w->color = RED;
		    x = x->p;
	       } else if (w->right->color == BLACK) {
		    w->left->color = BLACK;
		    w->color = RED;
		    rb_right_rotate(ptree, w);
		    w = x->p->right;
	       } else {
		    w->color = x->p->color;
		    x->p->color = BLACK;
		    w->right->color = BLACK;
		    rb_left_rotate(ptree, x->p);
		    x = ptree->root;
	       }
	  } else { /* x is the left child */ 	       
	       w = x->p->left;
	       if (w->color == RED) {
		    w->color = BLACK;
		    x->p->color = RED;
		    rb_right_rotate(ptree, x->p);
		    w = x->p->left;
	       }
	       if (w->right->color == BLACK && w->left->color == BLACK) {
		    w->color = RED;
		    x = x->p;
	       } else if (w->left->color == BLACK) {
		    w->right->color = BLACK;
		    w->color = RED;
		    rb_left_rotate(ptree, w);
		    w = x->p->left;
	       } else {
		    w->color = x->p->color;
		    x->p->color = BLACK;
		    w->left->color = BLACK;
		    rb_right_rotate(ptree, x->p);
		    x = ptree->root;
	       }	       
	  }
     }
     x->color = BLACK;
}
