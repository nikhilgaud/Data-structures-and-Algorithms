// rbtree.cpp 

#include <iostream>
#include <iomanip>
#include "rbtree.h"

using std::cout;
using std::setw;
using std::endl;

void RBTree::reverseInOrderPrint(Node *x, int depth) 
{
   if ( x != nil )
   {
      reverseInOrderPrint(x->right, depth+1);
      cout << setw(depth*4+4) << x->color << " ";
      cout << *(x->key) << " " << *(x->value) << endl;
      reverseInOrderPrint(x->left, depth+1);
   }
}

/*
Description: Default constructor
Input: nothing
Output: nothing
*/
RBTree::RBTree()
{
	nil = new Node();
	root = nil;
}

/*
Description: Default constructor
Input: nothing
Output: nothing
*/
RBTree::Node::Node()
{
	//color = NULL;
	//this->key = NULL;
	left = NULL;
	parent = NULL;
	right = NULL;
	color = 'B';
	//this->value = NULL;
}

/*
Description: Parameterized constructor
Input: const string& key, const string& value, Node* nil
Output: nothing
*/
RBTree::Node::Node(const string& key, const string& value, Node* nil)
{
	parent = nil;
	color = 'R';
	this->key = new string(key);
	this->value = new string(value);
	right = nil;
	left = nil;
}

/*
Description: Function to left rotate the tree
Input: Node *x
Output: nothing
*/
void RBTree::leftRotate(Node *x)
{
	Node *y = x->right;
	x->right = y->left;
	if(y->left!=nil)
	{
		y->left->parent=x;
	}
	y->parent = x->parent;
	if(x->parent==nil)
	{
		root=y;
	}
	else
	{
		if(x==x->parent->left)
		{
			x->parent->left = y;
		}
		else
		{
			x->parent->right = y;
		}
	}
	y->left=x;
	x->parent=y;
}

/*
Description: Function to right rotate the tree
Input: Node *x
Output: nothing
*/
void RBTree::rightRotate(Node *x)
{
	Node *y = x->left;
	x->left = y->right;
	if(y->right!=nil)
	{
		y->right->parent=x;
	}
	y->parent = x->parent;
	if(x->parent==nil)
	{
		root=y;
	}
	else 
	{
		if(x==x->parent->right)
		{
			x->parent->right = y;
		}
		else
		{
			x->parent->left = y;
		}
	}
	y->right=x;
	x->parent=y;
}

/*
Description: Function to fixup tree after insert
Input: Node *z
Output: nothing
*/
void RBTree::rbInsertFixup(Node *z)
{
	Node *y;
	while(z->parent->color=='R')
	{
		if(z->parent==z->parent->parent->left)
		{
			y=z->parent->parent->right;
			if(y->color=='R')
			{
				z->parent->color = 'B';
				y->color = 'B';
				z->parent->parent->color = 'R';
				z = z->parent->parent;
			}
			else if(z == z->parent->right)
			{
				z = z->parent;
				//left-rotate
				leftRotate(z);
			}
			else
			{
				z->parent->color = 'B';
				z->parent->parent->color = 'R';
				//right rotate
				rightRotate(z->parent->parent);
			}
		}
		else
		{
			y=z->parent->parent->left;
			if(y->color=='R')
			{
				z->parent->color = 'B';
				y->color = 'B';
				z->parent->parent->color = 'R';
				z = z->parent->parent;
			}
			else if(z == z->parent->left)
			{
				z = z->parent;
				//right-rotate
				rightRotate(z);
			}
			else
			{
				z->parent->color = 'B';
				z->parent->parent->color = 'R';
				//left rotate
				leftRotate(z->parent->parent);
			}
		}
	}
	root->color = 'B';
}

/*
Description: Function to fixup tree after delete
Input: Node *x
Output: nothing
*/
void RBTree::rbDeleteFixup(Node *x)
{
	Node *w;
	while((x!=root) && (x->color == 'B'))
	{
		if(x == x->parent->left)
		{
			w = x->parent->right;
			if(w->color == 'R')
			{
				w->color = 'B';
				x->parent->color = 'R';
				//left rotate
				leftRotate(x->parent);
				w = x->parent->right;
			}
			if(w->left->color == 'B' && w->right->color == 'B')
			{
				w->color = 'R';
				x = x->parent;
			}
			else if(w->right->color == 'B')
			{
				w->left->color = 'B';
				w->color = 'R';
				//right rotate
				rightRotate(w);
				w = x->parent->right;
			}
			else
			{
				w->color = x->parent->color;
				x->parent->color = 'B';
				w->right->color = 'B';
				//left rotate
				leftRotate(x->parent);
				x = root;
			}
		}
		else
		{
			w = x->parent->left;
			if(w->color == 'R')
			{
				w->color = 'B';
				x->parent->color = 'R';
				//right rotate
				rightRotate(x->parent);
				w = x->parent->left;
			}
			if(w->left->color == 'B' && w->right->color == 'B')
			{
				w->color = 'R';
				x = x->parent;
			}
			else if(w->left->color == 'B')
			{
				w->right->color = 'B';
				w->color = 'R';
				//left rotate
				leftRotate(w);
				w = x->parent->left;
			}
			else
			{
				w->color = x->parent->color;
				x->parent->color = 'B';
				w->left->color = 'B';
				//right rotate
				rightRotate(x->parent);
				x = root;
			}
		}
	}
	x->color = 'B';
}

