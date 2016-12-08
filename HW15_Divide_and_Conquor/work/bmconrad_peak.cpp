//
// peak.cpp
//
//  Created by Blake Conrad on 11/14/16.
//  Copyright (c) 2016 Blake Conrad. All rights reserved.
//
// This program is intended to display the divide and conquor techniques
// learned in class applied toward the peak algorithm.
//

// Preprocessor
#include "stdafx.h"
#include "stdlib.h"
#include <iostream>
#include <fstream>
#include <string>

#define MAX_ELEMENTS 30
using namespace std;

int peak(int *, int, int);
void printList(int *, int);

int main(int argc, const char * argv[]) {

	// Declarations
	int n = 0;
	int ls1[MAX_ELEMENTS];
	string line = "";
	ifstream myfile("peak.txt");
	
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			ls1[n++] = stoi(line);
		}
		myfile.close();
	}

	printList(ls1, n);
	std::cout << "Found a peak at: " << ls1[peak(ls1, 0, n)] << std::endl;
	
	return EXIT_SUCCESS;
}

// Confirm the list entered successfully from the file IO
void printList(int *ls1,int n)
{
	cout << "Input list from file:" << endl;
	for (int i = 0; i < n; i++)
	{
		cout << ls1[i] << "\t";
	}
	cout << endl;
}

// Return the index of a 'peak' in a list of integers
int peak(int L[], int lower, int upper)
{
	// Return variable used instead of multiple returns.
	int found = 0;

	// Get our midpoint.
	int middle = (lower + upper) / 2;
	
	// Left tail array situation, examine the 2 leftmost indices.
	if (middle == 1)
	{
		if (L[1] >= L[2]) {
			found = middle;
		}
	}

	// Right tail array situation, examine the 2 rightmost indices.
	else if (middle == upper)
	{
		if (L[middle] >= L[middle - 1]) {
			found = middle;
		}
	}

	// Middle array situation,

	else
	{
		// Look left, if he's greater, then recurse in that direction.
		if (L[middle - 1] > L[middle])
			peak(L, lower, middle);

		// Look right, if he's greater, then recurse in that direction.
		else if (L[middle] < L[middle + 1])
			peak(L, middle + 1, upper);

		// If both left, and right checks fail, we have an index that is both..
		// .. greater than it's left and right, i.e,.. a peak;
		else
			found = middle;
	}
	return middle;
}
