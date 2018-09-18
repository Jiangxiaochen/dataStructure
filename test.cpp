#include "ds_common.h"


//gen tree{{{
void tree7_19(GraphBase_jxc & G)
{
	G.setEdge(0,1,10);
	G.setEdge(0,4,100);
	G.setEdge(0,3,30);
	G.setEdge(1,2,50);
	G.setEdge(2,4,10);
	G.setEdge(3,1,10);
	G.setEdge(3,2,20);
	G.setEdge(3,4,60);
}
void tree7_23(GraphBase_jxc & G)
{
	G.setEdge(0,1,20);
	G.setEdge(1,0,20);
	G.setEdge(0,4,1);
	G.setEdge(4,0,1);
	G.setEdge(1,2,6);
	G.setEdge(2,1,6);
	G.setEdge(1,3,4);
	G.setEdge(3,1,4);
	G.setEdge(4,5,15);
	G.setEdge(5,4,15);
	G.setEdge(3,5,12);
	G.setEdge(5,3,12);
	G.setEdge(3,6,8);
	G.setEdge(6,3,8);
	G.setEdge(2,6,2);
	G.setEdge(6,2,2);
	G.setEdge(5,6,10);
	G.setEdge(6,5,10);
}
//}}}

int main(int argc, const char *argv[])
{
	int arr[20];
	RAND_ARR(arr,20);
	insertSort(arr,20);
	PRINT_ARR(arr,20);
	SPLIT_LINE;
	RAND_ARR(arr,20);
	shellSort(arr,20);
	PRINT_ARR(arr,20);
	SPLIT_LINE;

	RAND_ARR(arr,20);
	selectSort(arr,20);
	PRINT_ARR(arr,20);
	SPLIT_LINE;

	RAND_ARR(arr,20);
	heapSort(arr,20);
	PRINT_ARR(arr,20);
	SPLIT_LINE;

	RAND_ARR(arr,20);
	bubbleSort(arr,20);
	PRINT_ARR(arr,20);
	SPLIT_LINE;

	RAND_ARR(arr,20);
	quickSort(arr,0,19);
	PRINT_ARR(arr,20);
	SPLIT_LINE;
}
