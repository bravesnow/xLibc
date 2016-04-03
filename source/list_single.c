#include <stdio.h>
#include <stdlib.h>
#include "list_single.h"

/* 初始化列表结点 */ 
void slist_init(slist_t *plist)
{
    plist->len = 0;
    plist->head = malloc(sizeof(schain_t));
    plist->head->next = NULL;
}
/* 释放链表头结点 */ 
void slist_destroy(slist_t *plist)
{
    free(plist->head);
}
/* 获得给定索引元素的结点指针 */ 
schain_t *slist_get_chain(slist_t list, int i)
{
    if (i >= list.len) {
	printf("index overflow\n");
	exit(1);
    }
    schain_t *p = list.head;
    for (int k = 0; k <= i; ++k) {
	p = p->next;
    }
    return p;
}
/* 从头结点插入元素 */ 
void slist_add_head(slist_t *plist, schain_t *pchain)
{
    pchain->next = plist->head->next;
    plist->head->next = pchain;
    ++plist->len;
}
/* 在给定索引位置插入 */ 
void slist_insert(slist_t *plist, int i, schain_t *pchain)
{
    if (i > plist->len) {
	printf("%d\n",plist->len);
	printf("index over range\n");
	exit(1);
    }
    schain_t *prev = slist_get_chain(*plist, i-1);
    pchain->next = prev->next;
    prev->next = pchain;
    ++plist->len;
}
/* 删除给定索引位置元素 */ 
void slist_delete(slist_t *plist, int i)
{
    if (i >= plist->len) {
	printf("index over range\n");
	exit(1);
    }
    schain_t *prev = slist_get_chain(*plist, i-1);
    prev->next = prev->next->next;
    --plist->len;
}
/* 获取列表长度 */
int slist_len(slist_t list)
{
    return list.len;
}
 
void slist_travel(slist_t list, void (*visit)(schain_t *))
{
    schain_t *pchain = (list.head)->next;
     
    while (pchain) {
	visit(pchain);
	pchain = pchain->next;
    }
}
