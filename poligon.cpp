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
#include <sstream>
using namespace std;

int random(int n){
	return rand()%n;
}

void testAlgorithm(Graph *graph, char f, char kind, int n, int &sum){
	timeval a, b;
	long sec, usec, t;

	cout << f <<"(" << kind << "): ";
	gettimeofday(&a, 0);
	switch (f) {
	case 'p':
		mstPrim (graph);
		break;
	case 'k':
		mstKruscal(graph);
		break;
	case 'd':
		spDijkstra(graph, 0, n - 1);
		break;
	case 'b':
		spBellman(graph, 0, n - 1);
		break;
	}
	gettimeofday(&b, 0);

	sec = b.tv_sec - a.tv_sec;
	usec = b.tv_usec - a.tv_usec;
	sum += t = sec * 1000 + usec / 1000;

	cout << t << endl;

}

void randomGraph(Graph *graph, double density, int n){
	int y, v;

	for (int i = 0; i < n; ++i) {
		graph->addVertex(i);
		graph->addVertex(i);
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < static_cast<int>(density * (n - i)); ++j) {
			y = random(n - i) + i;
			v = random(100) + 1;
			graph->addEdge(i, y, v);
			graph->addEdge(i, y, v);
		}
	}
}

void generatePlot(){

}

int main(int argc, char **argv){
	const int xCount=10, ycount=15, dCount=3, nStep=500;
	double dStep=0.4;
	int lResult[ycount], mResult[ycount];
	char *funk = "pkdb";

	srand(time(NULL));

	for(double k=dStep/2.0; k<dCount*dStep; k+=dStep){
		for(char *f=funk; f != 0; ++f){
			for(int n=nStep; n<nStep*ycount+1; n+=nStep){
				int sl = 0, sm = 0;
				for(int i=0; i<xCount; ++i){

					LGraph *lgraph = new LGraph();
					MGraph *mgraph = new MGraph();

					randomGraph(lgraph, k, n);
					randomGraph(mgraph, k, n);

					testAlgorithm(lgraph, *f, 'L', n, sl);
					testAlgorithm(mgraph, *f, 'M', n, sm);

					delete lgraph;
					delete mgraph;
				}
				lResult[n/nStep-1] = sl;
				mResult[n/nStep-1] = sm;
			}
		}
	}
}

