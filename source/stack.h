#ifndef _STACK_H
#define _STACK_H

#include "array.h"

typedef struct stack{
    array_t array;
    int top;//栈顶位置
} stack_t;

/* 初始化栈 */ 
void stack_init(stack_t *pstack, size_t width);
void stack_destroy(stack_t *pstack);
/* 入栈和出栈 */ 
void stack_push(stack_t *pstack, void *value);
void stack_pop(stack_t *pstack);
/* 栈空判断 */ 
int stack_empty(stack_t stack);
/* 返回栈顶元素 */ 
void *stack_top(stack_t stack);


#endif
