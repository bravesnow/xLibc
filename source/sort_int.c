#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
/* *********************************** */ 
/* insert sort */ 
void sort_insert_int(int A[], int n)
{
    for (int i = 1; i < n; ++i) {
	int key = A[i];
	int j = i-1;
	while (j >= 0 && key < A[j]) {
	    A[j+1] = A[j];
	    --j;
	}
	A[j+1] = key;
    }
}

/* ************************************ */ 
/* merge sort */
static void merge_int(int A[], int start, int mid, int end)
{
    int nl = mid - start + 1;
    int nr = end - mid;
    int *left = malloc(sizeof(int)*(nl+1));
    int *right = malloc(sizeof(int)*(nr+1));
    for (int i = start; i <= mid; ++i) {
	left[i-start] = A[i];
    }
    left[nl] = INT_MAX;
    for (int j = mid + 1; j <= end; ++j) {
	right[j-mid-1] = A[j];
    }
    right[nr] = INT_MAX;
    int i = 0, j = 0;
    for (int k = start; k <= end; ++k) {
	A[k] = left[i] < right[j] ? left[i++] : right[j++];
    }
    free(left);
    free(right);
}
static void sort_merge_int_recursion(int A[], int start, int end)
{
    if (start < end) {
	int mid = (start+end)/2;
	sort_merge_int_recursion(A, start, mid);
	sort_merge_int_recursion(A, mid+1, end);
	merge_int(A, start, mid, end);
    }
}
void sort_merge_int(int A[], int n)
{
    sort_merge_int_recursion(A, 0, n-1);
}
/* *********************************** */
/* bubble sort */ 
void sort_bubble_int(int A[], int n)
{
    for (int i = 0; i < n; ++i) {
	for (int j = n-1; j >= i+1; --j) {
	    if (A[j] < A[j-1]) {
		int temp = A[j-1];
		A[j-1] = A[j];
		A[j] = temp;
	    }
	}
    }
}
/* **************************************** */
/* heap sort */
#define left(i) (2*(i+1)-1)
#define right(i) 2*(i+1)
#define parent(i) (i-1)/2
static void heap_heapify(int a[], int n, int i)
{
    int l = left(i);
    int r = right(i);
    int large = i;
    if (l < n && a[l] > a[i]) {
	large = l;
    }
    if (r < n && a[r] > a[large]) {
	large = r;
    }
    if (large != i) {
	int temp = a[i];
	a[i] = a[large];
	a[large] =temp;
	heap_heapify(a, n, large);
    }
}
static void heap_build_max(int a[], int n)
{
    for (int i = parent(n-1); i >= 0; --i) {
	heap_heapify(a, n, i);
    }
}
void sort_heap(int a[], int n)
{
    heap_build_max(a, n);
   
    for (int i = 0; i < n; ++i) {
	 int temp = a[0];
	 a[0] = a[n-i-1];
	 a[n-i-1] = temp;
	 heap_heapify(a, n-i-1, 0);
    }
}
/* priority queue */
int heap_extract_max(int a[], int n)
{
    int max = a[0];
    a[0] = a[n-1];
    heap_heapify(a, n-1, 0);
    return max;
}
void heap_increase_key(int a[], int n, int i, int key)
{
    int iparent = parent(i);
    while (iparent < n && a[i] > a[iparent]) {	
	i = iparent;
	iparent = parent(i);
    }
}
/* end queue */

/* ***************************** */
/* quick sort */
static int partition(int a[], int start, int end)
{
    int key = a[end];
    int i, k = start-1;
    for (i = start; i < end; ++i) {
	if (a[i] < key) {
	    ++k;
	    int temp = a[i];
	    a[i] = a[k];
	    a[k] = temp;
	}
    }
    ++k;
    int temp = a[k];
    a[k] = a[end];
    a[end] =temp;
    return k;
}
void sort_quick_recursion(int a[], int start, int end)
{
    if (start < end) {
	int mid = partition(a, start, end);
	sort_quick_recursion(a, start, mid-1);
	sort_quick_recursion(a, mid+1, end);
    }
}
void sort_quick_int(int a[], int n)
{
    sort_quick_recursion(a, 0, n-1);
}
