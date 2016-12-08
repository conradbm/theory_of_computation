      /*******************************************/
     /*     AUTHOR: Blake Conrad                */
    /**     CONTENTS:                         **/
   /***       Huffman Compression Algorith  ***/
  /*******************************************/


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
static ofstream ofs("codetable.txt");

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
    void printCodes();
};

Tree::Tree()
{
}


// Create and return node
Node *Tree::createNode(char chars1[], int freq1)
{
    Node* p;
    p = new Node;
    
    p->freq = freq1;
    strcpy( p->ch , chars1);
    
    p->right = p->left = NULL;
    
    return(p);
}

// Assign huffman encodings
void Tree::Assign_Code(Node* tree, int huffmCode[], int n)
{
    int i;

    // when we hit the leaf we can store that data or print
    if ((tree->left == NULL) && (tree->right == NULL))
    {
        vector<int> temp;
        if (tree->ch[0] == '\n') {
            //cout<<"LR "<<"code: ";
        }
        else
        {
            //cout<<tree->ch<<" code: ";
        }
        
        for (i = 0; i < n; i++)
        {
            //cout<<huffmCode[i];
            temp.push_back(huffmCode[i]);
        }
        //cout<<"\n";
        std::pair<char*,vector<int> > pair (tree->ch,temp);
        Tree::globalMap.insert(pair);
        //cout << "inserted successfully." << endl;
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


// Sort an array of nodes based on the number of letters in the list.
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

// Shift right operation, shifting each node to the right to n-1 to account for removing letters.
void Tree::sright(Node *a[], int n)
{
    int i;
    for (i = 1; i < n - 1; i++)
        a[i] = a[i + 1];
}



// Helper function to print our results.
void Tree::printCodes(){
    

    cout << "+--------------+" << endl;
    cout << "+letter | code +" << endl;
    cout << "+--------------+" << endl;
    ofs << "+---------------+" << endl;
    ofs << "+letter | code +" << endl;
    ofs << "+---------------+" << endl;
    for (std::map<char*,vector<int> >::iterator it = Tree::globalMap.begin();it!=Tree::globalMap.end();++it){
        if (it->first[0] == '\n') {
            cout << "| LF    | ";
            ofs << "| LF    | ";
        }
        else
        {
            cout << "| " << it->first << "     | ";
            ofs << "| " << it->first << "     | ";
        }
        
        for (int i = 0; i < it->second.size(); i++) {
            cout << it->second.at(i);
            ofs << it->second.at(i);
        }
        cout << endl;
        ofs << endl;
    }
    cout << "+---------------+" << endl;
    ofs << "+----------------+" << endl;
}

/********************/
/***     MAIN     ***/
/********************/
int main()
{
    int i, nrLetUsed=0, q=0, u, freq[256], huffmCode[256];
    char chars1[2], str[MAX], inChar;
    Node *pTree, *trNode[255];
    Tree treeObj;
    ifstream inFile;
    string line = "";
    int idx=0;
    
    //inFile.open("inputFile1.in");
    inFile.open("test.txt");
    if (!inFile)
    {
        cout<<"Error: File couldn't be open\n";
    }
    
    for(i=0; i<=255; i++)
        freq[i]=0;
    
    
    while (getline(inFile, line)) {
        
        if (line.find("LF") != std::string::npos) {
            freq[(int)'\n']=line.c_str()[3]-'0';
            //cout << "LETTER:" << "LF" << "\t" << "occurances:" << line.c_str()[3] << endl;
            
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
            //cout << "letter:" << letter << "\t" << "occurances:" << atoi(occurances.c_str()) << endl;;
            idx=0;
        }
        
    }
    
    for(i=0; i<255; i++)
        if(freq[i]!=0)
            nrLetUsed++;
    
    cout << "Character Frequencies: " << endl;
    for (i=0; i<nrLetUsed; i++)
    {
        while ((freq[q]==0)&&(q<255))
            q++;
        chars1[0]=q;
        chars1[1]='\0';
        if (chars1[0] == '\n') {
            cout<<"LR"<<","<<freq[q]<<endl;
        }
        else
            cout<<chars1[0]<<","<<freq[q]<<endl;
        
        trNode[i] = treeObj.createNode(chars1, freq[q]);
        q++;
    }
    
    // construct the huffman tree
    while (nrLetUsed > 1) // for each letter
    {
        // sort the tree for each letter
        treeObj.sort(trNode, nrLetUsed);

        // f(z) = f(x) + f(y)
        u = trNode[0]->freq + trNode[1]->freq;
        
        // always append the first two in the list
        strcpy(str, trNode[0]->ch);
        strcat(str, trNode[1]->ch);
        
        // make a new tree node for those concatenated nodes
        pTree = treeObj.createNode(str, u);
        
        // the greater of the two always get the right pointer
        pTree->right = trNode[1];
        
        // the lesser of the two always gets the left pointer
        pTree->left = trNode[0];
        
        // our newly constructed node gets the first index (overwrites the previous guy there)
        trNode[0] = pTree;
        
        // shift every node to the right because we're about to kill a letter
        treeObj.sright(trNode, nrLetUsed);
        
        // kill a letter
        nrLetUsed--;
    }
    
    cout << endl;

    // Basically just search through the tree and keep track of if we went left or right
    cout<<"Huffman Codes: ";
    treeObj.Assign_Code(trNode[0], huffmCode, 0);
    
    cout << endl;
    treeObj.printCodes();

    
    cout << "Open codetable.txt for further details." << endl;
    cout<<endl<<endl;
    return 0;
}
