#include <iostream>
#include <ctime>
#include <cstdlib>
#include "mgraph.h"
#include "lgraph.h"
#include "algorithms.h"
#include "containers.h"
#include <list>
using namespace std;


void showe(list<Edge> &e){
	list<Edge>::iterator it;
	for(it = e.begin(); it != e.end(); ++it){
		cout << "(" << it->x << ", " << it->y << ", " << it->v << ")" << endl;
	}
}

int main(){
	LGraph *graph = new LGraph();
	for(int i=1; i<9; ++i){
		graph->addVertex(i);
	}
	graph->addEdge(1, 2, 5);
	graph->addEdge(1, 3, 4);
	graph->addEdge(2, 3, 2);
	graph->addEdge(2, 5, 3);
	graph->addEdge(2, 6, 5);
	graph->addEdge(3, 4, 4);
	graph->addEdge(3, 5, 3);
	graph->addEdge(3, 6, 6);
	graph->addEdge(4, 6, 5);
	graph->addEdge(4, 7, 5);
	graph->addEdge(4, 8, 4);
	graph->addEdge(5, 6, 4);
	graph->addEdge(5, 7, 7);
	graph->addEdge(6, 7, 5);
	graph->addEdge(7, 8, 4);

	for(int i=1; i<9; ++i){
		cout<<spDijkstra(graph, 1, 3)<<endl;
	}

	delete graph;


}

