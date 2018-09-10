#ifndef jxc_stack_h
#define jxc_stack_h
extern "C" {
#include <common.h>
}
#include "list.h"
template < typename T > class Stack_jxc {
  public:
	void clear();
	bool push(const T item);
	bool pop(T & item);
	bool top(T & item);
	bool isEmpty();
	bool isFull();
};

template < typename T > class LinkStack_jxc:public Stack_jxc < T > {
  private:
	LinkList_jxc < T > *_llj;
  public:
	LinkStack_jxc() {
		_llj = new LinkList_jxc < T >;
	}
	~LinkStack_jxc() {
		delete _llj;
	}
	LinkStack_jxc & operator=(const LinkStack_jxc & rhs) = delete;	/* 阻止拷贝 */
	LinkStack_jxc(const LinkStack_jxc & rhs) = delete;	/*  */
	void clear() {
		delete _llj;
		_llj = new LinkList_jxc < T >;
	}
	bool push(const T item) {	/* 链表头为栈顶 */
		NodeLink_jxc < T > *tmp =
			new NodeLink_jxc < T > (item, _llj->_head->next);
		_llj->_head->next = tmp;
		_llj->_cur_len++;
		if (_llj->_head == _llj->_tail)
			_llj->_tail = tmp;
		return true;
	}
	bool pop(T & item) {
		if (_llj->_cur_len <= 0)
			return false;
		NodeLink_jxc < T > *cur = _llj->_head->next;
		_llj->_head->next = cur->next;
		if (cur == _llj->_tail)
			_llj->_tail = _llj->_head;
		item = cur->data;
		delete cur;
		_llj->_cur_len--;
		return true;
	}
	bool top(T & item) {
		if (_llj->_cur_len <= 0)
			return false;
		item = _llj->_head->next->data;
		return true;
	}
	bool isEmpty() {
		return _llj->_cur_len == 0;
	}
	int length() {
		return _llj->_cur_len;
	}
	T   getValue(int p) {
		T   tmp;
		_llj->getValue(p, tmp);
		return tmp;
	}

};

template < typename T > class ArrStack_jxc:public Stack_jxc < T > {
  private:
	int _max_size;
	int _top;
	T  *_arr;
  public:
	ArrStack_jxc(int s) {
		_max_size = s;
		_top = -1;
		_arr = new T[s];
		chk_null(_arr);
	}
	~ArrStack_jxc() {
		delete[]_arr;
	}
	ArrStack_jxc & operator=(const ArrStack_jxc &) = delete;	/* 阻止拷贝 */
	ArrStack_jxc(const ArrStack_jxc &) = delete;	/*  */
	void clear() {
		top = -1;
	}
	bool push(const T item) {
		if (_top == _max_size - 1) {
//          fprintf(stderr, "push error: stack full\n");
//          return false;
			T  *new_arr = new T[_max_size * 2];
			chk_null(new_arr);
			for (int i = 0; i <= _top; i++) {
				new_arr[i] = _arr[i];
			}
			delete[]_arr;
			_arr = new_arr;
			_max_size *= 2;
		}
		_arr[++_top] = item;
		return true;
	}
	bool top(T & item) {
		if (_top == -1) {
			fprintf(stderr, "top error: stack empty\n");
			return false;
		}
		item = _arr[_top];
		return true;
	}
	bool pop(T & item) {
		if (_top == -1) {
			fprintf(stderr, "pop error: stack empty\n");
			return false;
		}
		item = _arr[_top--];
		return true;
	}
};
#endif
