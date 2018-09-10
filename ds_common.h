#ifndef ds_jxc_h
#define ds_jxc_h
#include "stack.h"
#include <ctype.h>
#include <assert.h>

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
#endif
