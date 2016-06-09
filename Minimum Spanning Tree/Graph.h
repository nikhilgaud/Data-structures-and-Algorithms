#ifndef _GRAPH_H_
#define _GRAPH_H_
#include <iostream>
#include "MinPriority.h"
#include "Vertex.h"
#include <vector>
#include <string>

using namespace std;

class Graph
{
private:

	vector<Vertex*> vertexObj;//to store the adjacency list
	MinPriority minQ;
	int totalWeight;
	//PRIM's MST function
	void mst(vector <Vertex*> &theVect);

public:

	Graph();
	~Graph();
	//function for adding vertices
	void addVertex(string vertexName);
	//function for adding edges
	void addEdge(string fromNode, string toNode, int nodeWeight);
	bool checkGraphDuplicate(string vertice);
	void callMST();
};

#endif