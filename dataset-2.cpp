#include <vector>
#include <random>
#include <iostream>
#include <ctime>
#include "matrix-1.cpp"
#include "matrix-2.cpp"
#include "strassen.cpp"
#include "strassen2.cpp"

using namespace std;


vector<vector<int>> random(int size, int min = 0, int max = 10) {
    vector<vector<int>> matrix(size, vector<int>(size));
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(min, max);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            matrix[i][j] = dis(gen);
        }
    }
    return matrix;
}

vector<vector<int>> identidad(int size) {
    vector<vector<int>> matrix(size, vector<int>(size, 0));
    for (int i = 0; i < size; ++i) {
        matrix[i][i] = 1;
    }
    return matrix;
}

vector<vector<int>> simetrica(int size, int min = 0, int max = 10) {
    vector<vector<int>> matrix(size, vector<int>(size));
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(min, max);

    for (int i = 0; i < size; ++i) {
        for (int j = i; j < size; ++j) {
            matrix[i][j] = matrix[j][i] = dis(gen);
        }
    }
    return matrix;
}

int main() {
    int size = 128; // Tamaño de las matrices

    // Generar diferentes tipos de matrices
    auto randomMatrixA = random(size);
    auto randomMatrixB = random(size);

    auto identityMatrix = identidad(size);

    auto symmetricMatrix = simetrica(size);

    // Aquí puedes aplicar tus algoritmos de multiplicación
    // Por ejemplo:
    // std::vector<std::vector<int>> result(size, std::vector<int>(size));
    // matrixMultiplyTraditional(randomMatrixA, randomMatrixB, result);
    // strassenMultiply(largeValueMatrix, symmetricMatrix, result);
    // ...

    return 0;
}
