#ifndef _MIN_PRIORITY_H
#define _MIN_PRIORITY_H
#include <iostream>
#include "Vertex.h"
#include <vector>

using namespace std;

class MinPriority
{
private:
	
	int minHeapSize;

	typedef vector<Vertex*> queueObj;
	queueObj myqueueObj;

	void MinHeapSwapParent(int requiredPosition);
	void minHeapify(int position);
	int parent(int i);
	int leftChild(int i);
	int rightChild(int i);

public:

	MinPriority();
	~MinPriority();
	//insert into min Heap
	void minHeapInsert(Vertex* vertice, int key);
	void decreaseKey(Vertex* pointer, int newKey, Vertex* parent);
	Vertex* extractMinimum();
	bool isMember(Vertex* objVertex);
	bool isQueueEmpty();
};

# endif