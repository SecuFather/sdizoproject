#include "lgraph.h"

LGraph::LGraph() : vertices(new list<Edge>*[max]){
	for(int i=0; i<max; ++i){
		vertices[i] = 0;
	}
}

LGraph::~LGraph(){
	for(int i=0; i<max; ++i){
		if(vertices[i]){
			delete vertices[i];
		}
	}
	delete[] vertices;
}

bool LGraph::addVertex(int at){
	if(vertices[at]){
		return false;
	}else{
		vertices[at] = new list<Edge>;
		if(maxIndex < at){
			maxIndex = at;
		}
		return ++vCount;
	}
}

bool LGraph::addEdge(int x, int y, int value){
	if(vertices[x] && value){
		Edge e(x, y, value);
		vertices[x]->push_back(e);
		vertices[y]->push_back(e);
		return true;
	}else{
		return false;
	}
}

Edge LGraph::removeEdge(int x, int y){
	if(x == y){
		delete vertices[x];
		vertices[x] = 0;
		return Edge();
	}
	Edge e(*current);
	return e;
}

int LGraph::nextVertex(int prev){
	for(int i=prev+1; i<maxIndex+1; ++i){
		if(vertices[i]){
			return i;
		}
	}
	return -1;
}

int LGraph::nextEdge(int x, int prev){
	for(prev < 0 ? current = vertices[x]->begin() : ++current; current != vertices[x]->end(); ++current){
		if(vertices[current->y]){
			return getMaxIndex()+1;
		}
	}
	return -1;
}

int LGraph::getEdge(int x, int y){
	if(x == y && vertices[x]){
		return 1;
	}
	return 0;
}
