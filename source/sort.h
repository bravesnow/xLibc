#ifndef _SORT_H
#define _SORT_H
#include <stdlib.h>
#include <string.h>
/* int的比较函数 */ 
int compare(const void *first, const void *second)
{
     return *(int*)first - *(int*)second;
}
/* 内存交换函数 */ 
static void sort_swap(void *vfirst, void *vsecond, size_t width)
{
     char *first = (char*)(vfirst);
     char *second = (char*)(vsecond);
     if (first != second) {
	  while (width--) {
	       char temp = *first;
	       *first = *second;
	       *second = temp;
	       ++first;++second;
	  }
     }
}
/* *********************************************** */
/* 插入排序 */ 
void sort_insert(void *low, void *high, size_t width,
		 int (*comp)(const void*, const void*))
{
     char *cur, *key, *ptr;
     for (cur = (char)low+width; cur <= high; cur += width) {
	  key = cur;
	  for (ptr = cur-width; ptr >= low; ptr -= width) {
	       if (comp(key, ptr) < 0) {
		    sort_swap(key, ptr, width);
		    key = ptr;
	       }
	  }
     }
}
/* ************************************************* */
void merge(void *low, void *mid, void *high, size_t width,
	   int (*comp)(const void*, const void*))
{
     size_t nl = (char*)mid - (char*)low + width;
     size_t nr = (char*)high - (char*)mid + width;
     char *left = malloc(nl + width);
     char *right = malloc(nr + width);
     memcpy(left, low, nl);
     memcpy(right, mid, nr);
     int i = 0, j = 0, k = 0;
	 char *clow = (char*)low;
     while (i < nl/width && j < nr/width) {
	  if (compare(left+i*width, right+j*width) < 0) {
		  memcpy(clow + k*width, left + i*width, width);
	       ++k;++i;
	  } else {
		  memcpy(clow + k*width, right + j*width, width);
	       ++k;++j;
	  }
     }
     if (i == nl/width) {
		 memcpy(clow + k*width, right + j*width, nl + nr - k*width);
     } else {
		 memcpy(clow + k*width, left + i*width, nr + nl - k*width);
     }
}
void sort_merge(void *low, void *high, size_t width,
		int (*comp)(const void*, const void*))
{
     if (low < high) {
	  size_t length = (char*)high - (char*)low + width;
	  int n = length/width;
	  void *mid = (char*)low + n/2*width;
	  sort_merge(low, mid, width, comp);
	  sort_merge(mid, high, width, comp);
	  merge(low, mid, high, width, comp);
     }
}
/* heap sort */
void sort_heap(int a[], int n, int (*cmp)(void*,void*))
{
    heap_build_max(a, n, cmp);
   
    for (int i = 0; i < n; ++i) {
		int temp = a[0];
		a[0] = a[n-i-1];
		a[n-i-1] = temp;
		heap_heapify(a, n-i-1, 0, cmp);
    }
}
#endif
