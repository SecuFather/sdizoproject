#ifndef GRAPH_H_
#define GRAPH_H_

#include "containers.h"

class Graph{
protected:
	const int max;
	int vCount, maxIndex;
public:
	Graph():max(10000), vCount(0), maxIndex(-1){}
	virtual ~Graph(){};

	virtual bool addVertex(int at)=0;
	virtual bool addEdge(int x, int y, int value)=0;

	virtual Edge removeEdge(int x, int y)=0;

	virtual int nextVertex(int prev)=0;
	virtual int nextEdge(int x, int prev)=0;

	virtual int getEdge(int x, int y)=0;

	virtual int getMax(){ return max; }
	inline virtual int getMaxIndex()const{ return maxIndex; }
	inline virtual int getVertexCount()const{ return vCount; }
};

#endif /* GRAPH_H_ */
