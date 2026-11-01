#include <iostream>
using namespace std;

int fibRecursive(int n) {
    if (n <= 1)
        return n;

    return fibRecursive(n - 1) + fibRecursive(n - 2);
}

void fibIterative(int n) {
    int a = 0, b = 1, c;

    for (int i = 0; i < n; i++) {
        cout << a << " ";
        c = a + b;
        a = b;
        b = c;
    }
}

int main() {
    int n;
    cout<<"Enter n : ";
    cin >> n;

    cout << "Recursive Fibonacci: ";
    for (int i = 0; i < n; i++)
        cout << fibRecursive(i) << " ";

    cout << "\nIterative Fibonacci: ";
    fibIterative(n);

    return 0;
}