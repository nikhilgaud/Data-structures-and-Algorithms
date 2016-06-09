#include <iostream>
#include "Graph.h"

/*
Desc: Default constructor
Input: nothing
Output: nothing
*/
Graph::Graph()
{

}

/*
Desc: Destructor for deallocating the used memory
Input: nothing
Output: nothing
*/
Graph::~Graph()
{
	vector <Vertex*>::iterator iter = vertexObj.begin();
	while(iter!=vertexObj.end())
	{
		//free the memory allocated for each slot
		delete(*iter);		
		iter++;
	}
}

/*
Desc: Function to check whether the Graph already contains the vertice
Input: string vertice
Output: Boolean
*/
bool Graph::checkGraphDuplicate(string vertice)
{
	vector <Vertex*>::iterator iter = vertexObj.begin();
	while(iter!=vertexObj.end())
	{
		if (vertice == (*iter)->vertexName)
		{
			return true;
		}
		iter++;
	}
    return false;
}

/*
Desc: Caller function to PRIM's MST
Input: nothing
Output: nothing
*/
void Graph::callMST()
{
	mst(vertexObj);
}

/*
Desc: Function to insert new vertex in the vector
Input: string name
Output: nothing
*/
void Graph::addVertex(string name)
{
	Vertex* newVertex = new Vertex(name,100,100,NULL,NULL);
	vertexObj.push_back(newVertex);
}

/*
Desc: Function to add edge
Input: string fromNode, string toNode, int nodeWeight
Output: nothing
*/
void Graph::addEdge(string fromNode, string toNode, int nodeWeight)
{
	for ( vector <Vertex*>::iterator it = vertexObj.begin(); it != vertexObj.end(); it ++)
	{
		if (fromNode == (*it)->vertexName)
		{
			(*it)->next = new Vertex (toNode,88,nodeWeight,(*it),(*it)->next);
		}
	}

	for ( vector <Vertex*>::iterator it2 = vertexObj.begin(); it2 != vertexObj.end(); it2 ++)
	{
		if (toNode == (*it2)->vertexName)
		{
			(*it2)->next = new Vertex (fromNode,99,nodeWeight,(*it2),(*it2)->next);
			return;
		}
	}
}

/*
Desc: PRIM's Minimum Spanning Tree
Input: vector <Vertex*> &vectPassed
Output: nothing
*/
void Graph::mst(vector <Vertex*> &vectPassed)
{
	totalWeight = 0;
	vectPassed[0]->key = 0;
	vector <Vertex*>::iterator iter = vectPassed.begin();
	while(iter!=vectPassed.end())
	{
		minQ.minHeapInsert(*iter, (*iter)->key);
		iter++;
	}
	//object to hold the parent
	Vertex* minimum = NULL; 
	//object to hold the adjacency nodes
	Vertex* tempV = minimum; 

	while (minQ.isQueueEmpty() == false)
	{
		minimum = minQ.extractMinimum();
		//check whether the node is NULL
		if (minimum != NULL)
		{
			//print the name
			cout << minimum-> vertexName << " ";         
			if (minimum->parent != NULL)
			{
				//print the parent name
				cout << minimum -> parent->vertexName << " ";
			}
			else
			{
				//print NIL as parent is NIL
				cout << "NIL ";
			}
			cout << minimum -> key << endl;
			//add the weight
			totalWeight += minimum->key;
			tempV = minimum;
			for (; tempV != NULL; tempV = tempV -> next)
			{
				if (minQ.isMember(tempV) && tempV -> weight < tempV ->key)
				{
					//decrease the key value in queue
					minQ.decreaseKey(tempV, tempV->weight, minimum);
				}
			}
		}
	}
	cout << totalWeight<< endl;
}