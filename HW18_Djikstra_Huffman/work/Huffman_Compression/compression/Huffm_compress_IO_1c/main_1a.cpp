// Huffman_compress_IO_1c.cpp
// in this version we output the Huffman compressed file

#include "Tree.h"
#include <map>

////////////  main  /////////////////
int main()
{
    int i, nrLetUsed=0, q=0, u, flag=1, freq[256], huffmCode[15];
    char chars1[2], str[MAX], inChar;
    Node *pTree, *trNode[255];
    Tree treeObj; 
    
	ifstream inFile;
	
	inFile.open("inputFile1.in");
	if (!inFile)
	{
		cout<<"Error: File couldn't be open";
		system("pause");
		exit(1);
	} 

	for(i=0; i<=255; i++)
		freq[i]=0;
		
	while(flag)
	{
			inFile>>inChar;
			if(inChar=='0')
				flag=0;
			else
				freq[(int)inChar]++;;
	}


	for(i=0; i<255; i++)
		if(freq[i]!=0)
			nrLetUsed++;

	cout<<"\nNr of letters used is:  "<<nrLetUsed<<endl<<endl;

    cout<<"\nThe Frequency of each letter is: "<<endl;
	
   for (i=0; i<nrLetUsed; i++)
    {
		while ((freq[q]==0)&&(q<255))
			q++;
			
		chars1[0]=q;
		chars1[1]=NULL;
		cout<<"char: "<<chars1[0]<<", freq: "<<freq[q]<<endl;
		
        trNode[i] = treeObj.createNode(chars1, freq[q]);
		q++;
    }

    cout<<"\nThe Huffman Tree is: "<<endl<<endl;

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
    
    treeObj.printT(pTree, 0);

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
    
    
    // Decode a file given by the previous tree
    
    ifstream decodeFile;
    decodeFile.open("outFile1.txt");
    cout << endl;
    for (std::map<char*,int*>::iterator it = treeObj.globalMap.begin();
         it!=treeObj.globalMap.end();
         ++it){
        cout << it->first << "->";
        for (int i = 0; i < sizeof(it->second)/sizeof(int); i++) {
            cout << it->second[i];
        }
    }

   cout<<endl<<endl;
   system("pause");
}
