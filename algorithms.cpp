#include "algorithms.h"
#include "containers.h"
#include "graph.h"
#include <queue>
#include <set>
#include <list>
#include <algorithm>
#include <iostream>
using namespace std;

int mstPrim(Graph *graph){
	priority_queue<Edge> eQueue;
	int result=0;

	int x = graph->nextVertex(-1), y = -1, n = graph->getVertexCount();
	for(int i=0; i<n-1; ++i){

		while((y = graph->nextEdge(x, y)) >= 0){
			eQueue.push(graph->removeEdge(x, y));
		}
		graph->removeEdge(x, x);
		Edge e;
		do{
			e = eQueue.top();
			eQueue.pop();
		}while(graph->getEdge(e.x, e.x) <= 0 && graph->getEdge(e.y, e.y) <= 0);
		cout<<e.x<<", "<<e.y<<", "<<e.v<<endl;
		result += e.v;

		if(graph->getEdge(e.x, e.x) > 0){
			x = e.x;
		}else{
			x = e.y;
		}
	}
	return result;
}

int mstKruscal(Graph *graph){
	priority_queue<Edge> eQueue;
	list< set<int> > forest(graph->getVertexCount());
	list< set<int> >::iterator it;
	list< set<int> >::iterator tmp;

	int result = 0;
	int x = -1, y = -1;
	for(it = forest.begin(); (x = graph->nextVertex(x)) >= 0; ++it){
		it->insert(x);
		while((y = graph->nextEdge(x, y)) >= 0){
			eQueue.push(graph->removeEdge(x, y));
		}
	}
	while( forest.size() > 1 ){
		Edge e = eQueue.top();
		eQueue.pop();

		bool nxt = false;
		for(it = forest.begin(); it != forest.end(); ++it){
			if(!nxt){
				if(binary_search(it->begin(), it->end(), e.x)){
					nxt = true;
					tmp = it;
				}else{
					if(binary_search(it->begin(), it->end(), e.y)){
						nxt = true;
						swap(e.x, e.y);
						tmp = it;
					}
				}
			}else{
				if(binary_search(it->begin(), it->end(), e.y)){
					tmp->insert(it->begin(), it->end());
					forest.erase(it);
					result += e.v;
					cout<<e.x<<", "<<e.y<<", "<<e.v<<endl;
					break;
				}
			}
		}
	}
	return result;
}

int spDijkstra(Graph *graph, int start, int end){
	Heap paths(graph->getMaxIndex()+1);
	int x = start, y = -1, base;

	paths.addNode(start, 0);
	while(x != end){
		if((base = paths.pop()) < 0){
			return -1;
		}
		while( (y = graph->nextEdge(x, y)) >= 0){
			Edge e1 = graph->removeEdge(x, y);
			if(x != e1.x){
				paths.setNode(e1.x, base+e1.v);
			}else{
				paths.setNode(e1.y, base+e1.v);
			}
		}
		graph->removeEdge(x, x);
		x = paths.top();
	}

	return paths.pop();
}

int spBellman(Graph *graph, int start, int end){
	int n = graph->getMaxIndex()+1;
	int *paths = new int[n];
	paths[start] = 0;
	for(int i=0; i<n; ++i){
		if(i != start){
			paths[i] = -1;
		}
	}

	int x=-1, y=-1;
	while((x = graph->nextVertex(x)) >=0){
		while((y = graph->nextEdge(x, y)) >= 0){
			Edge e = graph->removeEdge(x, y);
			if(paths[e.y] > 0 && paths[e.y] > paths[e.x] + e.v){
				paths[e.y] = paths[e.x] + e.v;
			}
		}
	}
	n = paths[end];
	delete[] paths;
	return n;
}
