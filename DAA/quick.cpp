#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

int partition(vector<int>& a, int low, int high) {
    int pivot = a[high];
    int i = low - 1;

    for (int j = low; j < high; j++){
        if (a[j] < pivot){
            i++;
            swap(a[i], a[j]);
        }
    }

    swap(a[i + 1], a[high]);
    return i + 1;
}

void deterministicQuickSort(vector<int>& a, int low, int high) {
    if (low < high) {
        int p = partition(a, low, high);
        deterministicQuickSort(a, low, p - 1);
        deterministicQuickSort(a, p + 1, high);
    }
}

void randomizedQuickSort(vector<int>& a, int low, int high) {
    if (low < high) {
        int r = low + rand() % (high - low + 1);
        swap(a[r], a[high]);

        int p = partition(a, low, high);

        randomizedQuickSort(a, low, p - 1);
        randomizedQuickSort(a, p + 1, high);
    }
}

int main() {

    vector<int> a = {8, 3, 1, 7, 0, 10, 2};
    vector<int> b = a;

    deterministicQuickSort(a, 0, a.size() - 1);
    randomizedQuickSort(b, 0, b.size() - 1);

    cout << "Deterministic Quick Sort: ";
    for (int x : a) cout << x << " ";

    cout << "\nRandomized Quick Sort: ";
    for (int x : b) cout << x << " ";

    return 0;
}
