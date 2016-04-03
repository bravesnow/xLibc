#ifndef _LIST_H
#define _LIST_H
#include <stddef.h>

/* 通过结构体成员指针获得结构体指针 */ 
#define chain_get_node(mptr,s,m) ((s*)((char*)(mptr)-offsetof(s,m)))

/* 链接两个结点的结构体 */ 
typedef struct chain {
    struct chain *prev;
    struct chain *next;
} chain_t;

/* 链表 */ 
typedef struct list {
    int len;
    struct chain *head;
} list_t;

/* 初始化链表 */ 
void list_init(list_t *plist);

/**********插入与删除**************/ 
/* 从头插入链表 */ 
void list_add_head(list_t *plist, chain_t *new);
/* 给定索引插入 */
void list_insert_index(list_t *plist, int i, chain_t *pchain);
/* 在给定指针的结点之后插入新结点 */ 
void list_insert(list_t *plist, chain_t *current, chain_t *new);
/* 删除给定指针的结点 */
void list_delete(list_t *plist, chain_t *this);
 
/* 链表长度 */
int list_len(list_t list);
/* 遍历链表 */ 
void list_travel(list_t list, void (*visit)(chain_t *));
/* 访问节点数据*/
void list_visit_data(chain_t *pchain);

/* ****************************************** */ 
/* 可扩展自定义数据结点 */ 
typedef struct node {
    int value;
    chain_t chain;
} node_t;

#endif
