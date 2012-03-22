#include "algorithms.h"
#include "containers.h"
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

int spDijkstra(Graph *graph, int start, int end){
	Heap paths(graph->getMaxIndex()+1);
	int x = start, y = -1, base;

	paths.addNode(start, 0);
	while(x != end){
		base = paths.pop();
		while( (y = graph->nextEdge(x, y)) >= 0){
			Edge e1(x, y);
			e1.v = graph->getEdge(e1.x, e1.y);
			graph->setEdge(e1.x, e1.y, -e1.v);
			paths.setNode(y, base+e1.v);
		}
		x = paths.top();
	}
	graph->fix();

	return paths.pop();
}

int spBellman(Graph *graph, int start, int end){
	int n = graph->getMaxIndex()+1;
	int *paths = new int[n];
	paths[start] = 0;
	for(int i=0; i<n; ++i){
		if(i != start){
			paths[i] = 1000000;
		}
	}

	int x=-1, y=-1;
	while((x = graph->nextVertex(x)) >=0){
		while((y = graph->nextEdge(x, y)) >= 0){
			Edge e1(x, y);
			e1.v = graph->getEdge(e1.x, e1.y);
			if(paths[e1.y] > paths[e1.x] + e1.v){
				paths[e1.y] = paths[e1.x] + e1.v;
			}
		}
	}
	return paths[end];
}
