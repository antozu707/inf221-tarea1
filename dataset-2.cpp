#include <vector>
#include <random>
#include <iostream>
#include <ctime>
#include <chrono>
#include "matrix-1.cpp"
#include "matrix-2.cpp"
#include "strassen.cpp"


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
    cout << algorithm << " toma " << duration << " microsegundos" << endl;
}

template <typename T>
void benchmarkStrassen(const string& algorithm, T funcion, vector<vector<int>>& A, vector<vector<int>>& B) {
    auto start = high_resolution_clock::now();
    vector<vector<int>> C = funcion(A, B);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    cout << algorithm << " toma " << duration.count() << " microsegundos" << endl;

}

int main(){

    vector<vector<int>> A1 = random(256);
    vector<vector<int>> B1 = random(256);
    vector<vector<int>> C1(256, vector<int>(256));

    printf("Benchmarking para Multiplicación de Matrices\n");
    printf("Tamaño de la matriz: 256\n");
    benchmark2("Multiplicación tradicional", mmt, A1, B1, C1);
    benchmark2("Multiplicación tradicional optimizada", mmo, A1, B1, C1);
    benchmarkStrassen("Strassen", [](const vector<vector<int>>& A, const vector<vector<int>>& B) {
        return strassen(A, B); 
    }, A1, B1);

    vector<vector<int>> A2 = random(1024);
    vector<vector<int>> B2 = random(1024);
    vector<vector<int>> C2(1024, vector<int>(1024));

    printf("Tamaño de la matriz: 1024\n");
    benchmark2("Multiplicación tradicional", mmt, A2, B2, C2);
    benchmark2("Multiplicación tradicional optimizada", mmo, A2, B2, C2);
    benchmarkStrassen("Strassen", [](const vector<vector<int>>& A, const vector<vector<int>>& B) {
        return strassen(A, B);  
    }, A2, B2);


    vector<vector<int>> A3 = random(2048);
    vector<vector<int>> B3 = random(2048);
    vector<vector<int>> C3(2048, vector<int>(2048));

    printf("Tamaño de la matriz: 2048\n");
    benchmark2("Multiplicación tradicional", mmt, A3, B3, C3);
    benchmark2("Multiplicación tradicional optimizada", mmo, A3, B3, C3);
    benchmarkStrassen("Strassen", [](const vector<vector<int>>& A, const vector<vector<int>>& B) {
        return strassen(A, B); 
    }, A3, B3);

    return 0;
}
