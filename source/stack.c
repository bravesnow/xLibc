#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "stack.h"

/* ��ʼ����̬ջ */ 
void stack_init(stack_t *pstack, size_t width)
{
    array_init(&(pstack->array), width);
    pstack->top = -1;
}
/* �ͷŶ�̬ջ */ 
void stack_destroy(stack_t *pstack)
{
    array_destroy(&(pstack->array));
}
/* ��ջ */ 
void stack_push(stack_t *pstack, void *value)
{     
    array_insert(&pstack->array, (pstack->array).len, value);
    pstack->top = pstack->top + 1;    
}
/* ��ջ */ 
void stack_pop(stack_t *pstack)
{
    if (pstack->top == -1){
	printf("stack empty!\n");
	exit(1);
    }
    array_delete(&pstack->array, pstack->top);
    pstack->top = pstack->top - 1;
}
/* �ж�ջ�Ƿ�Ϊ�� */ 
int stack_empty(stack_t stack)
{
    return (stack.top == -1) ? 1 : 0;
}
/* ����ջ��Ԫ�� */ 
void *stack_top(stack_t stack)
{
    if (stack.top == -1){
	printf("stack empty!\n");
	exit(1);
    }
    return array_value(stack.array, stack.top);
}



