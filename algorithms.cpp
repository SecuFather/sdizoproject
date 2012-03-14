#include "algorithms.h"
#include "graph.h"
#include <queue>
#include <set>
#include <list>
#include <algorithm>
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

void mstPrim(Graph *graph){
	priority_queue<Edge> eQueue;

	int x = graph->nextVertex(-1), y = -1;
	for(int i=0; i<graph->getMaxIndex(); ++i){
		graph->setEdge(x, x, -1);

		while((y = graph->nextEdge(x, y)) >= 0){
			Edge e(x, y, 0);
			e.v = graph->getEdge(e.x, e.y);
			eQueue.push(e);
			graph->setEdge(e.x, e.y, 0);
		}
		Edge e = eQueue.top();
		eQueue.pop();
		graph->setEdge(e.x, e.y, -e.v);

		if(graph->getEdge(e.x, e.x) > 0){
			x = e.x;
		}else{
			x = e.y;
		}
	}
	graph->fix();

}

void mstKruscal(Graph *graph){
	priority_queue<Edge> eQueue;
	list< set<int> > forest(graph->getVertexCount());
	list< set<int> >::iterator it;
	list< set<int> >::iterator tmp;

	int x = -1, y = -1;
	for(it = forest.begin(); (x = graph->nextVertex(x)) >= 0; ++it){
		it->insert(x);
		while((y = graph->nextEdge(x, y)) >= 0){
			Edge e(x, y, 0);
			e.v = graph->getEdge(e.x, e.y);
			graph->setEdge(e.x, e.y, 0);

			eQueue.push(e);
		}
	}
	while( forest.size() > 1 ){
		Edge e = eQueue.top();
		eQueue.pop();

		bool nxt = false, inv = false;
		for(it = forest.begin(); it != forest.end(); ++it){
			if(!nxt){
				if(binary_search(it->begin(), it->end(), e.x)){
					nxt = true;
					tmp = it;
				}else{
					if(binary_search(it->begin(), it->end(), e.y)){
						nxt = true;
						inv = true;
						swap(e.x, e.y);
						tmp = it;
					}
				}
			}else{
				if(binary_search(it->begin(), it->end(), e.y)){
					tmp->insert(it->begin(), it->end());
					forest.erase(it);
					if(inv){
						graph->addEdge(e.y, e.x, e.v);
					}else{
						graph->addEdge(e.x, e.y, e.v);
					}
					break;
				}
			}
		}
	}
}
