#include <stdio.h>
#include "list.h"
#include "stack.h"
#include "ds_common.h"
#include <assert.h>
#include "queue.h"
#include "string.h"
#include "bitree.h"
#include "graph.h"
template < typename T > void func(NodeBiTree_jxc < T > *node)
{
	cout << node->data << ":";
	cout << "l_c=";
	if(node->l_c) cout << node->l_c->data;
	else cout << "NULL";
	cout << " ";
	cout << "r_c=";
	if(node->r_c) cout << node->r_c->data;
	else cout << "NULL";
	cout << endl;
}

int main(int argc, const char *argv[])
{
	GraphAdjm_jxc gaj(4);
	gaj.print();
	SPLIT_LINE;
	gaj.setEdge(0,1,1);
	gaj.setEdge(0,2,1);
	gaj.setEdge(2,3,1);
	gaj.setEdge(3,0,1);
	gaj.print();
	SPLIT_LINE;
	GraphAdjl_jxc gal(4);
	gal.setEdge(0,1,1);
	gal.setEdge(0,2,1);
	gal.setEdge(2,3,1);
	gal.setEdge(3,0,1);
	gal.print();
}
