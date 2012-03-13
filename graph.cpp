#include "graph.h"
#include "util.h"

Graph::Graph():max(1000), maxIndex(-1){
	matrix = new int*[max];
	for(int i=0; i<max; ++i){
		matrix[i] = new int[i+1];
		for(int j=0; j<i+1; ++j){
			matrix[i][j] = 0;
		}
	}
}
Graph::~Graph(){
	for(int i=0; i<max; ++i){
		delete[] matrix[i];
	}
	delete[] matrix;
}

bool Graph::addVerticle(int at){
	if(matrix[at][at]){
		return false;
	}
	if(at > maxIndex){
		maxIndex = at;
	}
	return matrix[at][at] = 1;
}
bool Graph::removeVerticle(int at){
	if(matrix[at][at]){
		for(int i=0; i<at; ++i){
			matrix[at][i] = 0;
		}
		for(int i=at; i<max; ++i){
			matrix[i][at] = 0;
		}
		return true;
	}else{
		return false;
	}
}
bool Graph::addEdge(int x, int y, int value){
	if(matrix[y][x]){
		return false;
	}else{
		return matrix[y][x] = value;
	}
}
bool Graph::removeEdge(int x, int y){
	if(matrix[y][x]){
		matrix[y][x] = 0;
		return true;
	}else{
		return false;
	}
}

int Graph::nextVertex(int prev){
	for(int i=prev+1; i<=maxIndex; ++i){
		if(matrix[i][i]){
			return i;
		}
	}
	return -1;
}

int Graph::nextEdge(int x, int prev){
	for(int i=prev+1; i<x; ++i){
		if(matrix[x][i] > 0){
			return i;
		}
	}
	prev = (prev < x ? x : prev );
	for(int i=prev+1; i<=maxIndex; ++i){
		if(matrix[i][x] > 0){
			return i;
		}
	}
	return -1;
}

int Graph::getEdge(int x, int y){
	if(matrix[y][x] > 0){
		return matrix[y][x];
	}
	return -1;
}

void Graph::setEdge(int x, int y, int v){
	matrix[y][x] = v;
}

int Graph::getMax(){ return max; }
int Graph::getMaxIndex(){ return maxIndex; }
int **Graph::getMatrix(){ return matrix; }
void Graph::fix(){
	for(int i=0; i<=maxIndex; ++i){
		for(int j=0; j<i+1; ++j){
			matrix[i][j] = -matrix[i][j];
		}
	}
}
