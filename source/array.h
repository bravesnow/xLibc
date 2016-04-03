#ifndef _ARRAY_H
#define _ARRAY_H

#include <stddef.h> /* for size_t */

/* 宏：获得数组的第i个元素的地址 */ 
#define ARRAYi(a, i) ((char*)((a).array)+(i)*(a).width)
/* 动态数组结构体 */
typedef struct array {
    void *array; 
    size_t width;
    size_t len;
    size_t capacity;
} array_t;

/* *********************************** */ 
/* 初始化动态数组 */
void array_init(array_t *pa, size_t width);
void array_init_n(array_t *pa, size_t width, int n);
/* 释放动态数组 */
void array_destroy(array_t *pa);
/* *********************************** */
/* 设置数组元素的值 */
void array_set(array_t *pa, int i, void *value);
/* 插入新元素 */ 
void array_insert(array_t *pa, int i, void *value);
/* 删除元素 */ 
void array_delete(array_t *pa, int i);
/* *********************************** */ 
/* 获得数组长度 */
size_t array_len(array_t array);
/* 获得数组元素 */
void *array_value(array_t array, int index);
/* 遍历数组所有元素 */
void array_travel(array_t array, void (*visit)(void *value));

#endif
