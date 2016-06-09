// rbapp.cpp 

#include <iostream>
#include <iomanip>
#include "rbapp.h"
#include "rbtree.h"
#include <fstream>

using namespace std;

RBapp rbApp;

//enum to check the command to execute
enum execCommand
{
	insert,
	finish,
	del,
	print,
	quit
};

/*
Description: Hash function to map the command with the enum value and select the appropriate case
Input: string command
Output: int case type
*/
int Hash(string command)
{
	if(command=="insert")
		return insert;
	if(command=="find")
		return finish;
	if(command=="delete")
		return del;
	if(command=="print")
		return print;
	if(command=="quit")
		return quit;
	return -1;
}

/*
Description: Function to Split the input into command and key-value
Input:vector<string> &tokens,string &keyValue
Output: nothing
*/
void stringSplit(vector<string> &tokens,string &keyValue)
{
	keyValue = keyValue.substr(1,keyValue.length());
	tokens.push_back(keyValue.substr(0,keyValue.find_first_of(" ",0)));
	tokens.push_back(keyValue.substr(keyValue.find_first_of(" ",0)+1,keyValue.length()));
}


int main()
{
	//RBapp rbApp0;
	rbApp.mainLoop();
	return 0;  
}

/*
Description: Function to call processCommand
Input: nothing
Output: nothing
*/
// process commands until done
void RBapp::mainLoop()
{
	processCommand();
}

/*
Description: Function to identify the command and invoke correct operation
Input: nothing
Output: nothing
*/
void RBapp::processCommand()
{
	string rbChoice;
	string rbCommand;
	string keyValue;
	//string fileName="test1.txt";
	//ifstream readFile;
	//readFile.open(fileName);
	//read until the end of file is encountered
	//if(readFile.is_open())
	//{
		//iterate until the end of file is reached
		//while(!readFile.eof()) 
		while(!cin.eof()) 
		{
			//read line by line to a temporary string buffer
			//getline(readFile,rbChoice); added for reading from file
			getline(cin,rbChoice);
			if(rbChoice.empty())
				continue;
			//extract command from the input sequence
			rbCommand = rbChoice.substr(0,rbChoice.find_first_of(" ",0));
			keyValue = "";
			switch(Hash(rbCommand))
			{
				case 0:
					keyValue = rbChoice.substr(rbChoice.find_first_of(" ",0),rbChoice.length());
					processInsert(keyValue);
					break;
	
				case 1:
					keyValue = rbChoice.substr(rbChoice.find_first_of(" ",0),rbChoice.length());
					processFind(keyValue);
					break;
	
				case 2:
					keyValue = rbChoice.substr(rbChoice.find_first_of(" ",0),rbChoice.length());
					processDelete(keyValue);
				break;
      
				case 3:
					processPrint();
				break;
	
				case 4:
					processQuit();
				break;
			}
		}
	//}
}

/*
Description: Function to call the insert function
Input: string& keyValue
Output: nothing
*/
void RBapp::processInsert(string& keyValue)
{
	if(keyValue.empty())
		return;
	vector<string> tokens;
	stringSplit(tokens,keyValue);
	rbApp.myRBT.rbInsert(tokens[0],tokens[1]);
}

/*
Description: Function to call the Find function
Input: string& key
Output: nothing
*/
void RBapp::processFind(string& key)
{
	if(key.empty())
		return;
	key = key.substr(1,key.length());
	vector<const string*> resultantVector = rbApp.myRBT.rbFind(key);
	for(vector<const string*>::iterator i=resultantVector.begin();i!=resultantVector.end();i++)
	{
		cout << key << " " << *(*i) << endl;
	}
}

/*
Description: Function to call function for delete nodes
Input: string& keyValue
Output: nothing
*/
void RBapp::processDelete(string& keyValue)
{
	if(keyValue.empty())
		return;
	vector<string> tokens;
	stringSplit(tokens,keyValue);
	rbApp.myRBT.rbDelete(tokens[0],tokens[1]);
}

/*
Description: Function to print the RB TRee
Input: nothing
Output: nothing
*/
void RBapp::processPrint()
{
	rbApp.myRBT.rbPrintTree();
}

/*
Description: Exit process
Input: nothing
Output: nothing
*/
void RBapp::processQuit()
{
	exit(0);
}