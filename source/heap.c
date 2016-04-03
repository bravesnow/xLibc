#include "heap.h"
static void mem_swap(void *vfirst, void *vsecond, size_t width)
{/* memory exchange */ 
    char *first = (char*)(vfirst);
    char *second = (char*)(vsecond);
    if (first != second) {
    	while (width--) {
    	    char temp = *first;
    	    *first = *second;
    	    *second = temp;
    	    ++first; ++second;
    	}
    }
}
/********* Heap Interface *********/ 
void heap_init(heap_t *ph, size_t width)
{
    array_init(&ph->array, width);
    ph->width = width;
    ph->cmp = NULL;
    ph->len = ph->array.len;
}
void *heap_top(heap_t heap)
{
    return array_value(heap.array, 0);
}
void *heap_value(heap_t heap, int index)
{
    return array_value(heap.array, index);
}
void heapify(heap_t *ph, int i)
{/* a single i heapify */ 
    int l = left(i);
    int r = right(i);
    int n = ph->len;
    int large = i;
    void *pl = heap_value(*ph, l);
    void *pr = heap_value(*ph, r);
    void *plarge = heap_value(*ph, large);
    
    if (l < n && (ph->cmp)(pl, plarge)>0) {
	large = l;
    }
    if (r < n && (ph->cmp)(pr, plarge)>0) {
	large = r;
    }
    if (large != i) {
	mem_swap(plarge, heap_value(*ph, i), ph->width);
	heapify(ph, large);
    }
}
void heap_make(heap_t *ph)
{
    int len = ph->len;
    for (int i = len-1; i >= 0; --i) {
	heapify(ph, i);
    }
}
void heap_add(heap_t *ph, void *value)
{
    int len = ph->len;
    array_insert(&ph->array, len, value);
    
    int i = len;
    void *ivalue = heap_value(*ph, i);
    int iparent = parent(i);
    void *ipvalue = heap_value(*ph, iparent);
    
    while (iparent >= 0 && (ph->cmp)(ipvalue, ivalue) < 0) {
	mem_swap(ipvalue, ivalue, ph->width);
	i = iparent;
	ivalue = heap_value(*ph, i);
	iparent = parent(i);
	ipvalue = heap_value(*ph, iparent);	
    }	
}
void heap_del(heap_t *ph)
{
    int len = ph->len;
    mem_swap(heap_value(*ph, 0), heap_value(*ph, len-1), ph->width);
    --ph->len;
    heapify(ph, 0);
}

void heap_destroy(heap_t *ph)
{
    array_destroy(&(ph->array));
}

