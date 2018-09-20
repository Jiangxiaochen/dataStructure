#ifndef jxc_linerar_list_h
#define jxc_linerar_list_h
#include <iostream>
template < typename T > class List_jxc {
  public:
	int _cur_len;
	virtual ~ List_jxc() {

	}
  public:
	void clear();
	bool isEmpty();
	bool append(const T v);
	bool insert(const int p, const T v);
	bool deleteEle(const int p);
	bool getValue(const int p, T & v);
	bool setValue(const int p, const T v);
	bool getPos(int &p, const T value);
	virtual int length() {
		return _cur_len;
	}
};

template < typename T > class ArrList_jxc:public List_jxc < T > {
	using List_jxc < T >::_cur_len;
  private:
	T * _a_list;
	int _max_size;
//  int _cur_len;
	int _position;
  public:
	ArrList_jxc(const int size):_max_size(size), _position(0) {
		_cur_len = 0;
		_a_list = new T[_max_size];
	}
	~ArrList_jxc() {
		delete[]_a_list;
	}
	ArrList_jxc & operator=(const ArrList_jxc & rhs) = delete;	/* 阻止拷贝 */
	ArrList_jxc(const ArrList_jxc & rhs) = delete;	/*阻止拷贝  */
	void clear() {
		_cur_len = _position = 0;
//      delete[]_a_list;
//      chk_null((_a_list = new T[_max_size]));
	}
	bool getPos(int &p, const T value);
	bool insert(const int p, const T v);
	bool deleteEle(const int p);
};

template < typename T > bool ArrList_jxc < T >::deleteEle(const int p)
{
	if (_cur_len <= 0) {
		fprintf(stderr, "%s\n", "cant delete: list is empty");
		return false;
	}
	if (p < 0 || p > _cur_len - 1) {
		fprintf(stderr, "%s\n", "cant delete: position illegal");
		return false;
	}
	for (int i = p; i < _cur_len - 1; i++) {
		_a_list[i] = _a_list[i + 1];
	}
	_cur_len--;
	return true;
}

template < typename T > bool ArrList_jxc < T >::insert(const int p, const T v)
{
	if (_cur_len >= _max_size) {
		fprintf(stderr, "%s\n", "cant insert: size overflow");
		return false;
	}
	if (p < 0 || p > _cur_len) {
		fprintf(stderr, "%s\n", "cant insert: position illegal");
		return false;
	}
	for (int i = _cur_len; i > p; i--) {
		_a_list[i] = _a_list[i - 1];
	}
	_a_list[p] = v;
	_cur_len++;
	return true;
}

template < typename T > bool ArrList_jxc < T >::getPos(int &p, const T v)
{
	for (int i = 0; i < _cur_len; i++) {
		if (_a_list[i] == v) {
			p = i;
			return true;
		}
	}
	return false;
}

template < typename T > class NodeLink_jxc {	/* 单链表节点 */
  public:
	T data;
	NodeLink_jxc < T > *next;
	NodeLink_jxc(const T d, NodeLink_jxc < T > *n = NULL) {
		data = d;
		next = n;
	}
	NodeLink_jxc() {
		next = NULL;
	}

};

template < typename T > class LinkStack_jxc;
template < typename T > class LinkQueue_jxc;
class GraphAdjl_jxc ;
template < typename T > class LinkList_jxc:public List_jxc < T > {
	using List_jxc < T >::_cur_len;
	friend LinkStack_jxc < T >;
	friend LinkQueue_jxc < T >;
	friend GraphAdjl_jxc;
	/*
	 * 单链表
	 */
  private:
	NodeLink_jxc < T > *_head, *_tail;
	NodeLink_jxc < T > *_setPos(int p) {	/* 书中方法会导致内存泄漏 */
		if (p < -1 || p > _cur_len - 1) {
			return NULL;
		}
		if (p == -1) {
			return _head;
		}
		NodeLink_jxc < T > *result = _head->next;
		while (p-- && result != nullptr) {
			result = result->next;
		}
		return result;
	}
  public:
	LinkList_jxc() {
		_head = _tail = new NodeLink_jxc < T >;
		_cur_len = 0;
	}
	~LinkList_jxc() {
		NodeLink_jxc < T > *tmp;
		while (_head != nullptr) {
			tmp = _head;
			_head = _head->next;
			delete tmp;
		}
	}
	LinkList_jxc & operator=(const LinkList_jxc & rhs) = delete;	/* 阻止拷贝 */
	LinkList_jxc(const LinkList_jxc & rhs) = delete;	/*  */
	bool getValue(const int p, T & v) {
		NodeLink_jxc < T > *ptr = _setPos(p);
		if (ptr == NULL || ptr == _head) {
			return false;
		}
		v = ptr->data;
		return true;
	}
	bool insert(const int p, const T v) {
		NodeLink_jxc < T > *prev, *pv;
		if ((prev = _setPos(p - 1)) == NULL) {
			fprintf(stderr, "%s\n", "cant insert: position illegal");
			return false;
		}
		pv = new NodeLink_jxc < T > (v, prev->next);
		prev->next = pv;
		if (prev == _tail) {
			_tail = pv;
		}
		_cur_len++;
		return true;
	}
	bool deleteEle(const int p) {
		NodeLink_jxc < T > *prev, *cur;
		if (p < 0 || p > _cur_len - 1) {
			fprintf(stderr, "%s\n", "can't delete: position illegal");
			return false;
		}
		prev = _setPos(p - 1);
		cur = prev->next;
		prev->next = cur->next;
		if (cur == _tail) {
			_tail = prev;
		}
		delete cur;
		_cur_len--;
		return true;
	}
	bool append(const T v) {
		_tail->next = new NodeLink_jxc < T > (v);
		_cur_len++;
		_tail = _tail->next;
		return true;
	}
	NodeLink_jxc<T> *getPos(const T &v){
		NodeLink_jxc<T> *p = _head->next;
		while(p){
			if(p->data == v) return p;
			p = p->next;
		}
		return NULL;
	}
	void print(){
		NodeLink_jxc<T> *p = _head->next;
		while(p){
			std::cout << p->data << " ";
			p = p->next;
		}
		std::cout << std::endl;
	}
};

template < typename T > class NodeDoubleLink_jxc {
  public:
	T data;
	NodeDoubleLink_jxc < T > *_prev, *_next;
	NodeDoubleLink_jxc(const T d, NodeDoubleLink_jxc < T > *p =
					   NULL, NodeDoubleLink_jxc < T > *n = NULL) {
		data = d;
		_prev = p;
		_next = n;
	}
};

#endif
