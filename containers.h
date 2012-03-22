#ifndef CONTAINERS_H_
#define CONTAINERS_H_

class Edge{
public:
	int x, y, v;
	Edge(int x=0, int y=0, int v=0) : x(x < y ? x : y), y(x < y ? y : x), v(v){}
};
bool operator<(const Edge &e1, const Edge &e2);

class Vertex{
public:
	int key, v, pos;
	Vertex(int key=-1, int v=0, int pos=0) : key(key), v(v), pos(pos){}
};
bool operator<(const Vertex &v1, const Vertex &v2);

class Heap{
private:
	Vertex **vertices;
	int *index, heapSize, maxSize;
public:
	Heap(int size);

	~Heap();
	void addNode(int key, int value);
	void setNode(int key, int value);
	int pop();
	int top();
	void repairHeap(int at);
	void swap(int at, int min);
	Vertex **getVertices(){ return vertices; }
};


#endif /* CONTAINERS_H_ */
