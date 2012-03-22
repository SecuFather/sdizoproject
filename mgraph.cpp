#include "mgraph.h"

MGraph::MGraph():Graph(), maxIndex(-1), vCount(0){
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

bool MGraph::addVerticle(int at){
	if(matrix[at][at]){
		return false;
	}
	if(at > maxIndex){
		maxIndex = at;
	}
	++vCount;
	return matrix[at][at] = 1;
}
bool MGraph::removeVerticle(int at){
	if(matrix[at][at]){
		for(int i=0; i<at; ++i){
			matrix[at][i] = 0;
		}
		for(int i=at; i<max; ++i){
			matrix[i][at] = 0;
		}
		--vCount;
		return true;
	}else{
		return false;
	}
}
bool MGraph::addEdge(int x, int y, int value){
	if(matrix[y][x]){
		return false;
	}else{
		return matrix[y][x] = value;
	}
}
bool MGraph::removeEdge(int x, int y){
	if(matrix[y][x]){
		matrix[y][x] = 0;
		return true;
	}else{
		return false;
	}
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

void MGraph::setEdge(int x, int y, int v){
	matrix[y][x] = v;
}

int MGraph::getMax(){ return max; }
int MGraph::getMaxIndex(){ return maxIndex; }
int **MGraph::getMatrix(){ return matrix; }
int MGraph::getVertexCount(){ return vCount; }
void MGraph::fix(){
	for(int i=0; i<=maxIndex; ++i){
		for(int j=0; j<i+1; ++j){
			matrix[i][j] = (matrix[i][j] < 0 ? -matrix[i][j] : matrix[i][j]);
		}
	}
}