/*
Description: Function to transplant
Input: Node *u, Node *v
Output: nothing
*/
void RBTree::rbTransplant(Node *u, Node *v)
{
	if(u->parent == nil)
	{
		root = v;
	}
	else if(u == u->parent->left)
	{
		u->parent->left = v;
	}
	else
	{
		u->parent->right = v;
	}
	v->parent = u->parent;
}

/*
Description: Function to insert in rbtree
Input: Node *z
Output: nothing
*/
void RBTree::rbInsert(Node *z)
{
	Node *x,*y;
	y = nil;
	x = root;
	while(x != nil)
	{
		y = x;
		if(*(z->key) < *(x->key))
		{
			x = x->left;
		}
		else
		{
			x = x->right;
		}
	}
	z->parent = y;
	if(y == nil)
	{
		root = z;
	}
	else if(*(z->key) < *(y->key))
	{
		y->left = z;
	}
	else
	{
		y->right = z;
	}
	z->left = nil;
	z->right = nil;
	z->color = 'R';
	rbInsertFixup(z);
}

/*
Description: Function to delete node
Input: Node *z
Output: nothing
*/
void RBTree::rbDelete(Node *z)
{
	Node *y,*x;
	y = z;
	char nodeOriginalColor = y->color;//taken an extra variable for storing original color of y
	if(z->left == nil)
	{
		x = z->right;
		rbTransplant(z,x);
	}
	else if(z->right == nil)
	{
		x = z->left;
		rbTransplant(z,x);
	}
	else
	{
		y = rbTreeMaximum(z->left);
		nodeOriginalColor = y->color;
		x = y->left;
		if(y->parent == z)
		{
			x->parent = y;
		}
		else
		{
			rbTransplant(y,x);
			y->left = z->left;
			y->left->parent = y;
		}
		rbTransplant(z,y);
		y->right = z->right;
		y->right->parent = y;
		y->color = z->color;
	}
	if(nodeOriginalColor == 'B')
	{
		rbDeleteFixup(x);
	}
}

/*
Description: Function to find the tree maximum
Input: Node *x
Output: Node*
*/
RBTree::Node* RBTree::rbTreeMaximum(Node *x)
{
	while(x->right != nil)
	{
		x = x->right;
	}
	return x;
}

/*
Description: Function to find the tree minimum
Input: Node *x
Output: Node*
*/
RBTree::Node* RBTree::rbTreeMinimum(Node *x)
{
	while(x->left != nil)
	{
		x = x->left;
	}
	return x;
}

/*
Description: Function to find the successor
Input: Node *x
Output: Node*
*/
RBTree::Node* RBTree::rbTreeSuccessor(Node *x)
{
	Node *y;
	if(x->right != nil)
	{
		return rbTreeMinimum(x->right);
	}
	y = x->parent;
	while((y != nil) && (x == y->right))
	{
		x = y;
		y = y->parent;
	}
	return y;
}

/*
Description: Function to find the predecessor
Input: Node *x
Output: Node*
*/
RBTree::Node* RBTree::rbTreePredecessor(Node *x)
{
	Node *y;
	if(x->left != nil)
	{
		return rbTreeMaximum(x->left);
	}
	y = x->parent;
	while((y != nil) && (x == y->left))
	{
		x = y;
		y = y->parent;
	}
	return y;
}

/*
Description: Function to search node
Input: Node* x, const string& k
Output: Node*
*/
RBTree::Node* RBTree::rbTreeSearch(Node* x, const string& k)
{
	Node* tempNode = nil;
	if(root == nil)
	{
		return nil;
	}

	if(k > *(x->key))
	{
		//search the right subtree of x
		tempNode = x->right;
		if(tempNode != nil)
		{
			tempNode = rbTreeSearch(tempNode, k);
		}
	}
	else if (k < *(x->key))
	{
		//search the left subtree of x
		tempNode = x->left;
		if(tempNode != nil)
		{
			tempNode = rbTreeSearch(tempNode, k);
		}
	}
	else if (*(x->key) == k)
	{
		return x;
	}

	return tempNode;
}

