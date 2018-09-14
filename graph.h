#ifndef jxc_graph_h
#define jxc_graph_h
#include <limits.h>
#include "list.h"

class Edge_jxc {
  public:
	int from, to, weight;

	    Edge_jxc(int f = -1, int t = -1, int w = 0) {
		from = f;
		to = t;
		weight = w;
}};

//基类{{{

class GraphBase_jxc {
  protected:
	int _num_vertex;
	int _num_edge;
	int *_mark;
	int *_indegree;
  public:
	int verticesNum() {
		return _num_vertex;
	}
	GraphBase_jxc(int n) {
		_num_vertex = n;
		_num_edge = 0;
		_indegree = new int[n];
		_mark = new int[n];
		for (int i = 0; i < n; i++) {
			_indegree[i] = _mark[i] = 0;
		}
	}
	~GraphBase_jxc() {
		delete[]_indegree;
		delete[]_mark;
	}
	int edgesNum() {
		return _num_edge;
	}
	virtual Edge_jxc firstEdge(int vertex) = 0;
	virtual Edge_jxc nextEdge(Edge_jxc pre) = 0;
	bool setEdge(int fv, int tv, int w);
	bool delEdge(int fv, int tv);
	bool isEdge(Edge_jxc e) {
		if (e.weight > 0 && e.from >= 0 && e.to >= 0)
			return true;
		return false;
	}
	int fromVertex(Edge_jxc e) {
		return e.from;
	}
	int toVertex(Edge_jxc e) {
		return e.to;
	}
	int getWeight(Edge_jxc e) {
		return e.weight;
	}
};

//}}}
//邻接矩阵{{{

class GraphAdjm_jxc:public GraphBase_jxc {
  private:
	int **_matrix;
  public:
	void print(void) {
		for (int i = 0; i < _num_vertex; i++) {
			for (int j = 0; j < _num_vertex; j++) {
				printf("%d ", _matrix[i][j]);
			} printf("\n");
		}
	}
	GraphAdjm_jxc(int n):GraphBase_jxc(n) {
		_matrix = new int *[n];
		for (int i = 0; i < n; i++) {
			_matrix[i] = new int[n];
		} for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				_matrix[i][j] = 0;
			}
		}
	}
	~GraphAdjm_jxc() {
		for (int i = 0; i < _num_vertex; i++) {
			delete[]_matrix[i];
		}
		delete[]_matrix;
	}
	Edge_jxc firstEdge(int v) {
		Edge_jxc e;
		e.from = v;
		for (int j = 0; j < _num_vertex; j++) {
			if (_matrix[v][j] != 0) {
				e.to = j;
				e.weight = _matrix[v][j];
				break;
			}
		}
		return e;
	}
	Edge_jxc nextEdge(Edge_jxc pre) {
		Edge_jxc e;
		e.from = pre.from;
		if (pre.to < _num_vertex) {
			for (int j = pre.to + 1; j < _num_vertex; j++) {
				if (_matrix[pre.from][j] != 0) {
					e.to = j;
					e.weight = _matrix[pre.from][j];
					break;
				}
			}
		}
		return e;
	}
	void setEdge(int f, int t, int w) {
		if (_matrix[f][t] <= 0) {
			_num_edge++;
			_indegree[t]++;
		}
		_matrix[f][t] = w;
	}
	void delEdge(int f, int t) {
		if (_matrix[f][t] > 0) {
			_num_edge--;
			_indegree[t]--;
		}
		_matrix[f][t] = 0;
	}
};

//}}}
//邻接表{{{
struct NodeAdjl_jxc {
	int v;
	int w;
	bool operator==(const NodeAdjl_jxc &rhs){
		return v == rhs.v;
	}
};
ostream& operator<<(ostream &os, const NodeAdjl_jxc &node){
	os << "(v:" << node.v << ",w:" << node.w << ')';
	return os;
}

class GraphAdjl_jxc : public GraphBase_jxc{
  private:
	LinkList_jxc < NodeAdjl_jxc > *_lljs;
  public:
	Edge_jxc firstEdge(int v) {
		Edge_jxc e;
		if  (v < 0 || v >= _num_vertex)
			    return e;
		    NodeLink_jxc < NodeAdjl_jxc > *node = _lljs[v]._setPos(0);
		if  (node != NULL)
			    e.from = v, e.to = node->data.v, e.weight = node->data.w;
		    return e;
	}
	Edge_jxc nextEdge(Edge_jxc pre){
		Edge_jxc e;
		e.from = pre.from;
		NodeLink_jxc<NodeAdjl_jxc> *p = _lljs[pre.from].getPos({pre.from,0});
		if(p && p->next){
			e.to = p->next->data.v;
			e.weight = p->next->data.w;
		}
		return e;
	}
	void setEdge(int f, int t, int w){
		NodeLink_jxc<NodeAdjl_jxc> * p = _lljs[f].getPos({t,0});
		if(p){
			p->data.w = w;
		}else{
			_lljs[f].append({t,w});
			_indegree[t]++;
			_num_edge++;
		}
	}
	void delEdge(int f, int t){
		NodeLink_jxc<NodeAdjl_jxc> *p = _lljs[f]._head;
		NodeAdjl_jxc to_find = {t,0};
		while(p->next){
			if(p->next->data == to_find){
				NodeLink_jxc<NodeAdjl_jxc> *tmp = p->next;
				p->next = p->next->next;
				delete tmp;
				break;
			}
			p = p->next;
		}
	}
	void print(){
		for (int i = 0; i < _num_vertex; i++) {
			NodeLink_jxc<NodeAdjl_jxc> *p = _lljs[i]._head;
			while(p->next){
				cout << p->next->data << " ";
				p=p->next;
			}
			cout << endl;
		}
	}
   	GraphAdjl_jxc(int n):GraphBase_jxc(n) {
		_lljs = new LinkList_jxc < NodeAdjl_jxc >[n];
	}
	~GraphAdjl_jxc() {
		delete[]_lljs;
	}

};

//}}}
#endif
