#ifndef MSTAPP_H
#define MSTAPP_H
#include "Graph.h"

class MSTapp
{
private:
	Graph myGraph;
	//variable to check for new line character
	char varpeek;
public:
	void readGraph();
	MSTapp(){};
	~MSTapp(){};
};

#endif