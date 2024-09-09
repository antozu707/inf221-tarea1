#include <vector>
#include <cassert>

void add(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, std::vector<std::vector<int>>& C) {
    int n = A.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void subtract(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, std::vector<std::vector<int>>& C) {
    int n = A.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

void strassenMultiply(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, std::vector<std::vector<int>>& C) {
    int n = A.size();
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int newSize = n / 2;
    std::vector<std::vector<int>> A11(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> A12(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> A21(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> A22(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> B11(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> B12(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> B21(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> B22(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> M1(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> M2(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> M3(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> M4(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> M5(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> M6(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> M7(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> C11(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> C12(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> C21(newSize, std::vector<int>(newSize));
    std::vector<std::vector<int>> C22(newSize, std::vector<int>(newSize));

    // Submatrices A and B
    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
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

    // Compute M1 to M7
    std::vector<std::vector<int>> temp(newSize, std::vector<int>(newSize));

    add(A11, A22, temp);
    strassenMultiply(temp, B11, M1);

    add(B12, B22, temp);
    strassenMultiply(A11, temp, M2);

    subtract(B21, B11, temp);
    strassenMultiply(A22, temp, M3);

    subtract(B12, B22, temp);
    strassenMultiply(A11, temp, M4);

    add(A21, A22, temp);
    strassenMultiply(temp, B11, M5);

    subtract(A11, A21, temp);
    add(B11, B12, temp);
    strassenMultiply(temp, B22, M6);

    subtract(A12, A22, temp);
    add(B21, B22, temp);
    strassenMultiply(temp, B11, M7);

    // Combine M1 to M7 into C
    add(M1, M4, temp);
    subtract(temp, M5, C11);
    add(C11, M7, C11);

    add(M3, M4, C12);

    add(M5, M6, C21);

    add(M1, M3, temp);
    subtract(temp, M2, C22);

    // Combine C11, C12, C21, C22 into C
    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            C[i][j] = C11[i][j];
            C[i][j + newSize] = C12[i][j];
            C[i + newSize][j] = C21[i][j];
            C[i + newSize][j + newSize] = C22[i][j];
        }
    }
}
