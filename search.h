#ifndef jxc_search_h
#define jxc_search_h

#include "utils.h"

//顺序检索算法(带监视哨&&位置调整){{{
template < typename T > int seqSearch(T *arr, int len, const T& k)
{
	T k0 = arr[0];
	if(k0 == k) return 0;
	arr[0] = k;
	while(arr[--len] != k);
	arr[0] = k0;                         /* restore */

	if(len == 0) return -1;                     /* not found */
	swap(arr[len], arr[len-1]);                 /* found, adjust pos */
	return len;
}
//}}}

#endif
