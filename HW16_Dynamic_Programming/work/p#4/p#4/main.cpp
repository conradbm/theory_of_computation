//
//  main.cpp
//  p#4
//
//  Created by Blake Conrad on 11/25/16.
//  Copyright (c) 2016 Blake Conrad. All rights reserved.
//

#include <iostream>
using namespace std;

int predecessor(int*, int*, int);
void printls(int*, int);

int main(int argc, const char * argv[]) {
    
    //int L[] = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
    int L[] = {6,2,9,6,5,8,12,15,7};
    int n = sizeof(L)/sizeof(int);
    int T[n];
    T[0]=1;
    
    for (int i = 1; i <= n; i++) {
        T[i] = predecessor(T,L, i) + 1;
    }
    
    printls(L, n);
    printls(T, n);
    
    cout << endl;
    return 0;
}

void printls(int *LIST, int size)
{
    for (int i = 0; i < size; i++) {
        cout << LIST[i] << " ";
    }
    cout << endl;
}

int predecessor(int *T, int *L, int k)
{
    int t=0;
    for (int i = k-1; i >= 0; i--) {
        if (L[k] > L[i]) {
            if (T[i] > t) {
                t=T[i];
            }
        }
    }
    return t;
}