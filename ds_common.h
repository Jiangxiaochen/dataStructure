#ifndef ds_jxc_h
#define ds_jxc_h

#include "sort.h"
#include <ctype.h>
#include <assert.h>
#include <iostream>
#include <stdio.h>
#include <queue>
#include <vector>
#include <functional>
#include "bitree.h"
#include "graph.h"
#include "tree.h"
#include "list.h"
#include "stack.h"
using std::max;
using std::min;
using std::cin;
using std::cout;
using std::endl;
using std::ostream;
#define SPLIT_LINE printf("---------------------------------------\n")
#define INFINITY_JXC 9999
#define PRINT_ARR(ARR,LEN){\
	for (int i = 0; i < LEN; i++) {\
		cout << ARR[i] << " ";\
	}\
	cout << endl;\
}
#define RAND_ARR(ARR,LEN){\
	srand(time(NULL));\
	for (int i = 0; i < LEN; i++) {\
		ARR[i] = rand()%2000;\
	}\
}
#define LEN_ARR(ARR) (int)(sizeof(ARR)/sizeof(ARR[0]))

//最长子序列{{{

typedef struct jxc_pair {
	long start;
	long len;
} jxc_pair;

template < typename T >
	static inline jxc_pair findLongestSubarr(T arr[], long len)
{								/* 最长子序列 */
	long i, length, j1, j2, k, pos;
	for (i = 0, length = 1; i < len - 1; i++) {
		for (j1 = j2 = k = i; k < len - 1 && arr[k] < arr[k + 1]; k++, j2++);
		if (length < j2 - j1 + 1) {
			length = j2 - j1 + 1;
			pos = i;
		}
	}
	jxc_pair p = { pos, length };
	return p;
}

//}}}
//中缀转后缀&表达式计算{{{

static inline int oprCmp(int opr1, int opr2)
{
	if (opr1 == '+' || opr1 == '-') {
		if (opr2 == '+' || opr2 == '-')
			return 0;
		if (opr2 == '*' || opr2 == '/')
			return -1;
	}
	if (opr1 == '*' || opr1 == '/') {
		if (opr2 == '+' || opr2 == '-')
			return 1;
		if (opr2 == '*' || opr2 == '/')
			return 0;
	}
	return -2;
}

static inline bool inFix2PostFix(const char *in_fix_expr, char *post_fix_buf,
								 int buf_len)
{								/* 中缀转后缀 */
	static const char *opr = "+-*/";
	memset(post_fix_buf, '\0', buf_len);
	LinkStack_jxc < int >lsj;
	int in_len = strlen(in_fix_expr);
	int index = 0;

	for (int i = 0; i < in_len; i++) {
		if (isdigit(in_fix_expr[i]))
			post_fix_buf[index++] = in_fix_expr[i];
		else if (in_fix_expr[i] == '(') {
			lsj.push(in_fix_expr[i]);
		} else if (in_fix_expr[i] == ')') {
			if (lsj.isEmpty()) {
				fprintf(stderr, "in_fix_expr format error\n");
				return false;
			}
			int tmp;
			while (lsj.pop(tmp)) {
				if (tmp != '(') {
					post_fix_buf[index++] = tmp;
				} else {
					break;
				}
			}
		} else if (strchr(opr, in_fix_expr[i]) != NULL) {
			int tmp;
			while (!lsj.isEmpty()) {
				lsj.top(tmp);
				if (tmp == '(')
					break;
				if (oprCmp(tmp, in_fix_expr[i]) == -1)
					break;
				lsj.pop(tmp);
				post_fix_buf[index++] = tmp;
			}
			lsj.push(in_fix_expr[i]);
		} else if (in_fix_expr[i] == ' ') {
			post_fix_buf[index++] = ' ';
		}
	}
	int tmp;
	while (!lsj.isEmpty()) {
		lsj.pop(tmp);
		if (tmp == '(')
			return false;
		post_fix_buf[index++] = tmp;
	}
	return true;
}

