#include <iostream>

using namespace std;

int n, a[20][20];
int r, c;

bool isSafe(int row, int col) {
    for (int i = 0; i < n; i++) {
        if (a[row][i] || a[i][col])
            return false;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j] && abs(i - row) == abs(j - col))
                return false;
        }
    }

    return true;
}

bool solve(int row) {
    if (row == n)
        return true;

    if (row == r)
        return solve(row + 1);

    for (int col = 0; col < n; col++) {
        if (isSafe(row, col)) {
            a[row][col] = 1;

            if (solve(row + 1))
                return true;

            a[row][col] = 0;
        }
    }

    return false;
}

int main() {
    cout << "Enter board size: ";
    cin >> n;

    if (n < 1 || n > 20) {
        cout << "Invalid board size";
        return 0;
    }

    cout << "Enter first queen position (row and column): ";
    cin >> r >> c;

    if (r < 1 || r > n || c < 1 || c > n) {
        cout << "Invalid position";
        return 0;
    }

    r--;
    c--;

    a[r][c] = 1;

    if (solve(0)) {
        cout << "Solution:\n";

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                cout << a[i][j] << " ";
            cout << endl;
        }
    } else {
        cout << "No solution";
    }

    return 0;
}