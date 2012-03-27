#include "containers.h"
#include <algorithm>
using namespace std;

bool operator<(const Edge &e1, const Edge &e2){
	return e1.v > e2.v;
}

bool operator<(const Vertex &v1, const Vertex &v2){
	return v1.v > v2.v;
}

Heap::Heap(int size) : vertices(new Vertex*[size]), index(new int[size]), heapSize(0), maxSize(size) {
	for(int i=0; i<maxSize; ++i){
		 vertices[i] = new Vertex();
		 index[i] = -1;
	 }
}

Heap::~Heap(){
	for(int i=0; i<maxSize; ++i){
		delete vertices[i];
	}
	delete[] vertices;
	delete[] index;
}

void Heap::addNode(int key, int value){
	vertices[heapSize]->key = key;
	vertices[heapSize]->v = value;
	vertices[heapSize]->pos = heapSize;
	index[key] = heapSize;
	repairHeap(heapSize++);
}

void Heap::setNode(int key, int value){
	if(index[key] < 0){
		return addNode(key, value);
	}else{
		if(vertices[index[key]]->v > value){
			vertices[index[key]]->v = value;
			repairHeap(index[key]);
		}
	}
}

int Heap::pop(){
	if(!heapSize){
		return -1;
	}
	swap(0, heapSize-1);
	--heapSize;
	repairHeap(0);
	return vertices[heapSize]->v;
}
int Heap::top(){
	return vertices[0]->key;
}

void Heap::repairHeap(int at){
	int i = (at-1)/2;

	if(vertices[i]->v > vertices[at]->v){ //up
		while(i >= 0 && vertices[i]->v > vertices[at]->v){
			swap(at, i);
			at = i;
			i = (at+1)/2-1;
		}
	}else{ //down
		i = 2*at+1;
		while( (i < heapSize && vertices[at]->v > vertices[i]->v) ||
			   (i+1 < heapSize && vertices[at]->v > vertices[i+1]->v) ){
			if(i+1 < heapSize && vertices[i]->v > vertices[i+1]->v){
				++i;
			}
			swap(at, i);
			at = i;
			i = 2*at+1;
		}
	}
}

void Heap::swap(int at, int min){
	Vertex tmp = *vertices[min];
	vertices[min]->key = vertices[at]->key;
	vertices[min]->v = vertices[at]->v;
	vertices[at]->key = tmp.key;
	vertices[at]->v = tmp.v;
	index[vertices[at]->key] = vertices[at]->pos;
	index[vertices[min]->key] = vertices[min]->pos;
}