static inline int postFixResult(const char *post_fix_buf)
{
	char num[100] = { '\0' };
	LinkStack_jxc < int >lsj;
	int buf_len = strlen(post_fix_buf);
	for (int i = 0; i < buf_len; i++) {
		if (isdigit(post_fix_buf[i])) {
			memset(num, '\0', 100);
			int index = 0;
			while (isdigit(post_fix_buf[i])) {
				num[index++] = post_fix_buf[i];
				i++;
			}
			lsj.push(atoi(num));
			i--;
		} else if (strchr("+-*/", post_fix_buf[i]) != NULL) {
			int a, b;
			assert(lsj.pop(b));
			assert(lsj.pop(a));
			if (post_fix_buf[i] == '+')
				lsj.push(a + b);
			if (post_fix_buf[i] == '-')
				lsj.push(a - b);
			if (post_fix_buf[i] == '*')
				lsj.push(a * b);
			if (post_fix_buf[i] == '/')
				lsj.push(a / b);
		}
	}
	int result;
	lsj.pop(result);
	return result;
}

//}}}
//背包问题&递归转迭代{{{

bool knap(int s, int *w, int n, LinkStack_jxc < int >*lsj)
{								/* 背包问题递归版本 */
	if (s == 0)
		return true;
	if (s < 0 || (s > 0 && n < 1))
		return false;
	if (knap(s - w[n - 1], w, n - 1, lsj)) {
		lsj->push(w[n - 1]);
		return true;
	} else {
		return knap(s, w, n - 1, lsj);
	}
}

enum RdType { L0, L1, L2 };
typedef struct KnapNode {
	int s, n;
	RdType rd;
	bool k;
} KnapNode;

static LinkStack_jxc < KnapNode > *lsj;
static LinkStack_jxc < int >*lsj_res;
static KnapNode tmp;
static int *w;
bool _knap_it(int s, int n);
bool _knap_it_ex(int s, int n);
bool knap_it(int s, int *ws, int n, LinkStack_jxc < int >*l)
{								/* 迭代版本包装函数 */
	w = ws;
	lsj_res = l;
	lsj = new LinkStack_jxc < KnapNode >;
	bool res = _knap_it_ex(s, n);
	delete lsj;
	return res;
}

#define DEBUG false
#define printKnapNode(i1,node1){\
	if(DEBUG){\
	printf("label%d: s:%d n:%d rd:%d k:%d stack_len:%d\n", i1 ,node1.s, node1.n,node1.rd,node1.k,lsj->length());\
	for (int i = 0; i < lsj->length(); i++) {\
		KnapNode node = lsj->getValue(i);\
		printf("lsj%d: s:%d n:%d rd:%d k:%d\n", i ,node.s, node.n,node.rd,node.k);\
	}\
	}\
}

KnapNode x;
bool _knap_it_ex(int s, int n)
{								/* 迭代版本实现 */
	tmp.s = s, tmp.n = n, tmp.rd = L0;	/* 非递归入口 */
	lsj->push(tmp);
	printKnapNode(-1, tmp);
  label0:						/*  递归入口 */
	lsj->pop(tmp);
	printKnapNode(0, tmp);
	if (tmp.s == 0) {			/*out1 */
		tmp.k = true;
		lsj->push(tmp);
		goto label3;
	}
	if (tmp.s < 0 || (tmp.s > 0 && tmp.n < 1)) {	/*  out2 */
		tmp.k = false;
		lsj->push(tmp);
		goto label3;
	}
	lsj->push(tmp);				/* repush */
	x.s = tmp.s - w[tmp.n - 1];
	x.n = tmp.n - 1;
	x.rd = L1;
	lsj->push(x);
	goto label0;				/* 规则1压栈并进入递归入口 */
  label1:
	lsj->pop(x);
	printKnapNode(1, x);
	if (tmp.k == true) {
		x.k = true;
		lsj->push(x);
		lsj_res->push(w[tmp.n]);
		goto label3;
	}
	lsj->push(x);
	tmp.s = x.s;
	tmp.n = x.n - 1;
	tmp.rd = L2;
	lsj->push(tmp);
	goto label0;				/* rule 2 push */
  label2:
	lsj->pop(x);
	printKnapNode(2, x);
	x.k = tmp.k;
	lsj->push(x);

  label3:						/* 递归出口 */
	lsj->pop(tmp);
	printKnapNode(3, tmp);
	switch (tmp.rd) {
	case L0:
		return tmp.k;
		break;
	case L1:
		goto label1;
		break;
	case L2:
		goto label2;
		break;
	default:
		return false;
	}

}

