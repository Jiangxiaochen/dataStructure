#ifndef jxc_tree_h
#define jxc_tree_h
#include "stack.h"
#include "queue.h"

//链式二叉树{{{

template < typename T > class NodeBiTree_jxc {
  public:
	T data;
	NodeBiTree_jxc < T > *l_c;
	NodeBiTree_jxc < T > *r_c;
	NodeBiTree_jxc() {
		l_c = r_c = NULL;
	}
	NodeBiTree_jxc(const T & e, NodeBiTree_jxc < T > *l =
				   NULL, NodeBiTree_jxc < T > *r = NULL) {
		data = e, l_c = l, r_c = r;
	}
	bool isLeaf() const {
		return l_c == NULL && r_c == NULL;
	}
};

template < typename T > class BinaryTree_jxc {
  protected:
	void (*_handler) (NodeBiTree_jxc < T > *);
	NodeBiTree_jxc < T > *_root;
	//递归版本
	void _preOrder(NodeBiTree_jxc < T > *n) {
		if (n != NULL) {
			_handler(n);
			_preOrder(n->l_c);
			_preOrder(n->r_c);
		}
	}
	void _inOrder(NodeBiTree_jxc < T > *n) {
		if (n != NULL) {
			_inOrder(n->l_c);
			_handler(n);
			_inOrder(n->r_c);
		}
	}
	void _postOrder(NodeBiTree_jxc < T > *n) {
		if (n != NULL) {
			_postOrder(n->l_c);
			_postOrder(n->r_c);
			_handler(n);
		}
	}
	//迭代版本
	void _preOrder_it(NodeBiTree_jxc < T > *n) {
		LinkStack_jxc < NodeBiTree_jxc < T > *>lsj;
		NodeBiTree_jxc < T > *p = n;
		lsj.push(NULL);			/* 使得循环结束 */
		while (p) {
			_handler(p);
			if (p->r_c)
				lsj.push(p->r_c);
			if (p->l_c)
				p = p->l_c;
			else
				lsj.pop(p);
		}
	}
	void _inOrder_it(NodeBiTree_jxc < T > *n) {
		LinkStack_jxc < NodeBiTree_jxc < T > *>lsj;
		NodeBiTree_jxc < T > *p = n;
		while (p || !lsj.isEmpty()) {
			if (p)
				lsj.push(p), p = p->l_c;
			else
				lsj.pop(p), _handler(p), p = p->r_c;
		}
	}
	void _postOrder_it(NodeBiTree_jxc < T > *n) {
		if (n == NULL)
			return;
		LinkStack_jxc < NodeBiTree_jxc < T > *>lsj;
		NodeBiTree_jxc < T > *p = n;
		NodeBiTree_jxc < T > *last = n;
		lsj.push(p);
		while (!lsj.isEmpty()) {
			lsj.top(p);
			if ((p->l_c == NULL && p->r_c == NULL)
				|| (p->r_c == NULL && last == p->l_c) || (last == p->r_c)) {
				_handler(p);
				last = p;
				lsj.pop(p);
			} else {
				if (p->r_c)
					lsj.push(p->r_c);
				if (p->l_c)
					lsj.push(p->l_c);
			}
		}
	}
  public:
	void preOrder(void (*handler) (NodeBiTree_jxc < T > *)) {
		_handler = handler;
		_preOrder(_root);
	}
	void inOrder(void (*handler) (NodeBiTree_jxc < T > *)) {
		_handler = handler;
		_inOrder(_root);
	}
	void postOrder(void (*handler) (NodeBiTree_jxc < T > *)) {
		_handler = handler;
		_postOrder(_root);
	}
	void levelOrder(void (*handler) (NodeBiTree_jxc < T > *)) {
		_handler = handler;
		LinkQueue_jxc < NodeBiTree_jxc < T > *>lqj;
		NodeBiTree_jxc < T > *p = _root;
		if (p)
			lqj.enQueue(p);
		while (!lqj.isEmpty()) {
			lqj.deQueue(p);
			_handler(p);
			if (p->l_c)
				lqj.enQueue(p->l_c);
			if (p->r_c)
				lqj.enQueue(p->r_c);
		}
	}
	bool isEmpty() {
		return _root ? false : true;
	}

	NodeBiTree_jxc < T > *parent(NodeBiTree_jxc < T > *cur) {
		if (cur == NULL)
			return NULL;
		NodeBiTree_jxc < T > *p = _root;
		LinkStack_jxc < NodeBiTree_jxc < T > *>lsj;
		lsj.push(NULL);
		while (p) {
			if (p->l_c == cur || p->r_c == cur)
				return p;
			if (p->r_c)
				lsj.push(p->r_c);
			if (p->l_c)
				p = p->l_c;
			else
				lsj.pop(p);
		}
		return NULL;
	}

	void createTree(const T & info, BinaryTree_jxc < T > &lt,
					BinaryTree_jxc < T > &rt) {
		_root = new NodeBiTree_jxc < T > (info, lt._root, rt._root);
		lt._root = rt._root = NULL;
	}

	void deleteTree(NodeBiTree_jxc < T > *n) {
		if (n != NULL) {
			deleteTree(n->l_c);
			deleteTree(n->r_c);
			delete n;
		}
	}
	BinaryTree_jxc() {
		_handler = NULL;
		_root = NULL;
	}

	virtual ~ BinaryTree_jxc() {
		deleteTree(_root);
	}

};

