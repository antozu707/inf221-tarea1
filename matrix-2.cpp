#include <vector>

void matrixMultiplyOptimized(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, std::vector<std::vector<int>>& C) {
    int n = A.size();
    std::vector<std::vector<int>> BT(n, std::vector<int>(n)); // Transponer B

    // Transponer B
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            BT[i][j] = B[j][i];
        }
    }

    // Multiplicación de matrices
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < n; ++k) {
                C[i][j] += A[i][k] * BT[j][k];
            }
        }
    }
}
