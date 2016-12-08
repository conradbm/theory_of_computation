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

void Tree::Assign_Code(Node* tree, int huffmCode[], int n)
{
    int i;
    
    if ((tree->left == NULL) && (tree->right == NULL))
    {
        vector<int> temp;
        if (tree->ch[0] == '\n') {
            cout<<"LR"<<" code: ";
        }
        else
            cout<<tree->ch<<" code: ";
        for (i = 0; i < n; i++)
         {
          cout<<huffmCode[i];
             temp.push_back(huffmCode[i]);
         }
        cout<<"\n";
        std::pair<char*,vector<int> > pair (tree->ch,temp);
        Tree::globalMap.insert(pair);
        cout << "inserted successfully." << endl;
    }
    
    else
    {
        huffmCode[n] = 0;
        n++;
        Assign_Code(tree->left, huffmCode, n);
        huffmCode[n - 1] = 1;
        Assign_Code(tree->right, huffmCode, n);
    }
}

void Tree::writeCode(Node* tree, int huffmCode[], int n, char inChar1)
{
            int i;
			ofstream outF;
			outF.open("outFile1.txt",ios::app);
			
			if (!outF)
			{
				cout<<"Error: File couldn't be open";
				system("pause");
				exit(1);
			} 
			
            if ((tree->left == NULL) && (tree->right == NULL))
            {
                        if(tree->ch[0]==inChar1) 
							for (i = 0; i < n; i++)
							{
								outF<<huffmCode[i];
							    cout<<huffmCode[i];             
							}

		    }
			else
	        {
				huffmCode[n] = 0;
				n++;
				writeCode(tree->left, huffmCode, n, inChar1);
				huffmCode[n - 1] = 1;
				writeCode(tree->right, huffmCode, n, inChar1);
            }
}

void Tree::printT (Node *p, int moveC)
{    
    if (p != NULL)
    {
          printT (p->right, moveC+6);
          
          for(int i=0; i < moveC; i++)
                  cout << " ";
        
        if (p->ch[0] == '\n') {
            cout << "LF" <<"," << p->freq << endl;
         }
        else
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



void Tree::printCodes(){
    
    for (std::map<char*,vector<int> >::iterator it = Tree::globalMap.begin();it!=Tree::globalMap.end();++it){
        if (it->first[0] == '\n') {
            cout << "LR" << "->";
        }
        else
            cout << it->first << "->";
        for (int i = 0; i < it->second.size(); i++) {
            cout << it->second.at(i);
        }
        cout << endl;
    }
}