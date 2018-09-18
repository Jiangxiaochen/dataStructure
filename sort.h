#ifndef jxc_sort_h
#define jxc_sort_h
#include "bitree.h"
template < typename T > static inline void swap(T & a, T & b)
{
	T   tmp = a;
	a = b;
	b = tmp;
}

//插入排序{{{

template < typename T > void insertSort(T arr[], int n)
{								/* 直接插入 O(n2) */
	if (n <= 1)
		return;
	T   tmp;
	int i, j;
	for (i = 1; i < n; i++) {
		tmp = arr[i];
		j = i - 1;
		while (j >= 0 && tmp < arr[j]) {
			arr[j + 1] = arr[j];
			j--;
		}
		arr[j + 1] = tmp;
	}
}

template < typename T > void modifiedInsertSort(T arr[], int n, int delta)
{
//  int tmp;
	for (int i = delta; i < n; i += delta) {
		for (int j = i; j >= delta; j -= delta) {
			if (arr[j] < arr[j - delta])
//              tmp = arr[j], arr[j] = arr[j - delta], arr[j - delta] = tmp;
				swap(arr[j], arr[j - delta]);
			else
				break;
		}
	}
}

template < typename T > void shellSort(T arr[], int n)
{								/* shell sort O(n2) */
	int i, delta;
	for (delta = n / 2; delta > 0; delta /= 2)
		for (i = 0; i < delta; i++)
			modifiedInsertSort(&arr[i], n - i, delta);

}

//}}}
//选择排序{{{
template < typename T > void selectSort(T arr[], int n)
{								/* 直接选择 O(n2) */
	int min_index;
	for (int i = 0; i < n - 1; i++) {
		min_index = i;
		for (int j = i + 1; j < n; j++) {
			if (arr[j] < arr[min_index])
				min_index = j;
		}
		swap(arr[i], arr[min_index]);
	}
}

template < typename T > void heapSort(T arr[], int n)
{								/* 堆排序  O(nlogn) */
	MinHeap_jxc < T > min_heap(arr, n);
	for (int i = 0; i < n; i++) {
		min_heap.remove(0, arr[i]);
	}
}

//}}}
//交换排序{{{
template < typename T > void bubbleSort(T arr[], int n)
{								/* 冒泡排序，稳定的 O(n2) */
	bool no_swap;
	for (int i = 0; i < n - 1; i++) {
		no_swap = true;
		for (int j = n - 1; j > i; j--) {
			if (arr[j] < arr[j - 1]) {
				swap(arr[j], arr[j - 1]);
				no_swap = false;
			}
		}
		if (no_swap)
			return;
	}
}

template < typename T > int partition(T arr[], int left, int right)
{
	T   tmp = arr[right];
	while (left != right) {
		while (arr[left] <= tmp && right > left)
			left++;
		if (left < right)
			arr[right--] = arr[left];
		while (arr[right] >= tmp && right > left)
			right--;
		if (left < right)
			arr[left++] = arr[right];
	}
	arr[left] = tmp;
	return left;
}

template < typename T > void quickSort(T arr[], int left, int right)
{
	if (right <= left)
		return;
	int pivot = left + (right - left) / 2;
	swap(arr[right], arr[pivot]);
	pivot = partition(arr, left, right);
	quickSort(arr, left, pivot - 1);
	quickSort(arr, pivot + 1, right);
}


//}}}
//归并排序{{{

//}}}
#endif
