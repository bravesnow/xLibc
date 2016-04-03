#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"
/* ***************************************** */
/* 初始化动态数组 */ 
void array_init(array_t *pa, size_t width)
{
    pa->array = NULL;
    pa->width = width;
    pa->len = 0;
    pa->capacity = 0;
}
void array_init_n(array_t *pa, size_t width, int n)
{
    pa->array = malloc(width*n);
    pa->width = width;
    pa->len = n;
    pa->capacity = n;
}
/* 释放动态数组 */ 
void array_destroy(array_t *pa)
{
    if (pa->array != NULL) {
        free(pa->array);
    }
}

/* ***************************************** */
/* 置数组元素的值 */ 
void array_set(array_t *pa, int i, void *value)
{
    if ((size_t)i >= pa->len) {
        printf("index over range\n");
        exit(1);
    }
    memcpy(ARRAYi(*pa, i), value, pa->width);
}
/* 插入新元素 */ 
void array_insert(array_t *pa, int i, void *value)
{
    if ( pa->len >= pa->capacity) {
        pa->capacity = 2*(pa->capacity)+1; /* 预分配内存策略 */ 
        pa->array = realloc(pa->array, pa->width*pa->capacity);
    }
    if ((size_t)i > pa->len) {
        printf("index error!\n");
        exit(1);
    }
    int k = pa->len;
    for (; k > i; --k) {
        memcpy(ARRAYi(*pa, k), ARRAYi(*pa, k-1), pa->width);
    }
    memcpy(ARRAYi(*pa, i), value, pa->width);
    
    ++pa->len;
}
/* 删除元素 */ 
void array_delete(array_t *pa, int i)
{
    if ((size_t)i >= pa->len) {
        printf("array overflow!\n");
        exit(1);
    }
    for (; (size_t)i < pa->len-1; ++i) {
        memcpy(ARRAYi(*pa, i), ARRAYi(*pa, i+1), pa->width);
    }
    --(pa->len);
}

/* ***************************************** */
/* 获得数组长度 */
size_t array_len(array_t array)
{
    return array.len;
}
/* 获得数组元素 */
void *array_value(array_t array, int index)
{
    return ARRAYi(array, index);
}
/* 遍历数组所有元素 */
void array_travel(array_t array, void (*visit)(void *value))
{
    for (size_t i = 0; i < array.len; ++i) {
        visit(ARRAYi(array, i));
    }
}

