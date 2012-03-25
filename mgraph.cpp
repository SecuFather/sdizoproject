#include "mgraph.h"

MGraph::MGraph():Graph(){
	matrix = new int*[max];
	for(int i=0; i<max; ++i){
		matrix[i] = new int[i+1];
		for(int j=0; j<i+1; ++j){
			matrix[i][j] = 0;
		}
	}
}
MGraph::~MGraph(){
	for(int i=0; i<max; ++i){
		delete[] matrix[i];
	}
	delete[] matrix;
}

bool MGraph::addVertex(int at){
	if(matrix[at][at]){
		return false;
	}
	if(at > maxIndex){
		maxIndex = at;
	}
	++vCount;
	return matrix[at][at] = 1;
}

bool MGraph::addEdge(int x, int y, int value){
	if(matrix[y][x]){
		return false;
	}else{
		return matrix[y][x] = value;
	}
}
Edge MGraph::removeEdge(int x, int y){
	Edge e(x, y);
	e.v = matrix[e.y][e.x];

	matrix[e.y][e.x] = 0;
	return e;
}

int MGraph::nextVertex(int prev){
	for(int i=prev+1; i<=maxIndex; ++i){
		if(matrix[i][i]){
			return i;
		}
	}
	return -1;
}

int MGraph::nextEdge(int x, int prev){
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

int MGraph::getEdge(int x, int y){
	if(matrix[y][x] > 0){
		return matrix[y][x];
	}
	return -1;
}

