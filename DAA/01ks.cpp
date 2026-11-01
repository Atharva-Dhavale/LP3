// #include <iostream>
// #include <vector>
// using namespace std;

// // 1. Recursive
// int recursive(int i, int W, vector<int>& wt, vector<int>& val) {
//     if (i == 0 || W == 0)
//         return 0;

//     if (wt[i - 1] <= W)
//         return max(val[i - 1] + recursive(i - 1, W - wt[i - 1], wt, val),
//                    recursive(i - 1, W, wt, val));

//     return recursive(i - 1, W, wt, val);
// }

// // 2. Memoization
// int memoization(int i, int W, vector<int>& wt, vector<int>& val,
//                 vector<vector<int>>& dp) {
//     if (i == 0 || W == 0)
//         return 0;

//     if (dp[i][W] != -1)
//         return dp[i][W];

//     if (wt[i - 1] <= W)
//         return dp[i][W] = max(val[i - 1] + memoization(i - 1, W - wt[i - 1], wt, val, dp),
//                               memoization(i - 1, W, wt, val, dp));

//     return dp[i][W] = memoization(i - 1, W, wt, val, dp);
// }

// // 3. Tabulation
// int tabulation(int n, int W, vector<int>& wt, vector<int>& val) {
//     vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

//     for (int i = 1; i <= n; i++) {
//         for (int w = 1; w <= W; w++) {
//             if (wt[i - 1] <= w)
//                 dp[i][w] = max(val[i - 1] + dp[i - 1][w - wt[i - 1]],
//                                dp[i - 1][w]);
//             else
//                 dp[i][w] = dp[i - 1][w];
//         }
//     }

//     return dp[n][W];
// }

// // 4. Space Optimization
// int optimized(int n, int W, vector<int>& wt, vector<int>& val) {
//     vector<int> dp(W + 1, 0);

//     for (int i = 0; i < n; i++) {
//         for (int w = W; w >= wt[i]; w--) {
//             dp[w] = max(dp[w], val[i] + dp[w - wt[i]]);
//         }
//     }

//     return dp[W];
// }

// int main() {
//     int n, W;
//     cin >> n >> W;

//     vector<int> wt(n), val(n);

//     for (int i = 0; i < n; i++)
//         cin >> wt[i] >> val[i];

//     vector<vector<int>> dp(n + 1, vector<int>(W + 1, -1));

//     cout << "Recursive: " << recursive(n, W, wt, val) << endl;
//     cout << "Memoization: " << memoization(n, W, wt, val, dp) << endl;
//     cout << "Tabulation: " << tabulation(n, W, wt, val) << endl;
//     cout << "Optimized: " << optimized(n, W, wt, val) << endl;

//     return 0;
// }




#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int recursive(int i, int W, vector<int>& wt, vector<int>& val) {
    if (i == 0 || W == 0)
        return 0;

    if (wt[i - 1] <= W)
        return max(val[i - 1] + recursive(i - 1, W - wt[i - 1], wt, val),
                   recursive(i - 1, W, wt, val));

    return recursive(i - 1, W, wt, val);
}

int memoization(int i, int W, vector<int>& wt, vector<int>& val,
                vector<vector<int>>& dp) {
    if (i == 0 || W == 0)
        return 0;

    if (dp[i][W] != -1)
        return dp[i][W];

    if (wt[i - 1] <= W)
        return dp[i][W] = max(
            val[i - 1] + memoization(i - 1, W - wt[i - 1], wt, val, dp),
            memoization(i - 1, W, wt, val, dp)
        );

    return dp[i][W] = memoization(i - 1, W, wt, val, dp);
}

int tabulation(int n, int W, vector<int>& wt, vector<int>& val) {
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= W; w++) {
            if (wt[i - 1] <= w)
                dp[i][w] = max(
                    val[i - 1] + dp[i - 1][w - wt[i - 1]],
                    dp[i - 1][w]
                );
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    return dp[n][W];
}

int optimized(int n, int W, vector<int>& wt, vector<int>& val) {
    vector<int> dp(W + 1, 0);

    for (int i = 0; i < n; i++) {
        for (int w = W; w >= wt[i]; w--) {
            dp[w] = max(dp[w], val[i] + dp[w - wt[i]]);
        }
    }

    return dp[W];
}

int main() {
    int n, W;

    cout << "Enter number of items: ";
    cin >> n;

    cout << "Enter knapsack capacity: ";
    cin >> W;

    vector<int> wt(n), val(n);

    cout << "Enter weight and value of each item:\n";

    for (int i = 0; i < n; i++) {
        cout << "Item " << i + 1 << ": ";
        cin >> wt[i] >> val[i];
    }

    vector<vector<int>> dp(n + 1, vector<int>(W + 1, -1));

    cout << "\nMaximum value using different approaches:\n";

    cout << "Recursive: " << recursive(n, W, wt, val) << endl;
    cout << "Memoization: " << memoization(n, W, wt, val, dp) << endl;
    cout << "Tabulation: " << tabulation(n, W, wt, val) << endl;
    cout << "Space Optimization: " << optimized(n, W, wt, val) << endl;

    return 0;
}




// Enter number of items: 3
// Enter knapsack capacity: 5
// Enter weight and value of each item:
// Item 1: 2 10
// Item 2: 3 20
// Item 3: 4 30

// Enter number of items: 4
// Enter knapsack capacity: 7
// Enter weight and value of each item:
// Item 1: 1 1
// Item 2: 3 4
// Item 3: 4 5
// Item 4: 5 7