#ifndef GRAPH_H_
#define GRAPH_H_

class Graph{
protected:
	const int max;
public:
	Graph():max(1000){}
	virtual ~Graph(){};

	virtual bool addVerticle(int at)=0;
	virtual bool addEdge(int x, int y, int value)=0;

	virtual bool removeVerticle(int at)=0;
	virtual bool removeEdge(int x, int y)=0;

	virtual int nextVertex(int prev)=0;
	virtual int nextEdge(int x, int prev)=0;

	virtual int getEdge(int x, int y)=0;
	virtual void setEdge(int x, int y, int v)=0;

	virtual int getMax()=0;
	virtual int getMaxIndex()=0;
	virtual int **getMatrix()=0;
	virtual int getVertexCount()=0;
	virtual void fix()=0;
};

#endif /* GRAPH_H_ */
