#ifndef jxc_tree_h
#define jxc_tree_h

//等价类&并查集{{{

template < typename T > class NodeParTree_jxc {
  public:
	T data;
	NodeParTree_jxc < T > *parent;
	int count;
	NodeParTree_jxc() {
		parent = NULL;
		count = 1;
	}
};

template < typename T > class ParTree_jxc {
  private:
	NodeParTree_jxc < T > *_arr;
	int _size;
  public:
	ParTree_jxc(int s) {
		_size = s;
		_arr = new NodeParTree_jxc < T >[s];
	}
	virtual ~ ParTree_jxc() {
		delete[]_arr;
	}
	ParTree_jxc(const ParTree_jxc < T > &rhs) = delete;
	ParTree_jxc < T > &operator=(const ParTree_jxc < T > &rhs) = delete;
	NodeParTree_jxc < T > *find(NodeParTree_jxc < T > *node) const {
		while (node->parent != NULL)
			node = node->parent;
		return node;
	}
	bool different(int i, int j) const {
		return find(&_arr[i]) != find(&_arr[j]);
	}
	void conjunction(int i, int j) const {
		NodeParTree_jxc < T > *p1 = find(&_arr[i]);
		NodeParTree_jxc < T > *p2 = find(&_arr[j]);
		if (p1 != p2) {
			if (p1->count > p2->count)
				p2->parent = p1, p1->count += p2->count;
			else
				p1->parent = p2, p2->count += p1->count;
		}
	}
	NodeParTree_jxc < T > *findPC(NodeParTree_jxc < T > *node) const {	/* 带路径压缩的 */
		if (node->parent == NULL)
			return node;
		node->parent = findPC(node->parent);
		return node->parent;
	}
};
//}}}
#endif
