#ifndef GRAPH_H_
#define GRAPH_H_

class Graph{
private:
	const int max;
	int **matrix;
	int maxIndex;
public:
	Graph();
	~Graph();

	bool addVerticle(int at);
	bool addEdge(int x, int y, int value);

	bool removeVerticle(int at);
	bool removeEdge(int x, int y);

	int nextVertex(int prev);
	int nextEdge(int x, int prev);

	int getEdge(int x, int y);
	void setEdge(int x, int y, int v);

	int getMax();
	int getMaxIndex();
	int **getMatrix();
	void fix();
};

#endif /* GRAPH_H_ */
