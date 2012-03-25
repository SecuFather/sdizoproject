#ifndef LGRAPH_H_
#define LGRAPH_H_

#include "graph.h"
#include <list>
using namespace std;

class LGraph : public Graph{
protected:
	list<Edge> **vertices;
	list<Edge>::iterator current;
public:
	LGraph();
	virtual ~LGraph();

	virtual bool addVertex(int at);
	virtual bool addEdge(int x, int y, int value);

	virtual Edge removeEdge(int x, int y);

	virtual int nextVertex(int prev);
	virtual int nextEdge(int x, int prev);

	virtual int getEdge(int x, int y);

};


#endif /* LGRAPH_H_ */
