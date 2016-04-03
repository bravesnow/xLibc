#ifndef _SLIST_H
#define _SLIST_H

#include <stddef.h>
/* 通过结构体成员指针获得结构体指针 */ 
#define chain_get_node(mptr,s,m) ((s*)((char*)(mptr)-offsetof(s,m)))

/* 链结构 */
typedef struct chain_single {
    struct chain_single *next;
} schain_t;

/* 单链表 */ 
typedef struct slist {
     int len;
     struct chain_single *head;
} slist_t;

void slist_init(slist_t *plist);
void slist_destroy(slist_t *plist);

void slist_add_head(slist_t *plist, schain_t *pchain);
void slist_insert(slist_t *plist, int i, schain_t *pchain);
void slist_delete(slist_t *plist, int i);

int slist_len(slist_t list);
schain_t *slist_get_chain(slist_t list, int i);
void slist_travel(slist_t list, void (*visit)(schain_t *));

/*----------------------------------------*/
/* 
typedef struct node {
//可扩展自定义数据结点 
     int val;
     struct chain_single schain;
} node_t;
 
void visit(schain_t *pschain)
{// 可扩展自定义通过链接结点访问数据
     node_t *pnode = chain_get_node(pschain, node_t, schain);
     printf("%d\n", pnode->val);
}
*/

#endif