bool _knap_it(int s, int n)
{								/* 迭代版本实现 */
	tmp.s = s, tmp.n = n, tmp.rd = L0;	/* 非递归入口 */
	lsj->push(tmp);
	printKnapNode(-1, tmp);
  label0:						/*  递归入口 */
	lsj->pop(tmp);
	printKnapNode(0, tmp);
	if (tmp.s == 0) {			/*out1 */
		tmp.k = true;
		lsj->push(tmp);
		goto label3;
	}
	if (tmp.s < 0 || (tmp.s > 0 && tmp.n < 1)) {	/*  out2 */
		tmp.k = false;
		lsj->push(tmp);
		goto label3;
	}
	lsj->push(tmp);				/* repush */
	tmp.s -= w[tmp.n - 1];
	tmp.n -= 1;
	tmp.rd = L1;
	lsj->push(tmp);
	goto label0;				/* 规则1压栈并进入递归入口 */
  label1:
	if (tmp.k == true) {
		lsj_res->push(w[tmp.n]);
		lsj->pop(tmp);
		tmp.k = true;
		lsj->push(tmp);
		goto label3;
	}
	lsj->top(tmp);
	tmp.n -= 1;
	tmp.rd = L2;
	lsj->push(tmp);
	goto label0;				/* rule 2 push */
  label2:
	if (tmp.k == true) {
		lsj->pop(tmp);
		tmp.k = true;
		lsj->push(tmp);
	}
  label3:						/* 递归出口 */
	lsj->pop(tmp);
	printKnapNode(3, tmp);
	switch (tmp.rd) {
	case L0:
		return tmp.k;
		break;
	case L1:
		goto label1;
		break;
	case L2:
		goto label2;
		break;
	default:
		return false;
	}

}

//}}}
//最大K个数{{{
void quickSearch(int arr[], int left, int right, int len, int k)
{
	if (right <= left)
		return;
	int pivot = left + (right - left) / 2;
	swap(arr[right], arr[pivot]);
	pivot = partition(arr, left, right);
	int num = len - pivot;
	if (num == k)
		return;
	if (num > k) {
		quickSearch(arr, pivot + 1, right, len, k);
	} else {
		quickSearch(arr, left, pivot - 1, len, k);
	}
}

void findKMax_quickSort(int *data, int len, int k, int *arr)
{								/* 快排 O(n*logk) */
	quickSearch(data, 0, len - 1, len, k);
	for (int i = len - k; i < len; i++)
		arr[i - len + k] = data[i];
}

void findKMax_minHeap(const int *data, int len, int k, int *arr)
{								/* 最小堆 O(n*logk) */
	static MinHeap_jxc < int >mh(k);
	mh.clear();
	for (int i = 0; i < k; i++) {
		mh.insert(data[i]);
	}
	int res;
	for (int i = k; i < len; i++) {
		if (data[i] > mh.top(res)) {
			mh.remove(0, res);
			mh.insert(data[i]);
		}
	}
	int index = 0;
	while (mh.remove(0, res)) {
		arr[index++] = res;
	}

}

//}}}
//Dijkstra单源最短路径{{{
class Dist {
  public:
	int index, length, pre;
	bool operator>(const Dist & rhs) {
		return length > rhs.length;
	} bool operator<(const Dist & rhs) {
		return length < rhs.length;
	}
	bool operator==(const Dist & rhs) {
		return length == rhs.length;
	}
};

ostream & operator<<(ostream & os, const Dist & d)
{
	char s[100];
	sprintf(s, "(i:%d,l:%d,p:%d)", d.index, d.length, d.pre);
	os << s << " ";
	return os;
}

void dijkstra(GraphBase_jxc & g, Dist * d_arr, int s)
{
	int *mark = g.mark();
	int v_num = g.verticesNum();
	int e_num = g.edgesNum();
	memset(mark, 0, v_num * sizeof(int));
	for (int i = 0; i < v_num; i++) {
		mark[i] = 0;
		d_arr[i].index = i, d_arr[i].length = INFINITY_JXC, d_arr[i].pre = s;
	}
	d_arr[s].length = 0;
	MinHeap_jxc < Dist > min_heap(e_num);
	min_heap.insert(d_arr[s]);
	for (int i = 0; i < v_num; i++) {
		bool found = false;
		Dist d;
		while (!min_heap.isEmpty()) {
			min_heap.remove(0, d);
			if (mark[d.index] == 0) {
				found = true;
				break;
			}
		}
		if (!found)
			break;
		mark[d.index] = 1;
		Edge_jxc e = g.firstEdge(d.index);
		while (g.isEdge(e)) {
			if (d_arr[e.to].length > (d_arr[d.index].length + e.weight)) {
				d_arr[e.to].length = d_arr[d.index].length + e.weight;
				d_arr[e.to].pre = d.index;
				min_heap.insert(d_arr[e.to]);
			}
			e = g.nextEdge(e);
		}
	}
}

