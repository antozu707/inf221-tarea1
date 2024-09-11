#include <vector>
#include <random>
#include <iostream>
#include <ctime>
#include <chrono>
#include "matrix-1.cpp"
#include "matrix-2.cpp"
#include "strassen.cpp"
#include "strassen3.cpp"

using namespace std;
using namespace std::chrono;

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


template <typename M>
void benchmark2(const string& algorithm, M funcion, const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C) {
    auto start = high_resolution_clock::now();
    funcion(A, B, C);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start).count();
    cout << algorithm << " toma " << duration << " microsegundos en multiplicar matrices de tamaño " << A.size() << "x" << A.size() << endl;
}

template <typename T>
void benchmarkStrassen(const string& algorithm, T funcion, vector<vector<int>>& A, vector<vector<int>>& B) {
    auto start = high_resolution_clock::now();
    vector<vector<int>> C = funcion(A, B); // Ejecuta la función Strassen
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    cout << algorithm << " toma " << duration.count() << " microsegundos" << endl;

    // Opcional: imprime resultado para depurar
    // printMatrix(C);
}

int main(){

    vector<vector<int>> A = random(1024);
    vector<vector<int>> B = random(1024);
    vector<vector<int>> C(16, vector<int>(16));

    benchmark2("Multiplicación tradicional", mmt, A, B, C);
    benchmark2("Multiplicación tradicional optimizada", mmo, A, B, C);
    //benchmark2("Strassen", strassen(A,B), A, B, C);
    //benchmark2("Strassen", [](vector<vector<int>>& data) { strassen(A, B); }, A, B, C);

    // Aquí puedes aplicar tus algoritmos de multiplicación
    // Por ejemplo:
    // std::vector<std::vector<int>> result(size, std::vector<int>(size));
    // matrixMultiplyTraditional(randomMatrixA, randomMatrixB, result);
    // strassenMultiply(largeValueMatrix, symmetricMatrix, result);
    // ...

    return 0;
}
