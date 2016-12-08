//  Node.h

#ifndef Node_h
#define Node_h

#include <iostream>
#include <cstring>  // for strcpy()
#include <fstream>
using namespace std;

#define MAX 100

class Node
{
    public:
	    int freq;
	    char ch[MAX];
        Node *left, *right;
           
    public:
          Node ();
          ~Node();
};

#endif  
          
                 
