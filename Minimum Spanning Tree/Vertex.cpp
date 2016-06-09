#include "Vertex.h"

/*
Desc: parameterized constructor for initializing the attributes of the vertex
Input: string p_vertexName,int p_key, int p_weight, Vertex* p_parent, Vertex* p_next
Output: nothing
*/
Vertex::Vertex(string p_vertexName,int p_key, int p_weight, Vertex* p_parent, Vertex* p_next)
{
	vertexName = p_vertexName;
	weight = p_weight;
	parent = p_parent;
	next = p_next;
	key = p_key;
}