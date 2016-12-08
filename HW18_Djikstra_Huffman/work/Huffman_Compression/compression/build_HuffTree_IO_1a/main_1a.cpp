// build_HuffmanTree_1a.cpp

#include "Tree.h"

////////////  main  /////////////////
int main()
{
    int i, nrLetUsed=0, q=0, u, flag=1, freq[256];
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
		
    /******************************************/
    /****** Increment Asci Index of char ******/
    /******************************************/
	while(flag)
	{
			inFile>>inChar;
			if(inChar=='0')
				flag=0;
			else
                // Increment the index of the asci characters location by 1
				freq[(int)inChar]++;
	}

    /****************************************/
    /****** Get Number of Letters Used ******/
    /****************************************/
	for(i=0; i<255; i++)
		if(freq[i]!=0)
			nrLetUsed++;

	cout<<"\nNr of letters used is:  "<<nrLetUsed<<endl;

    cout<<"\nThe Frequency of each letter is: "<<endl;
	
    /*****************************************************/
    /****** Get Frequency of each letters ocurrence ******/
    /*****************************************************/
   for (i=0; i<nrLetUsed; i++)//each letter
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
	    
   cout<<endl<<endl;
   system("pause");
}
