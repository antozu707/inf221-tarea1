#include <vector>
#include <random>
#include <algorithm>
#include <iostream>
#include <ctime>

using namespace std;

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

// Genera un vector parcialmente ordenado
vector<int> asc_parcial(int size, float sortedRatio = 0.5) {
    int sortedSize = static_cast<int>(size * sortedRatio);
    vector<int> dataset = asc(sortedSize);
    vector<int> randomPart = random(size - sortedSize);
    dataset.insert(dataset.end(), randomPart.begin(), randomPart.end());
    return dataset;
}

// Genera un vector con valores duplicados
vector<int> dup(int size, int numDuplicates = 100) {
    vector<int> dataset = random(size - numDuplicates);
    for (int i = 0; i < numDuplicates; ++i) {
        dataset.push_back(42); // Valor duplicado arbitrario
    }
    shuffle(dataset.begin(), dataset.end(), mt19937{random_device{}()});
    return dataset;
}

int main() {
    vector<int> dataset = asc_parcial(10);
    for (auto i : dataset) {
        cout << i << " ";
    }
    return 0;
}
