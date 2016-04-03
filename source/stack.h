#ifndef _STACK_H
#define _STACK_H

#include "array.h"

typedef struct stack{
    array_t array;
    int top;//ջ��λ��
} stack_t;

/* ��ʼ��ջ */ 
void stack_init(stack_t *pstack, size_t width);
void stack_destroy(stack_t *pstack);
/* ��ջ�ͳ�ջ */ 
void stack_push(stack_t *pstack, void *value);
void stack_pop(stack_t *pstack);
/* ջ���ж� */ 
int stack_empty(stack_t stack);
/* ����ջ��Ԫ�� */ 
void *stack_top(stack_t stack);


#endif
