// Blake_DataCompression_Decode_Compressed_File.cpp
// Take home final due May 4th
// This program expacts on the code given from class  to  do the following:
        /*
        a) encode a file using huffman compression
        b) build the huffman tree
        c) distribute the codes for each character
        d*) decode the file back to it's origional text given the tree (and finding their codes)
        {Part d) was my contribution}
        */

#include "Tree.h"
#include <map>
#include <utility>

inline bool is_code_in_mapping(map<char*,string> mapper, string curr_code){
    // is the curr_code in mapper somewhere?
    
    for (std::map<char*,string>::iterator it = mapper.begin(); it!= mapper.end(); it++) {
        if (it->second == curr_code) {
            return true;
        }
    }
    return false;
}

inline char* find_key_of_code_in_mapping(map<char*,string> mapper, string curr_code){
    // return the key to the value of the code we just found
    
    for (std::map<char*,string>::iterator it = mapper.begin(); it!= mapper.end(); it++) {
        if (it->second == curr_code) {
            return it->first;
        }
    }
}

////////////  main  /////////////////
int main()
{
    
    /********************************************** Get character freqs **********************************************/
    
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
		
    cout << "All contents from our file.\n";
	while(flag)
	{
			inFile>>inChar;
			if(inChar=='0')
				flag=0;
            else{
                cout << inChar;
				freq[(int)inChar]++;;
            }
    }
    cout << endl;

	for(i=0; i<255; i++)
		if(freq[i]!=0)
			nrLetUsed++;

    /********************************************** Display results from freqs **********************************************/
    
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

    /********************************************** DISPLAY HUFFMAN TREE **********************************************/
    
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

    /********************************************** GET CODES / ENCODE **********************************************/
    
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
    
    /********************************************** BEGIN DECODING **********************************************/

    // Make sure everything is going ok so far
    treeObj.update_to_strings_only();
    treeObj.printMappings();

    // Freshen up with a new line
    cout << endl;
    
    // Open some streams
    ifstream is("outFile1.txt");
    ofstream os("decryptedFile.txt");
    
    // Make some variables
    char c;
    string s="";
    
    // Loop getting single characters, append until found
    while (is.get(c)){
        s+=c;
        if (is_code_in_mapping(treeObj.map_char_freq_as_string, s)) {
            char* key = find_key_of_code_in_mapping(treeObj.map_char_freq_as_string, s);
            cout << "We found the code: " << s << "\nTo have the following key: " <<  key << endl;
            os << key;
            s="";
        }
    }
    is.close();
    os.close();
    

   cout<<endl<<endl;
   system("pause");
}
