// Tree.cpp

#include "Tree.h"

Tree::Tree()
{
}

Node *Tree::createNode(char chars1[], int freq1)
{
    Node* p;
    p = new Node;
    
    p->freq = freq1;
    strcpy( p->ch , chars1);
    
    p->right = p->left = NULL;
    
    return(p);
}

void Tree::printT (Node *p, int moveC)
{    
    if (p != NULL)
    {
          printT (p->right, moveC+6);
          
          for(int i=0; i < moveC; i++)
                  cout << " ";
                  
          cout << p->ch<<","<<p->freq<<endl;

          printT (p->left, moveC+6);
    }
}

void Tree::sort(Node *a[], int n)
{
    int i, j;
    Node* temp;
    
    for (i = 0; i < n - 1; i++)
        for (j = i; j < n; j++)
            if (a[i]->freq > a[j]->freq)                
			{
                temp = a[i];
                a[i] = a[j];             
			    a[j] = temp;
            }
}

void Tree::sright(Node *a[], int n)
{
    int i;
    for (i = 1; i < n - 1; i++)
         a[i] = a[i + 1];
}
