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

	cout << f << "(" << kind << "): ";
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

string getFileName(char f, double density){
	stringstream fileName;
		if(f == 'p' || f =='k'){
			fileName << "mst" << density;
		}else{
			fileName << "sp" << density;
		}
	return fileName.str();
}
string getFunctionName(char f){
	switch(f){
	case 0:
	case 'p':
		return "Prim";
	case 1:
	case 'k':
		return "Kruskal";
	case 2:
	case 'd':
		return "Dijkstra";
	}
	return "Bellman";
}

void writeToFile(char f, char kind, double density, int *result, int n){
	ofstream out(getFileName(f, density).c_str(), ios_base::app);

	out << getFunctionName(f) << kind << " = [ ";
	for(int i=0; i<n; ++i){
		out << result[i] << " ";
	}
	out<< "];"<<endl;
}

void generatePlot(char f, double density, int nStep, int nCount){
	string fileName = getFileName(f, density);
	ofstream out(fileName.c_str(), ios_base::app);
	int k = (f=='p' ? 0 : 2);
	char comma=' ';
	const char *lm = "LM";

	out << "x = " << nStep << ":" << nStep << ":" << nStep*nCount << ";"<<endl;

	out << "plot(" << endl;
	for(int i=k; i<k+2; ++i){
		for(int j=0; j<2; ++j){
			out << comma << "x," << getFunctionName(i) << lm[j] << ",'-" << (i*2+j)%4
																<< "','linewidth',5" << endl;
			comma = ',';
		}

	}
	out << ");"<<endl;

	out << "legend(";
	for(int i=k; i<k+2; ++i){
		for(int j=0; j<2; ++j){
			out << "'" << getFunctionName(i) << lm[j] << "',";
		}
	}
	out << "'location', 'northwest');"<<endl;

	if(k < 2){
			out << "title('Minimum spanning tree(density: " << density << ")');" << endl;
		}else{
			out << "title('Shortest path(density: " << density << ")');" << endl;
		}
		out << "xlabel('n-vertices');" << endl;
		out << "ylabel('time[ms]');" << endl;

	out << "print " << fileName << ".jpg;" << endl;

	system((string("octave ") + fileName).c_str());
	system((string("rm ") + fileName).c_str());
}

int main(int argc, char **argv){
	const int xCount=5, nCount=20, dCount=3, nStep=200;
	double dStep=0.4;
	int *lResult = new int[nCount], *mResult = new int[nCount];
	char *funk = (char*)"pkdb";

	srand(time(NULL));

	for(double k=dStep/2.0; k<dCount*dStep; k+=dStep){
		for(char *f=funk; *f != 0; ++f){
			for(int n=nStep; n<nStep*nCount+1; n+=nStep){
				int sl = 0, sm = 0;
				for(int i=0; i<xCount; ++i){

					LGraph *lgraph = new LGraph(n);
					MGraph *mgraph = new MGraph(n);

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
			writeToFile(*f, 'L', k, lResult, nCount);
			writeToFile(*f, 'M', k, mResult, nCount);
		}
		generatePlot('p', k, nStep, nCount);
		generatePlot('d', k, nStep, nCount);
	}
	delete[] lResult;
	delete[] mResult;
}

