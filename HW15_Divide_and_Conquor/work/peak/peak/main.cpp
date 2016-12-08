//
//  main.cpp
//  peak
//
//  Created by Blake Conrad on 11/14/16.
//  Copyright (c) 2016 Blake Conrad. All rights reserved.
//

#include <iostream>
using namespace std;

// Declare function in the pre-processor to later be implemented
int peak(int *, int, int);

// Enter the main function
int main(int argc, const char * argv[]) {
    
    // Instantiate and open a few file object from an absolute path
    FILE *fp;
    fp=fopen("/Users/bmc/Desktop/CSCI-48400/HW15_Divide_and_Conquor/peak/peak/test.txt", "r");
    
    // Dummy variable
    char c;
    
    // Main list to store our file characters
    int ls1[30];
    
    // Max element of our list
    int n=0;
    
    // Get characters line by line and store into ls1
    while((c = fgetc(fp)) != EOF)
    {
        if(c != '\n')
            ls1[n++]=atoi(&c);
    }
    
    // Print the location at which the peak occurs in ls1
    std::cout << ls1[peak(ls1, 0, n)] << std::endl;
    
    return 0;
}

/*
 
 { [],[],[],[middle-1],[middle],[middle+1],[],[],[] }
 

 */
int peak(int L[], int lower, int upper)
{
    // Get the middle location
    int middle = (lower + upper)/2;
    
    // instead of returning in multiple locations, just return found instead.
    int found = 0;
    
    if(middle == 1) // Left-tail Peak
    {
        if (L[1] >= L[2]) {
            found = middle;
        }
    }
    else if (middle == upper) // Right-tail Peak
    {
        if (L[middle] >= L[middle-1]) {
            found = middle;
        }
    }
    else // Middle Peak
    {
        // The correct conditions for a peak are:
            //1. mid > left
            //2. mid > right
        
        // If left > middle, go left until not true
        if(L[middle-1] > L[middle])
            peak(L, lower, middle);
        
        // If right > middle, go right until not true
        else if(L[middle] < L[middle+1])
            peak(L, middle+1, upper);
        
        // We hit this else statement when both if and else if have failed, thus
        // we have a peak.. set found = middle (peak) and return it.
        else
            found = middle;
    }
    return middle;
}
