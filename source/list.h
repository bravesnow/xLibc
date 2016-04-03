#ifndef _LIST_H
#define _LIST_H
#include <stddef.h>

/* ͨ���ṹ���Աָ���ýṹ��ָ�� */ 
#define chain_get_node(mptr,s,m) ((s*)((char*)(mptr)-offsetof(s,m)))

/* �����������Ľṹ�� */ 
typedef struct chain {
    struct chain *prev;
    struct chain *next;
} chain_t;

/* ���� */ 
typedef struct list {
    int len;
    struct chain *head;
} list_t;

/* ��ʼ������ */ 
void list_init(list_t *plist);

/**********������ɾ��**************/ 
/* ��ͷ�������� */ 
void list_add_head(list_t *plist, chain_t *new);
/* ������������ */
void list_insert_index(list_t *plist, int i, chain_t *pchain);
/* �ڸ���ָ��Ľ��֮������½�� */ 
void list_insert(list_t *plist, chain_t *current, chain_t *new);
/* ɾ������ָ��Ľ�� */
void list_delete(list_t *plist, chain_t *this);
 
/* ������ */
int list_len(list_t list);
/* �������� */ 
void list_travel(list_t list, void (*visit)(chain_t *));
/* ���ʽڵ�����*/
void list_visit_data(chain_t *pchain);

/* ****************************************** */ 
/* ����չ�Զ������ݽ�� */ 
typedef struct node {
    int value;
    chain_t chain;
} node_t;

#endif
