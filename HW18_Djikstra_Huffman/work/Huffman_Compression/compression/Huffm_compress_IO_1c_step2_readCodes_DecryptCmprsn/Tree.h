//  Tree.h

#ifndef Tree_h
#define Tree_h

#include <map>
#include <utility>
#include <vector>
#include <sstream>
#include "Node.h"

class Tree
{          
    public:
         Tree ();
    map<char*,vector<int> > map_char_freq_as_int;
    map<char*,string> map_char_freq_as_string;
		 void sort(Node *[], int);
		 Node *createNode(char[], int);
		 void sright(Node *[], int);
 		 void Assign_Code(Node*, int [], int);
	 	 void writeCode(Node*, int [], int, char ch1);
		 void printT (Node *p, int moveC);
    void update_to_strings_only();
    void printMappings();
};

#endif  
          
