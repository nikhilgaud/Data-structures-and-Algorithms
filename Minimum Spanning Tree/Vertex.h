# ifndef _VERTEX__H
# define _VERTEX__H
#include <iostream>
# include <string>

using namespace std;

class Vertex
	{
	private:
		Vertex *parent;
		Vertex *next;
		string vertexName;
		int key, weight;

	public:
		//friend classes
		friend class MinPriority;
		friend class Graph;
		Vertex(string vertexName,int key, int weight, Vertex* parent, Vertex* next);
		~Vertex()
		{};
	};

# endif