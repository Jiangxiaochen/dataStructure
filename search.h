#ifndef jxc_search_h
#define jxc_search_h

#include "utils.h"
#include "list.h"
#include <math.h>
#include <stdio.h>

//顺序检索算法(带监视哨&&位置调整) O(n){{{
template < typename T > static inline int seqSearch(T * arr, int len,
													const T & k)
{
	T   k0 = arr[0];
	if (k0 == k)
		return 0;
	arr[0] = k;
	while (arr[--len] != k);
	arr[0] = k0;				/* restore */

	if (len == 0)
		return -1;				/* not found */
	swap(arr[len], arr[len - 1]);	/* found, adjust pos */
	return len;
}

//}}}
//二分检索 O(logn){{{
template < typename T > static inline int binSearch(T * arr, int len,
													const T & k)
{
	int low = 0, high = len - 1, mid;
	while (low <= high) {
		mid = low + (high - low) / 2;
		if (arr[mid] == k)
			return mid;
		else if (arr[mid] > k)
			high = mid - 1;
		else
			low = mid + 1;
	}
	return -1;
}

//}}}
//散列方法{{{
static inline bool isPrime(int n)
{
	if (n <= 1)
		return false;
	if (n == 2 || n == 3)
		return true;
	if (n % 2 == 0)
		return false;
	int mid = sqrt(n);
	for (int i = 3; i <= mid; i += 2)
		if (n % i == 0)
			return false;
	return true;
}

static int SORT_M = -1;
static inline int hash(int key)
{
	return key % SORT_M;
}

static inline void buildHash(int *arr, int len, LinkList_jxc < int >*&ht)
{
	for (int i = len;; i++)
		if (isPrime(i)) {
			SORT_M = i;
			break;
		}
	ht = new LinkList_jxc < int >[SORT_M];
	for (int i = 0; i < len; i++) {
		ht[hash(arr[i])].append(arr[i]);
	}
}

//}}}
#endif
