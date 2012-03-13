#include "algorithms.h"
#include "graph.h"
#include <queue>
#include <iostream>
using namespace std;

void displayGraphMatrix(Graph *graph){
	int **matrix = graph->getMatrix();

	for(int i=0;i<=graph->getMaxIndex(); ++i){
		for(int j=0; j<i+1; ++j){
			cout.width(3);
			cout<<matrix[i][j];
		}
		cout<<endl;
	}
}

class Edge{
public:
	int x, y, v;
	Edge(int x=0, int y=0, int v=0) : x(x < y ? x : y), y(x < y ? y : x), v(v){}
};

bool operator<(const Edge &e1, const Edge &e2){
	return e1.v > e2.v;
}

void minimumSpanningTree(Graph *graph){
	priority_queue<Edge> vQueue;

	int x = graph->nextVertex(-1), y = -1;
	for(int i=0; i<graph->getMaxIndex(); ++i){
		graph->setEdge(x, x, -1);

		while((y = graph->nextEdge(x, y)) >= 0){
			Edge e(x, y, 0);
			e.v = graph->getEdge(e.x, e.y);
			vQueue.push(e);
			graph->setEdge(e.x, e.y, 0);
		}
		Edge e = vQueue.top();
		vQueue.pop();
		graph->setEdge(e.x, e.y, -e.v);

		if(graph->getEdge(e.x, e.x) > 0){
			x = e.x;
		}else{
			x = e.y;
		}
	}
	graph->fix();

}
