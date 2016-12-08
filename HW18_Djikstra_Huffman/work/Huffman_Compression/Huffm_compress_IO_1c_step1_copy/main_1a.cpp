    /***********************************/
   /*     AUTHOR: Blake Conrad      ***/
  /**     CONTENTS:                 **/
 /***       Huffman Compression   ***/
/***********************************/


/*****************************/
/***     PRE-PROCESSOR     ***/
/*****************************/
#include <ctype.h>
#include <string>
#include <map>
#include <utility>
#include <vector>
#include <iostream>
#include <cstring>  // for strcpy()
#include <fstream>
#define MAX 100
using namespace std;


/********************/
/***     NODE     ***/
/********************/
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

Node::Node()
{
}

Node::~Node()
{ }


/********************/
/***     TREE     ***/
/********************/
class Tree
{
public:
    Tree ();
    map<char*,vector<int> > globalMap;
    void sort(Node *[], int);
    Node *createNode(char[], int);
    void sright(Node *[], int);
 		 void Assign_Code(Node*, int [], int);
	 	 void writeCode(Node*, int [], int, char ch1);
    void printT (Node *p, int moveC);
    void printCodes();
};

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
            cout << "LR" <<"," << p->freq << endl;
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

/********************/
/***     MAIN     ***/
/********************/
int main()
{
    int i, nrLetUsed=0, q=0, u, flag=1, freq[256], huffmCode[256];
    char chars1[2], str[MAX], inChar;
    Node *pTree, *trNode[255];
    Tree treeObj; 
    
	ifstream inFile;
	
	//inFile.open("inputFile1.in");
    inFile.open("test.txt");
	if (!inFile)
	{
		cout<<"Error: File couldn't be open";
		system("pause");
		exit(1);
	} 

	for(i=0; i<=255; i++)
		freq[i]=0;
		
    // Assume LR is first, get newline substitute.
    string line = "";

    int idx=0;
    while (getline(inFile, line)) {
        
        if (line.find("LF") != std::string::npos) {
            freq[(int)'\n']=line.c_str()[3]-'0';
            cout << "LETTER:" << "LF" << "\t" << "occurances:" << line.c_str()[3] << endl;
            
        }

        else{
            char letter;
            string occurances="";
            while (line.c_str()[idx] != '\0') {
                if (idx == 0) {
                    letter = line.c_str()[idx];
                }
                else{
                    occurances += line.c_str()[idx];
                }
                idx++;
            }
            freq[(int) letter] = atoi(occurances.c_str());
            cout << "letter:" << letter << "\t" << "occurances:" << atoi(occurances.c_str()) << endl;;
            idx=0;
        }
        
    }

	for(i=0; i<255; i++)
		if(freq[i]!=0)
			nrLetUsed++;

	cout<<"\nNumber of letters used is:  "<<nrLetUsed<<endl<<endl;

    cout<<"\nThe Frequency of each letter is: "<<endl;
	
   for (i=0; i<nrLetUsed; i++)
    {
		while ((freq[q]==0)&&(q<255))
			q++;
			
		chars1[0]=q;
		chars1[1]=NULL;
        if (chars1[0] == '\n') {
            cout<<"char: "<<"LR"<<", freq: "<<freq[q]<<endl;
        }
        else
            cout<<"char: "<<chars1[0]<<", freq: "<<freq[q]<<endl;
		
        trNode[i] = treeObj.createNode(chars1, freq[q]);
		q++;
    }

    // construct the huffman tree
   while (nrLetUsed > 1)
    {
        treeObj.sort(trNode, nrLetUsed);
        
        u = trNode[0]->freq + trNode[1]->freq;
        
        strcpy(str, trNode[0]->ch);
        strcat(str, trNode[1]->ch);
        
        pTree = treeObj.createNode(str, u);
        
        pTree->right = trNode[1];
        pTree->left = trNode[0];
        trNode[0] = pTree;
        
        treeObj.sright(trNode, nrLetUsed); 
        nrLetUsed--;
    }
    
    // couldn't get this working just write, but it does do some printing
    //treeObj.printT(pTree, 0);

    cout<<"\nThe Huffman Codes are: "<<endl;
    treeObj.Assign_Code(trNode[0], huffmCode, 0);


	ifstream inFile2;
	inFile2.open("inputFile1.in");
	if (!inFile2)
	{
		cout<<"Error: File couldn't be open";
		system("pause");
		exit(1);
	} 
			
	cout<<"\n\nHere is the Huffman Compressed file: \n";
	flag=1;
	while(flag)
	{
		 inFile2>>inChar;
		 if(inChar=='0')
			 flag=0;
		 else
			 treeObj.writeCode(trNode[0], huffmCode, 0, inChar);
	}
	    	    
    cout << endl;
    treeObj.printCodes();


   cout<<endl<<endl;
   system("pause");
}
