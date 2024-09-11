#include <vector>
#include <random>
#include <algorithm>
#include <iostream>
#include <ctime>
#include <chrono>
#include "bubble-sort.cpp"
#include "merge-sort.cpp"
#include "quick-sort.cpp"
#include "sort-function.cpp"


using namespace std;
using namespace std::chrono;

vector<int> random(int size) {
    vector<int> dataset(size);
    mt19937 g(time(0));
    uniform_int_distribution<> dis(0, 1000);

    for (int& num : dataset) {
        num = dis(g);
    }
    return dataset;
}

vector<int> asc(int size) {
    vector<int> dataset(size);
    mt19937 g(time(0));
    uniform_int_distribution<int> dis(0, 1000);
    int r = dis(g); 

    for (int i = 0; i < size; ++i) {
        dataset[i] = r++;
    }
    return dataset;
}


vector<int> desc(int size) {
    vector<int> dataset(size);
    mt19937 g(time(0));
    uniform_int_distribution<int> dis(0, 1000);
    int r = dis(g); 

    for (int i = 0; i < size; ++i) {
        dataset[i] = r - i;
    }
    return dataset;
}

template <typename T>
void benchmark1(const string& algorithm, T funcion, vector<int>& dataset) {
    auto start = high_resolution_clock::now();
    funcion(dataset); 
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << algorithm << " toma " << duration.count() << " microsegundos" << endl;
}



int main() {
    vector<int> random1000 = random(1000);
    vector<int> random10000 = random(10000);
    vector<int> asc1000 = asc(1000);
    vector<int> asc10000 = asc(10000);
    vector<int> desc1000 = desc(1000);
    vector<int> desc10000 = desc(10000);

    printf("Benchmarking para Algoritmos de Ordenamiento\n");
    
    printf("Tamaño de los datasets: 1000\n");
    benchmark1("Bubble Sort Random", bubbleSort, random1000);
    benchmark1("Bubble Sort Asc", bubbleSort, asc1000);
    benchmark1("Bubble Sort Desc", bubbleSort, desc1000);
    benchmark1("Merge Sort Random", [](vector<int>& data) { mergeSort(data, 0, data.size() - 1); }, random1000);
    benchmark1("Merge Sort Asc", [](vector<int>& data) { mergeSort(data, 0, data.size() - 1); }, asc1000);
    benchmark1("Merge Sort Desc", [](vector<int>& data) { mergeSort(data, 0, data.size() - 1); }, desc1000);
    benchmark1("Quick Sort Random", [](vector<int>& data) { quickSort(data, 0, data.size() - 1); }, random1000);
    benchmark1("Quick Sort Asc", [](vector<int>& data) { quickSort(data, 0, data.size() - 1); }, asc1000);
    benchmark1("Quick Sort Desc", [](vector<int>& data) { quickSort(data, 0, data.size() - 1); }, desc1000);
    benchmark1("Sort Function Random", standardSort, random1000);
    benchmark1("Sort Function Asc", standardSort, asc1000);
    benchmark1("Sort Function Desc", standardSort, desc1000);

    printf("Tamaño de los datasets: 10000\n");
    benchmark1("Bubble Sort Random", bubbleSort, random10000);
    benchmark1("Bubble Sort Asc", bubbleSort, asc10000);
    benchmark1("Bubble Sort Desc", bubbleSort, desc10000);
    benchmark1("Merge Sort Random", [](vector<int>& data) { mergeSort(data, 0, data.size() - 1); }, random10000);
    benchmark1("Merge Sort Asc", [](vector<int>& data) { mergeSort(data, 0, data.size() - 1); }, asc10000);
    benchmark1("Merge Sort Desc", [](vector<int>& data) { mergeSort(data, 0, data.size() - 1); }, desc10000);
    benchmark1("Quick Sort Random", [](vector<int>& data) { quickSort(data, 0, data.size() - 1); }, random10000);
    benchmark1("Quick Sort Asc", [](vector<int>& data) { quickSort(data, 0, data.size() - 1); }, asc10000);
    benchmark1("Quick Sort Desc", [](vector<int>& data) { quickSort(data, 0, data.size() - 1); }, desc10000);
    benchmark1("Sort Function Random", standardSort, random10000);
    benchmark1("Sort Function Asc", standardSort, asc10000);
    benchmark1("Sort Function Desc", standardSort, desc10000);
    
    return 0;
}
