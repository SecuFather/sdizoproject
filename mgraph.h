#ifndef MGRAPH_H_
#define MGRAPH_H_

#include "graph.h"

class MGraph : public Graph{
protected:
	int **matrix;
	int maxIndex, vCount;
public:
	MGraph();
	virtual ~MGraph();

	virtual bool addVerticle(int at);
	virtual bool addEdge(int x, int y, int value);

	virtual bool removeVerticle(int at);
	virtual bool removeEdge(int x, int y);

	virtual int nextVertex(int prev);
	virtual int nextEdge(int x, int prev);

	virtual int getEdge(int x, int y);
	virtual void setEdge(int x, int y, int v);

	virtual int getMax();
	virtual int getMaxIndex();
	virtual int **getMatrix();
	virtual int getVertexCount();
	virtual void fix();
};


#endif /* MGRAPH_H_ */
