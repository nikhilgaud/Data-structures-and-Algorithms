#include <iostream>
#include "MinPriority.h"
#include <math.h>

/*
Desc: Default constructor
Input: nothing
Output: nothing
*/
MinPriority::MinPriority()
{
	minHeapSize = 0;//initialize heap size to 0
}

/*
Desc: Destructor
Input: nothing
Output: nothing
*/
MinPriority::~MinPriority()
{}

/*
Desc: isQueueEmpty to check whether the queue is empty
Input: nothing
Output: Boolean
*/
bool MinPriority::isQueueEmpty()
{
	//if the heap is empty return true
	if (minHeapSize < 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
Desc: MinHeapSwapParent for swapping
Input: integer requiredPosition
Output: nothing
*/
void MinPriority::MinHeapSwapParent(int requiredPosition)
{
	//moving node to correct position based on comparison with parents having greater key value
	while(minHeapSize > 0 && myqueueObj[parent(requiredPosition)]->key > myqueueObj[requiredPosition]->key)
	{
		swap(myqueueObj[requiredPosition],myqueueObj[parent(requiredPosition)]);
		requiredPosition = parent(requiredPosition);
	}
}

/*
Desc: Function to min Heapify the tree
Input: integer i
Output: nothing
*/
void MinPriority::minHeapify(int i)
{
	int l, r;
	l = leftChild(i);
	if(l==0)
	{
		l=1;
	}
	r = rightChild(i);
	if(r==1)
	{
		r=2;
	}
	int smallest = i;
	//if left child is smaller than parent set smallest to left child
	if( l <= minHeapSize && (myqueueObj[l]->key < myqueueObj[i]->key))
	{
		smallest = l;
	}
	else
	{
		smallest = i;
	}
	//if right child is smaller than the current smallest, set it to right child
	if(r <= minHeapSize && (myqueueObj[r]->key < myqueueObj[smallest]->key))
	{
		smallest = r;
	}

	if(smallest!=i)
	{
		swap(myqueueObj[i],myqueueObj[smallest]);
		minHeapify(smallest);
	}
}

/*
Desc: parent returns the parent of the given node
Input: integer
Output: integer, index of parent
*/
int MinPriority::parent(int i)
{

	return floor(static_cast<float>(i/2));
}

/*
Desc: leftChild returns the left child of the given node
Input: integer i
Output: integer, index of left child
*/
int MinPriority::leftChild(int i)
{
	return floor(static_cast<float>(2*i));
}

/*
Desc: rightChild returns the right child of the given node
Input: integer i
Output: integer, index of right child
*/
int MinPriority::rightChild(int i)
{
	return floor(static_cast<float>((2*i) + 1));
}

/*
Desc: Function to insert in the min heap
Input: Vertex* vertice, int key
Output: nothing
*/
void MinPriority::minHeapInsert(Vertex* vertice, int key)
{
	//insert at end
	myqueueObj.push_back(vertice);
	//increase size of heap
	minHeapSize++;
	decreaseKey(vertice,key,NULL);
}

/*
Desc: Function to decrease the key of a vertice
Input: Vertex* pointer, int newKey, Vertex* parent 
Output: nothing
*/
void MinPriority::decreaseKey(Vertex* pointer, int newKey, Vertex* parent)
{
	int tempCount = 0;
	int requiredPosition = 0;
	vector <Vertex*>::iterator iter = myqueueObj.begin();
	while(iter!=myqueueObj.end())
	{
		if((*iter)->vertexName == pointer->vertexName)
		{
			requiredPosition = tempCount;
		}
		tempCount++;
		iter++;
	}
	if(newKey > myqueueObj[requiredPosition]->key)
	{
		return;//if new key is greater than the current key
	}
	//update the key
	myqueueObj[requiredPosition]->key = newKey;
	//update to new parent
	myqueueObj[requiredPosition]->parent = parent;

	MinHeapSwapParent(requiredPosition);
}

/*
Desc: Function to extract the minimum from the queue
Input: nothing
Output: Vertex*
*/
Vertex* MinPriority::extractMinimum()
{
	if(minHeapSize < 1)
	{
		return NULL;//heap empty, return null
	}
	//set root to minimum
	Vertex* minimum = myqueueObj[0];
	myqueueObj[0] = NULL;
	myqueueObj.erase(myqueueObj.begin());
	//decrease size of the heap
	minHeapSize = minHeapSize - 1;
	minHeapify(0);
	//cout << "min->" << length;
	return minimum;
		
}

/*
Desc: Function to check whether the node already exists in myqueueObj
Input: Vertex* objVertex
Output: Boolean
*/
bool MinPriority::isMember(Vertex* objVertex)
{
	vector <Vertex*>::iterator iter = myqueueObj.begin();
	while(iter!=myqueueObj.end())
	{
		if ((*iter) ->vertexName == objVertex -> vertexName)
		{
			return true;
		}
		iter++;
	}
    return false;
}