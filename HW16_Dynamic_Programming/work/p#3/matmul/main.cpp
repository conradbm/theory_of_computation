//
//  main.cpp
//  matmul
//
//  Created by Blake Conrad on 11/23/16.
//  Copyright (c) 2016 Blake Conrad. All rights reserved.
//

#include <iostream>
#include <vector>
using namespace std;

int find_min_matmul(int**&,int**&,vector<int>,int);
void opt_parens(int* INDEX_TABLE[], int, int);
void print_matrix(int *matrix[], int n);
void printls(vector<int>);
int main(int argc, const char * argv[]) {

    // A1:30x1, A2:1x40, A3:40x10, A4:10x25.
    // Even indices are always shared in this implementation.
    //vector<int> A({30,1,40,10,25});
    vector<int> A({10,17,12,25,14,30,15,9});
    int N = A.size();
    int **M, **INDEX_TABLE;
    
    printls(A);
    cout << "Minimum multiplications: " << find_min_matmul(M,INDEX_TABLE,A,N) << endl;
    cout << "Optimal ordering:";
    opt_parens(INDEX_TABLE, 1, N-1);
    cout << "\n\nContents of Matrix M(i,j):\n";
    print_matrix(M, N);
    
    //cout << "\n\nContents of Matrix INDEX_TABLE:\n";
    //print_matrix(INDEX_TABLE, N);
    
    
    return 0;
}

void printls(vector<int> ls1)
{
    int counter=0;
    for (int i = 1; i < ls1.size(); i++) {
        cout << "A" << i << ": ";
        cout << ls1[i-1] << "x" << ls1[i] << endl;
    }
}

void print_matrix(int* matrix[], int n)
{
    for (int i = 0; i< n; i++) {
        for (int j = 0; j < n; j++) {
            if (i!=0) {
                if(j!=0)
                {
                    cout << matrix[i][j] << " ";
                }
                
            }
            
        }
        cout << endl;
    }
}

void opt_parens(int* INDEX_TABLE[], int start, int finish)
{

    if (start == finish) {
        cout << "A" << start << " ";
    }
    else{
        cout << "(";
        opt_parens(INDEX_TABLE, start, INDEX_TABLE[start][finish]);
        opt_parens(INDEX_TABLE, INDEX_TABLE[start][finish]+1, finish);
        cout << ")";
    }
}
int find_min_matmul(int** &M, int** &INDEX_TABLE, vector<int> A, int N)
{
    // Setup arrays
    int j,tmp;
    M = new int*[N];
    INDEX_TABLE = new int*[N];
    for (int i =0; i < N; i++) {
        INDEX_TABLE[i] = new int[N];
        M[i] = new int[N];
    }
    
    // Set the main diagonal to 0's
    for (int i = 0; i < N; i++) {
        M[i][i]=0;
    }
    
    
    for (int d = 1; d < N-1; d++) {             /* For each diagonal. */
        for (int i = 0; i < N - d; i++) {       /* For each square in that diagonal. */
            j = i+d;
            M[i][j]=999999;
            for (int k = i; k < j; k++) {       /* For each updated value around that square, find and update the min value. */
                int tmp_cost = M[i][k] + M[k+1][j] + A[i-1]*A[k]*A[j];
                if (tmp_cost < M[i][j]) {
                    M[i][j] = tmp_cost;
                    INDEX_TABLE[i][j] = k;      /* Store our optimal index. */
                    //cout << "Updating (" << i << "," << j << ") to: " << M[i][j] << endl;
                }
            }
        }
    }
    
    return M[1][N-1];
}
