#include <iostream>
#include <ctime>
#include <sys/time.h>
#include <cstdlib>
#include "mgraph.h"
#include "lgraph.h"
#include "algorithms.h"
#include "containers.h"
#include <list>
#include <fstream>
using namespace std;

int random(int n){
	return rand()%n;
}

int main(){
	timeval a, b;
	long sec, usec, t;

	srand(time(NULL));

	MGraph *graph = new MGraph();
	int n=1000;
	for(int i=0; i<n; ++i){
		graph->addVertex(i);
	}
	for(int i=1; i<n; ++i){

	}
	gettimeofday(&a, 0);
	gettimeofday(&b, 0);
	cout<<"start"<<endl;
	cout<<spDijkstra(graph, 0, n-1)<<endl;

	sec = b.tv_sec - a.tv_sec;
	usec = b.tv_usec - a.tv_usec;
	t = sec*1000 + usec/1000;
	cout<<t<<endl;

	delete graph;


}

