#include <stdio.h>
#include <stdlib.h>
#include "list.h"

/* 初始化链表 */ 
void list_init(list_t *plist)
{
    plist->len = 0;
    plist->head = (chain_t*)malloc(sizeof(chain_t));
    if (plist->head == NULL)
    {
        printf("list init fail!\n");
        exit(1);
    }
    plist->head->prev = NULL;
    plist->head->next = NULL;   
}
/* 从头插入链表 */ 
void list_add_head(list_t *plist, chain_t *new)
{

    new->next = plist->head->next;   
    if (plist->head->next)
    {
        plist->head->next->prev = new;
    }
    new->prev = plist->head;
    plist->head->next = new;   
    ++(plist->len);
}
/* 获得给定索引元素的结点指针 */ 
chain_t *list_get_chain(list_t list, int i)
{
    if (i >= list.len) {
	    printf("index overflow\n");
	    exit(1);
    }
    chain_t *ptr = list.head;
    for (int k = 0; k <= i; ++k) {
	    ptr = ptr->next;
    }
    return ptr;
}
void list_insert_index(list_t *plist, int i, chain_t *pchain)
{
    if (i > plist->len) {
        printf("%d\n", plist->len);
        printf("index over range\n");
        exit(1);
    }
    chain_t *prev = list_get_chain(*plist, i-1);
    list_insert(plist, prev, pchain);
    ++plist->len;
}
/* 在给定指针的结点之后插入新结点 */ 
void list_insert(list_t *plist, chain_t *current, chain_t *new)
{
    if (current == NULL) {
	    printf("chain null(insert)\n");
	    exit(1);
    }
    new->next = current->next;
    new->prev = current;
    if (current->next != NULL) {
	    current->next->prev = new;
    }    
    current->next = new;
    ++(plist->len);
}
/* 删除给定指针的结点 */ 
void list_delete(list_t *plist, chain_t *this)
{
    if (this == NULL) {
	printf("chain null(delete)\n");
	exit(1);
    }
    if (this->prev != NULL) {
	this->prev->next = this->next;
    }
    if (this->next != NULL) {
	this->next->prev = this->prev;
    }
    --(plist->len);
}

/* 链表长度 */
int list_len(list_t list)
{
    return list.len;
}

/* 访问链表结点的数据 */
void list_visit_data(chain_t *pchain)
{
    node_t *pnode = chain_get_node(pchain, node_t, chain);
    printf("%d\n",pnode->value);
}


/* 遍历链表 */ 
void list_travel(list_t list, void (*visit)(chain_t *))
{
    struct chain *pchain = list.head->next;
     
    while (pchain) {
	visit(pchain);
	pchain = pchain->next;
    }
}