//}}}
//二叉搜索树{{{

template < typename T > class BST_jxc:public BinaryTree_jxc < T > {
	using BinaryTree_jxc < T >::_root;
	using BinaryTree_jxc < T >::parent;
  public:
	void insertNode(NodeBiTree_jxc < T > *newNode) {
		if (_root == NULL) {
			_root = newNode;
			return;
		}
		NodeBiTree_jxc < T > *p = _root;
		while (p) {
			if (p->data == newNode->data)
				return;
			if (p->data > newNode->data) {
				if (p->l_c == NULL) {
					p->l_c = newNode;
					return;
				}
				p = p->l_c;
			} else {
				if (p->r_c == NULL) {
					p->r_c = newNode;
					return;
				}
				p = p->r_c;
			}
		}
	}
	NodeBiTree_jxc < T > *searchNode(const T & d) {
		if (_root == NULL)
			return NULL;
		NodeBiTree_jxc < T > *p = _root;
		while (p) {
			if (p->data == d)
				return p;
			else if (p->data > d) {
				p = p->l_c;
			} else {
				p = p->r_c;
			}
		}
		return NULL;
	}
	void deleteNode(const T & d) {
		NodeBiTree_jxc < T > *to_del = searchNode(d);
		if (to_del == NULL)
			return;
		NodeBiTree_jxc < T > *max, *max_parent, *del_parent;
		del_parent = parent(to_del);
		if (to_del->l_c == NULL)
			max = to_del->r_c;
		else {
			max_parent = NULL;
			max = to_del->l_c;
			while (max->r_c != NULL)
				max_parent = max, max = max->r_c;
			if (max_parent == NULL)
				to_del->l_c = max->l_c;
			else
				max_parent->r_c = max->l_c;
			max->l_c = to_del->l_c;
			max->r_c = to_del->r_c;
		}
		//开始替换
		if (del_parent == NULL)
			_root = max;
		else if (del_parent->l_c == to_del)
			del_parent->l_c = max;
		else
			del_parent->r_c = max;

		delete to_del;
	}
};

//}}}
//最小堆{{{

template < typename T > class MinHeap_jxc {
  private:
	T * _arr;
	int _cur_size;
	int _max_size;
	void _swap(int x, int y);
	void _buildHeap() {
		for (int i = _cur_size / 2 - 1; i >= 0; i--)
			siftDown(i);
	}
  public:
	MinHeap_jxc(int n) {
		assert(n > 0);
		_cur_size = 0;
		_max_size = n;
		_arr = new T[n];
		_buildHeap();
	}
	~MinHeap_jxc() {
		delete[]_arr;
	}
	bool isEmpty() {
		return _cur_size == 0;
	}
	bool isLeaf(int pos) {
		return (pos < _cur_size) && (pos >= _cur_size / 2);
	}
	int leftChild(int pos) {
		return 2 * pos + 1;
	}
	int rightChild(int pos) {
		return 2 * pos + 2;
	}
	int parent(int pos) {
		return (pos - 1) / 2;
	}
	bool insert(const T & newNode) {
		if (_cur_size >= _max_size)
			return false;
		_arr[_cur_size] = newNode;
		siftUp(_cur_size);
		_cur_size++;
		return true;
	}
	bool remove(int pos, T & res) {
		if (pos < 0 || pos >= _cur_size)
			return false;
		res = _arr[pos];
		_arr[pos] = _arr[--_cur_size];
		if (pos > 0 && _arr[parent(pos)] < _arr[pos])
			siftUp(pos);
		else
			siftDown(pos);
		return true;
	}
	void siftUp(int pos) {
		if (pos <= 0 || pos >= _cur_size)
			return;
		T   to_sift = _arr[pos];
		while (pos > 0 && _arr[parent(pos)] > to_sift) {
			_arr[pos] = _arr[parent(pos)];
			pos = parent(pos);
		}
		_arr[pos] = to_sift;
	}
	void siftDown(int pos) {
		if (pos <= 0 || pos >= _cur_size)
			return;
		if (isLeaf(pos))
			return;
		T   to_sift = _arr[pos];
		int min_pos = leftChild(pos);
		while (min_pos < _cur_size) {
			if (min_pos + 1 < _cur_size && _arr[min_pos] > _arr[min_pos + 1])
				min_pos++;
			if (_arr[min_pos] > to_sift)
				break;
			_arr[pos] = _arr[min_pos];
			pos = min_pos;
			min_pos = leftChild(pos);
		}
		_arr[pos] = to_sift;
	}
};

//}}}
#endif
