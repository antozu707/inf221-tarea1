#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

void standardSort(std::vector<int>& arr) {
    std::sort(arr.begin(), arr.end());
}

// TEST
int main() {
    vector<int> v = {13, 5, 7, 2, 9};
    standardSort(v);
    for (auto i : v)
        cout << i << " ";
    return 0;
}

