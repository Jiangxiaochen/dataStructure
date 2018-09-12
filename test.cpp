#include <stdio.h>
#include "list.h"
#include "stack.h"
#include "ds_common.h"
#include <assert.h>
#include "queue.h"
#include "string.h"
#include "tree.h"
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
	BST_jxc < int >bstj;
	int arr[] = { 50, 92, 88, 20, 100, 5, 35, 53, 19, 55 };
	NodeBiTree_jxc < int >*tmp;
	for (unsigned i = 0; i < sizeof(arr) / sizeof(int); i++) {
		tmp = new NodeBiTree_jxc < int >(arr[i]);
		bstj.insertNode(tmp);
	}
	bstj.inOrder(func);
	SPLIT_LINE;
	bstj.preOrder(func);
	SPLIT_LINE;
//  for (unsigned i = 0; i < sizeof(arr)/sizeof(int); i++) {
//      printf("%p\n", bstj.searchNode(arr[i]));
//  }
//  printf("%lu\n", sizeof(NodeBiTree_jxc<int>));
	bstj.deleteNode(55);
	bstj.preOrder(func);
	SPLIT_LINE;
	bstj.deleteNode(50);
	bstj.preOrder(func);
	return 0;
}
