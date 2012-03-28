#ifndef MGRAPH_H_
#define MGRAPH_H_

#include "graph.h"

class MGraph : public Graph{
protected:
	int **matrix;
public:
	MGraph(int maxSize);
	virtual ~MGraph();

	virtual bool addVertex(int at);
	virtual bool addEdge(int x, int y, int value);

	virtual Edge removeEdge(int x, int y);

	virtual int nextVertex(int prev);
	virtual int nextEdge(int x, int prev);

	virtual int getEdge(int x, int y);
};


#endif /* MGRAPH_H_ */
