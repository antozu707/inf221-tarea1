// Código proporcionado por: https://www.geeksforgeeks.org/strassens-matrix-multiplication-algorithm-implementation/
// Posee una modificación en el tipo de dato de las matrices de entrada y salida, de lld** a vector<vector<int>>.

#include <iostream>
#include <vector>

using namespace std;

// Helper function to add two matrices
vector<vector<int>> add(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    return C;
}

// Helper function to subtract two matrices
vector<vector<int>> subtract(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
    return C;
}

// Standard matrix multiplication
vector<vector<int>> multiply(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    vector<vector<int>> C(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return C;
}

// Strassen's algorithm for matrix multiplication
vector<vector<int>> strassen(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int n = A.size();
    
    if (n == 1) {
        // Base case: 1x1 matrix multiplication
        return {{A[0][0] * B[0][0]}};
    }
    
    // Divide matrices into 4 submatrices of size n/2 x n/2
    int newSize = n / 2;
    vector<vector<int>> A11(newSize, vector<int>(newSize)), A12(newSize, vector<int>(newSize)),
                        A21(newSize, vector<int>(newSize)), A22(newSize, vector<int>(newSize));
    vector<vector<int>> B11(newSize, vector<int>(newSize)), B12(newSize, vector<int>(newSize)),
                        B21(newSize, vector<int>(newSize)), B22(newSize, vector<int>(newSize));
    
    // Filling the submatrices
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + newSize];
            A21[i][j] = A[i + newSize][j];
            A22[i][j] = A[i + newSize][j + newSize];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + newSize];
            B21[i][j] = B[i + newSize][j];
            B22[i][j] = B[i + newSize][j + newSize];
        }
    }

    // Compute the 7 products (recursively)
    vector<vector<int>> P1 = strassen(add(A11, A22), add(B11, B22));       // P1 = (A11 + A22) * (B11 + B22)
    vector<vector<int>> P2 = strassen(add(A21, A22), B11);                 // P2 = (A21 + A22) * B11
    vector<vector<int>> P3 = strassen(A11, subtract(B12, B22));            // P3 = A11 * (B12 - B22)
    vector<vector<int>> P4 = strassen(A22, subtract(B21, B11));            // P4 = A22 * (B21 - B11)
    vector<vector<int>> P5 = strassen(add(A11, A12), B22);                 // P5 = (A11 + A12) * B22
    vector<vector<int>> P6 = strassen(subtract(A21, A11), add(B11, B12));  // P6 = (A21 - A11) * (B11 + B12)
    vector<vector<int>> P7 = strassen(subtract(A12, A22), add(B21, B22));  // P7 = (A12 - A22) * (B21 + B22)

    // Combine the results into the resulting matrix C
    vector<vector<int>> C(n, vector<int>(n));
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize; j++) {
            C[i][j] = P1[i][j] + P4[i][j] - P5[i][j] + P7[i][j];
            C[i][j + newSize] = P3[i][j] + P5[i][j];
            C[i + newSize][j] = P2[i][j] + P4[i][j];
            C[i + newSize][j + newSize] = P1[i][j] - P2[i][j] + P3[i][j] + P6[i][j];
        }
    }

    return C;
}
/*
int main() {
    // Test case
    vector<vector<int>> A = {{1, 2}, {5, 6}};
    vector<vector<int>> B = {{7, 8}, {9, 10}};
    
    vector<vector<int>> C = strassen(A, B);
    
    // Print result
    for (const auto& row : C) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
    
    return 0;
}*/
