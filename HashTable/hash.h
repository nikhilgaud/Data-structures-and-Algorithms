/* This assignment originated at UC Riverside. The hash table size
 should be defined at link time. Use -D HASH_TABLE_SIZE=X */
 
#ifndef __HASH_H
#define __HASH_H

#include <string>
#include <list>

using std::string;
using std::list;

class Hash {

public:
  void remove(string);              // remove key from hash table
  void print();                     // print the entire hash table
  void processFile(string);         // open file and add keys to hash table
  bool search(string);              // search for a key in the hash table
  void output(string);              // print entire hash table to a file
  void printStats();                // print statistics

private:
   // HASH_TABLE_SIZE should be defined using the -D option for g++
   list<string> hashTable [HASH_TABLE_SIZE];
   int collisions;
   int longestList;
   double avgLength;

   int hf(string);                  // the hash function

// put additional variables/functions below
// do not change anything above!

};

#endif