//}}}
//Floyd计算每对顶点间的最短路径{{{
void floyd(GraphBase_jxc & G, Dist ** D)
{
	int v_num = G.verticesNum();
	for (int i = 0; i < v_num; i++) {	/* init adjm */
		for (int j = 0; j < v_num; j++) {
			if (i == j) {
				D[i][j].length = 0;
				D[i][j].pre = i;
			} else {
				D[i][j].length = INFINITY_JXC;
				D[i][j].pre = -1;
			}
		}
	}

	for (int v = 0; v < v_num; v++) {
		Edge_jxc e = G.firstEdge(v);
		while (G.isEdge(e)) {
			D[v][e.to].length = e.weight;
			D[v][e.to].pre = v;
			e = G.nextEdge(e);
		}
	}

	for (int v = 0; v < v_num; v++) {	/* n times iteration */
		for (int i = 0; i < v_num; i++) {
			for (int j = 0; j < v_num; j++) {
				if (D[i][j].length > (D[i][v].length + D[v][j].length)) {
					D[i][j].length = D[i][v].length + D[v][j].length;
					D[i][j].pre = D[v][j].pre;
				}
			}
		}
	}
}

//}}}
//最小生成树：Prim算法{{{
int minVertex(GraphBase_jxc & G, Dist * d_arr)
{
	int v_num = G.verticesNum();
	int *mark = G.mark();
	int res;
	for (int i = 0; i < v_num; i++) {
		if (mark[i] == 0) {
			res = i;
			break;
		}
	}
	for (int i = 0; i < v_num; i++) {
		if (mark[i] == 0 && (d_arr[i] < d_arr[res]))
			res = i;
	}
	return res;
}

void prim(GraphBase_jxc & G, Edge_jxc * MST, int s)
{
	int v_num = G.verticesNum();
	int *mark = G.mark();
	memset(mark, 0, v_num * sizeof(int));
	Dist *d_arr = new Dist[v_num];
	for (int i = 0; i < v_num; i++) {
		mark[i] = 0;
		d_arr[i].index = i;
		d_arr[i].length = INFINITY_JXC;
		d_arr[i].pre = s;
	}
	d_arr[s].length = 0;
	mark[s] = 1;

	int v = s;
	for (int i = 0; i < v_num - 1; i++) {
		if (d_arr[v].length == INFINITY_JXC)
			return;
		Edge_jxc e = G.firstEdge(v);
		while (G.isEdge(e)) {
			if (mark[e.to] == 0 && d_arr[e.to].length > e.weight) {
				d_arr[e.to].length = e.weight;
				d_arr[e.to].pre = v;
			}
			e = G.nextEdge(e);
		}
		v = minVertex(G, d_arr);
		mark[v] = 1;
		e = {
		d_arr[v].pre, d_arr[v].index, d_arr[v].length};
		MST[i] = e;
	}
}

//}}}
//最小生成树：Kruskal算法{{{
void kruskal(GraphBase_jxc & G, Edge_jxc * MST)
{
	int v_num = G.verticesNum();
	int e_num = G.edgesNum();
	int *mark = G.mark();
	memset(mark, 0, v_num * sizeof(int));
	MinHeap_jxc < Edge_jxc > min_heap(e_num);
	Edge_jxc tmp_edge;
	for (int i = 0; i < v_num; i++) {
		tmp_edge = G.firstEdge(i);
		while (G.isEdge(tmp_edge)) {
			min_heap.insert(tmp_edge);
			tmp_edge = G.nextEdge(tmp_edge);
		}
	}
	int mst_e_num = 0;
	ParTree_jxc < int >pt(v_num);	/* 并查集 */
	while (true) {
		if (min_heap.isEmpty() || mst_e_num == v_num - 1)
			break;
		min_heap.remove(0, tmp_edge);
		if (!pt.different(tmp_edge.to, tmp_edge.from))
			continue;
		mark[tmp_edge.to] = 1;
		mark[tmp_edge.from] = 1;
		MST[mst_e_num++] = tmp_edge;
		pt.conjunction(tmp_edge.to, tmp_edge.from);
	}
}

//}}}

#endif
