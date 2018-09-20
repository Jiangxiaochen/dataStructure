#ifndef jxc_sort_h
#define jxc_sort_h
#include "bitree.h"
#include "utils.h"

//内排
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
template < typename T > void merge(T arr[], int left, int middle, int right)
{
	T   tmp[right - left + 1];
	for (int i = 0; i < right - left + 1; i++) {
		tmp[i] = arr[i + left];
	}
	int i1 = left, i2 = middle + 1;
	int i3 = left;
	while (i1 <= middle && i2 <= right) {
		if (tmp[i1 - left] <= tmp[i2 - left])
			arr[i3++] = tmp[i1++ - left];
		else
			arr[i3++] = tmp[i2++ - left];
	}
	while (i1 <= middle)
		arr[i3++] = tmp[i1++ - left];
	while (i2 <= right)
		arr[i3++] = tmp[i2++ - left];
}

template < typename T > void mergeSort(T arr[], int left, int right)
{
	if (right <= left)
		return;
	int middle = left + (right - left) / 2;
	mergeSort(arr, left, middle);
	mergeSort(arr, middle + 1, right);
	merge(arr, left, middle, right);
}

//}}}
//分配排序和索引排序{{{
template < typename T > void bucketSort(T arr[], int n, int max)
{								/* 桶式排序 O(m+n) */
	T  *tmp_arr = new T[n];
	int *count = new int[max];

	for (int i = 0; i < n; i++) {
		tmp_arr[i] = arr[i];
	}
	for (int i = 0; i < max; i++) {
		count[i] = 0;
	}
	for (int i = 0; i < n; i++) {
		count[arr[i]]++;
	}
	for (int i = 1; i < max; i++) {
		count[i] = count[i - 1] + count[i];
	}
	for (int i = n - 1; i >= 0; i--) {
		arr[--count[tmp_arr[i]]] = tmp_arr[i];
	}
}

template < typename T > void radixSort(T arr[], int n, int d, int r)
{								/* d:排序码个数 r:基数 */
	T  *tmp_arr = new T[n];
	int *count = new int[r];

	int radix = 1;
	int i, j, k;
	for (i = 1; i <= d; i++) {
		for (j = 0; j < r; j++)
			count[j] = 0;
		for (j = 0; j < n; j++)
			k = (arr[j] / radix) % r, count[k]++;
		for (j = 1; j < r; j++)
			count[j] = count[j - 1] + count[j];
		for (j = n - 1; j >= 0; j--) {
			k = (arr[j] / radix) % r;
			count[k]--;
			tmp_arr[count[k]] = arr[j];
		}
		for (j = 0; j < n; j++)
			arr[j] = tmp_arr[j];
		radix *= r;
	}
	delete[]tmp_arr;
	delete[]count;
}

template < typename T > void adjust(T arr[], int index_arr[], int n)
{
	T   tmp;
	int i, j, k;
	for (i = 0; i < n; i++) {
		j = i;
		tmp = arr[i];
		while (index_arr[j] != i) {
			k = index_arr[j];
			arr[j] = arr[k];
			index_arr[j] = j;
			j = k;
		}
		arr[j] = tmp;
		index_arr[j] = j;
	}
}

template < typename T > void indexSort(T arr[], int n)
{								/* 索引排序 */
	int i, j;
	int *index_arr = new int[n];
	for (i = 0; i < n; i++)
		index_arr[i] = i;
	for (i = 1; i < n; i++) {
		for (j = i; j > 0; j--) {
			if (arr[index_arr[j]] < arr[index_arr[j - 1]]) {
				swap(index_arr[j], index_arr[j - 1]);
			} else {
				break;
			}
		}
	}
	adjust(arr, index_arr, n);
}

//}}}
//外排{{{

#define OUTSORT_NAME "outsorttmp"
#define OUTSORT_SIZE 100000
template < typename T > void genSequence(FILE * fp_in, int &seq_num)
{
	int res, last;
	char name[100];
	FILE *fp_out_seq;
	T   in_val, min_val;
	T  *arr = new T[OUTSORT_SIZE];
	assert(arr);
	res = fread(arr, sizeof(T), OUTSORT_SIZE, fp_in);
	if (res != OUTSORT_SIZE && ferror(fp_in))
		exit(-10);				/* 读入失败 */
	if (res != OUTSORT_SIZE) {	/* 个数过少 */
		MinHeap_jxc < T > mhj(arr, res);
		sprintf(name, OUTSORT_NAME "%d", seq_num);
		assert((fp_out_seq = fopen(name, "wb")));
		while (mhj.top(min_val)) {
			assert(fwrite(&min_val, sizeof(T), 1, fp_out_seq) == 1);
		}
		fclose(fp_out_seq);
		fclose(fp_in);
		return;
	}
	//普通流程
	MinHeap_jxc < T > mhj(arr, OUTSORT_SIZE);
	while (1) {
		last = OUTSORT_SIZE - 1;
		sprintf(name, OUTSORT_NAME "%d", seq_num);
		assert((fp_out_seq = fopen(name, "wb")));
		while (last >= 0) {
			mhj.remove(0, min_val);
			assert(fwrite(&min_val, sizeof(T), 1, fp_out_seq) == 1);
			res = fread(&in_val, sizeof(T), 1, fp_in);
			if(res != 1 && ferror(fp_in)) ;
		}
	}
}
template < typename T > void merSequence(FILE * fp_in, int &seq_num)
{

}

template < typename T > void outSort(const char *in, const char *out)
{
	FILE *fp_in = fopen(in, "rb");
	FILE *fp_out = fopen(out, "wb");
	assert(fp_in && fp_out);
	int seq_num = 0;
	genSequence < T > (fp_in, seq_num);
	merSequence < T > (fp_out, seq_num);
}

//template < typename T > void replaceSelect(T arr[], int n, const char *in,
//                                         const char *out)
//{
//  int last = n - 1, res;
//  T   min_val, in_val;
//  FILE *fp_in, *fp_out;
//  fp_in = fopen(in, "rb");
//  fp_out = fopen(out, "wb");
//  assert(fp_in != NULL && fp_out != NULL);    /* 打开文件 */
//
//  res = fread(arr, sizeof(T), n, fp_in);
//  if (res != n && ferror(fp_in))
//      exit(-1);
//  if (res != n) {
//      MinHeap_jxc < T > mhj(arr, res);
//      while (mhj.top(min_val))
//          assert(fwrite(&min_val, sizeof(T), 1, fp_out) == 1);
//      fclose(fp_in);
//      fclose(fp_out);
//      return;
//  }
//
//  MinHeap_jxc < T > mhj(arr, n);
//  while(last >= 0){
//
//  }
//
//}
//}}}
#endif
