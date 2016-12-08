#include <iostream>
#include <vector>
using namespace std;

int MatrixChainOrder(int p[], int n);

int main(int argc, const char * argv[]) {

    // A1:30x1, A2:1x40, A3:40x10, A4:10x25.
    // Even indices are always shared in this implementation.
    int ls1[] = {30,1,40,10,25};
    int ls2[] = {10,17,12,25,14,30,15,9};
    
    
    int size = sizeof(ls2)/sizeof(ls2[0]);
    
    cout << "Min mults: " << MatrixChainOrder(ls2, size) << endl;
    
    return 0;
}


// Matrix Ai has dimension p[i-1] x p[i] for i = 1..n
int MatrixChainOrder(int p[], int n)
{
    
    /* For simplicity of the program, one extra row and one
     extra column are allocated in m[][].  0th row and 0th
     column of m[][] are not used */
    int m[n][n];
    
    int i, j, k, L, q;
    
    /* m[i,j] = Minimum number of scalar multiplications needed
     to compute the matrix A[i]A[i+1]...A[j] = A[i..j] where
     dimension of A[i] is p[i-1] x p[i] */
    
    // cost is zero when multiplying one matrix.
    for (i=1; i<n; i++)
        m[i][i] = 0;
    
    // L is chain length.
    for (L=2; L<n; L++)
    {
        for (i=1; i<n-L+1; i++)
        {
            j = i+L-1;
            m[i][j] = INT_MAX;
            for (k=i; k<=j-1; k++)
            {
                // q = cost/scalar multiplications
                q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
                if (q < m[i][j])
                    m[i][j] = q;
            }
        }
    }
    
    return m[1][n-1];
}

