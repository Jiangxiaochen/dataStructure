#include <common.h>

#define MAX 102
#define INFINITY 65536

int BrokerToPassRomour(Graph & G)
{
	int **D;
	int max[G.VerticesNum()];
	int min = 0;
	int pos = 0;
	for (int i = 0; i < G.VerticesNum(); i++) {
		max[i] = -1;
	}
	Floyd(G, D);				/* 找出各个顶点间的最短路径 */
	for (int i = 0; i < G.VerticesNum(); i++) {
		for (int j = 0; j < G.VerticesNum(); j++) {
			if (D[i][j] > max[i]) {
				max[i] = D[i][j];	/* 找出各个顶点最大花费 */
			}
		}
	}
	min = max[0];
	for (int i = 0; i < G.VerticesNum(); i++) {
		if (max[i] < min) {
			min = max[i];
			pos = i;
		}
	}
	if (min == INFINITY) {
		return -1;				/* 没有通路 */
	}
	return pos;
}
