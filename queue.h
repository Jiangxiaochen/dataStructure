#ifndef jxc_queue_h
#define jxc_queue_h

#include "list.h"
#include "stack.h"

template < typename T > class Queue_jxc {
  public:
	void clear();
	bool enQueue(const T item);
	bool deQueue(T & item);
	bool getFront(T & item);
	bool isEmpty();
	bool isFull();
};

//双栈实现队列{{{
template < typename T > class LinkQueueImpByTwoStack_jxc:public Queue_jxc < T > {
  private:
	LinkStack_jxc < T > *_lsj0;
	LinkStack_jxc < T > *_lsj1;
  public:
	LinkQueueImpByTwoStack_jxc() {
		_lsj0 = new LinkStack_jxc < T >;
		_lsj1 = new LinkStack_jxc < T >;
	}
	~LinkQueueImpByTwoStack_jxc() {
		delete _lsj0;
		delete _lsj1;
	}
	LinkQueueImpByTwoStack_jxc & operator=(const LinkQueueImpByTwoStack_jxc &
										   rhs) = delete;
	LinkQueueImpByTwoStack_jxc(const LinkQueueImpByTwoStack_jxc & rhs) = delete;
	bool isEmpty() {
		return _lsj0->isEmpty() && _lsj1->isEmpty();
	}
	bool isFull() {
		return false;
	}

	bool enQueue(const T item) {
		return _lsj0->push(item);
	}
	bool deQueue(T & item) {	/* _lsj1 非空时直接弹出 */
		if (isEmpty())
			return false;
		if (!_lsj1->isEmpty())
			return _lsj1->pop(item);
		T   tmp;
		while (_lsj0->pop(tmp)) {
			_lsj1->push(tmp);
		}
		return _lsj1->pop(item);
	}
};

//}}}

template < typename T > class LinkQueue_jxc:public Queue_jxc < T > {
  private:
	LinkList_jxc < T > *_llj;
  public:
	LinkQueue_jxc() {
		_llj = new LinkList_jxc < T >;
	}
	~LinkQueue_jxc() {
		delete _llj;
	}
	LinkQueue_jxc & operator=(const LinkQueue_jxc & rhs) = delete;
	LinkQueue_jxc(const LinkQueue_jxc & rhs) = delete;
	bool isEmpty() {
		return _llj->_cur_len == 0;
	}
	bool isFull() {
		return false;
	}
	void clear() {
		delete _llj;
		_llj = new LinkList_jxc < T >;
	}
	bool enQueue(const T item) {
		return _llj->append(item);
	}
	bool deQueue(T & item) {
		if (_llj->_cur_len <= 0) {
			fprintf(stderr, "deQueue error:empty\n");
			return false;
		}
		NodeLink_jxc < T > *to_del = _llj->_head->next;
		_llj->_head->next = to_del->next;
		item = to_del->data;
		delete to_del;
		if (to_del == _llj->_tail)
			_llj->_tail = _llj->_head;
		_llj->_cur_len--;
		return true;
	}
	bool getFront(T & item) {
		if (isEmpty()) {
			fprintf(stderr, "getFront error:empty\n");
			return false;
		}
		item = _llj->_head->next->data;
		return true;
	}

};

template < typename T > class ArrQueue_jxc:public Queue_jxc < T > {
  private:
	int _size;
	int _front;
	int _rear;
	T  *_arr;
  public:
	ArrQueue_jxc(int size) {
		_size = size;
		_arr = new T[_size + 1];
		_front = _rear = 0;
	}
	~ArrQueue_jxc() {
		delete[]_arr;
	}
	ArrQueue_jxc & operator=(const ArrQueue_jxc & rhs) = delete;
	ArrQueue_jxc(const ArrQueue_jxc & rhs) = delete;
	void clear() {
		_front = _rear;
	}
	bool isEmpty() {
		return _front == _rear;
	}
	bool isFull() {
		return (_rear + 1) % (_size + 1) == _front;
	}
	bool enQueue(const T item) {
		if (isFull()) {
			fprintf(stderr, "enQueue error: full\n");
			return false;
		}
		_arr[_rear] = item;
		_rear = (_rear + 1) % (_size + 1);
		return true;
	}
	bool deQueue(T & item) {
		if (isEmpty()) {
			fprintf(stderr, "deQueue error:empty\n");
			return false;
		}
		item = _arr[_front];
		_front = (_front + 1) % (_size + 1);
		return true;
	}
	bool getFront(T & item) {
		if (isEmpty()) {
			fprintf(stderr, "getFront error:empty\n");
			return false;
		}
		item = _arr[_front];
		return true;
	}
};
#endif
