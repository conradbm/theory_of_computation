//  Tree.h

#ifndef Tree_h
#define Tree_h

#include "Node.h"

class Tree
{          
    public:
         Tree ();
		 void sort(Node *[], int);
		 Node *createNode(char[], int);
		 void sright(Node *[], int);
		 void printT (Node *p, int moveC);
};

#endif  
          
