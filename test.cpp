#include <stdio.h>
#include "list.h"
#include "stack.h"
#include "ds_common.h"
#include <assert.h>
#include "queue.h"
#include "string.h"
#include "bitree.h"
#include "graph.h"

int main(int argc, const char *argv[])
{
	GraphAdjl_jxc gal(5);
	gal.setEdge(0,1,10);
	gal.setEdge(0,4,100);
	gal.setEdge(0,3,30);
	gal.setEdge(1,2,50);
	gal.setEdge(2,4,10);
	gal.setEdge(3,2,20);
	gal.setEdge(3,1,10);
	gal.setEdge(3,4,60);
	gal.print();
	Dist d_arr[5];
	dijkstra(gal, d_arr, 0);
	for (int i = 0; i < 5; i++) {
		cout << d_arr[i] << endl;
	}
	return 0;
}