/*
Description: Function to insert new node
Input: const string& key, const string& value
Output: nothing
*/
void RBTree::rbInsert(const string& key, const string& value)
{
	Node *insertNewNode = new Node(key,value,nil);
	insertNewNode->parent = nil;
	insertNewNode->left = nil;
	insertNewNode->right = nil;
	insertNewNode->key = new string(key);
	insertNewNode->value = new string(value);
	rbInsert(insertNewNode);
	//rbInsertFixup(insertNewNode);
}

/*
Description: Function to delete node
Input: const string& key, const string& value
Output: nothing
*/
void RBTree::rbDelete(const string& key, const string& value)
{
	if(root!= nil)
	{
		Node* searchResult;
		Node* nodePredecessor;
		Node* nodeSuccessor;
		searchResult = rbTreeSearch(root, key);
		//iterate until the search result doesn't return anything
		while(searchResult != nil)
		{
			//check whether the value of the node to be deleted is the same
			if(*(searchResult->value) == value)
			{
				rbDelete(searchResult);
				//deallocate
				delete(searchResult);
				//check whether duplicate exists
				searchResult = rbTreeSearch(root, key);
			}			
			nodePredecessor = searchResult;
			while(nodePredecessor != nil)
			{
				//search for its predecessor until all the nodes to be deleted are found
				nodePredecessor = rbTreePredecessor(nodePredecessor);
				//check for the value as nodes with similar keys can have different values
				if((nodePredecessor != nil) && (*nodePredecessor->key == key) && (*(nodePredecessor->value) == value))
				{
					rbDelete(nodePredecessor);
					//deallocate
					delete(nodePredecessor);
					nodePredecessor = rbTreeSearch(root, key);
				}
			}
			nodeSuccessor = searchResult;
			while(nodeSuccessor != nil)
			{
				//search for its successor until all the nodes to be deleted are found
				nodeSuccessor = rbTreeSuccessor(nodeSuccessor);
				//check for the value as nodes with similar keys can have different values
				if((nodeSuccessor != nil)&&(*nodeSuccessor->key == key)&&(*(nodeSuccessor->value) == value))
				{
					rbDelete(nodeSuccessor);
					//deallocate
					delete(nodeSuccessor);
					nodeSuccessor = rbTreeSearch(root, key);
				}
			}
			//check whether the node is still present
			searchResult = rbTreeSearch(root, key);

			if(searchResult != nil)
			{
				if(*(searchResult->value) != value)
				{
					break;
				}
			}		
		}
	}
}

/*
Description:
Input:
Output:
*/
RBTree::Node* RBTree::rbTreeSearch(const string& key, const string& value)
{
	Node *tempNode = root;
	while(tempNode!=nil)
	{
		if((*(tempNode->key)==key) && (*(tempNode->value)==value))
			break;
		else if(key<*(tempNode->key))
			tempNode = tempNode->left;
		else
			tempNode = tempNode->right;
	}
	return tempNode;
}

/*
Description: Function to find using predecessor and successor
Input: const string& key
Output: vector<const string*>
*/
vector<const string*> RBTree::rbFind(const string& key)
{
	vector<const string*> searchedNodes;	
	if(root!=nil)
	{
		//string *temp = new string(*(nodeFound->value));
		Node *nodeFound = rbTreeSearch(root, key);
		if(nodeFound!=nil)
		{
			searchedNodes.push_back(nodeFound->value);
			//loop over to find multiple nodes using predecessor and successor
			Node* nodePredecessor = nodeFound;
			while(nodePredecessor!=nil)
			{
				nodePredecessor = rbTreePredecessor(nodePredecessor);
				if((nodePredecessor != nil) && (*nodePredecessor->key == key))
				{
				searchedNodes.push_back(nodePredecessor->value);
				}
			}
			Node* nodeSuccessor = nodeFound;
			while(nodeSuccessor!=nil)
			{
				nodeSuccessor = rbTreeSuccessor(nodeSuccessor);
				if((nodeSuccessor != nil) && (*nodeSuccessor->key == key))
				{
				searchedNodes.push_back(nodeSuccessor->value);
				}
			}
		}
	}
	return searchedNodes;
}

/*
Description: Function to call reverseInOrderPrint
Input: nothing
Output: nothing
*/
void RBTree::rbPrintTree()
{
	if(root!=nil)
	{
		reverseInOrderPrint(root, 0);
	}
}

/*
Description: Destructor
Input: nothing
Output: nothing
*/
RBTree::Node::~Node()
{
	/*delete key;
	delete value;*/
}

/*
Description: Desctructor
Input: nothing
Output: nothing
*/
RBTree::~RBTree()
{
	
}