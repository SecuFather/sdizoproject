#include <iostream>
#include <ctime>
#include <cstdlib>
#include "graph.h"
#include "algorithms.h"
using namespace std;





int main(){
	Graph *graph = new Graph();
	for(int i=0; i<6; ++i){
		graph->addVerticle(i);
	}
	graph->addEdge(0, 1, 4);
	graph->addEdge(0, 4, 1);
	graph->addEdge(0, 5, 2);
	graph->addEdge(1, 2, 2);
	graph->addEdge(1, 4, 2);
	graph->addEdge(2, 3, 8);
	graph->addEdge(3, 4, 3);
	graph->addEdge(3, 5, 6);
	graph->addEdge(4, 5, 7);

	displayGraphMatrix(graph);

	minimumSpanningTree(graph);

	displayGraphMatrix(graph);
	delete graph;
}
