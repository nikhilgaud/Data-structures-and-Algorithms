# include "MSTapp.h"

int main()
{
	MSTapp mst;
	mst.readGraph();
	return 0;
}

void MSTapp::readGraph()
{
	while(!cin.eof())//read until end of file is encountered
	{
		string vertex;
		//take first input
		cin >> vertex;
		//check whether it is empty
		if(vertex.length()!=0)
		{
			//check whether vertex is already present, if not add
			if(!myGraph.checkGraphDuplicate(vertex) && varpeek!= '\n')
			{
				myGraph.addVertex(vertex);
				varpeek = cin.peek();
			}
			//if is an edge, add edge
			else
			{
				string vertex2;
				cin >> vertex2;
				int weight;
				cin >> weight;
				myGraph.addEdge(vertex, vertex2, weight);
			}
		}
	}
	myGraph.callMST();
}