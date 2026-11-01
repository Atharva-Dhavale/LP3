Here’s the code explained line by line. It solves the N-Queens puzzle by placing one queen in each row while keeping the first queen at the position you enter.

### Setup and variables

**Line 1**
```cpp
#include <iostream>
```
Includes the C++ input/output tools used by `cin` and `cout`.

**Line 3**
```cpp
using namespace std;
```
Lets the code write `cout` instead of `std::cout`, and `cin` instead of `std::cin`.

**Line 5**
```cpp
int n, a[20][20];
```
Declares:
- `n`: the board size.
- `a`: a 20×20 array representing the board. A cell is `1` when it has a queen and `0` when it is empty. The program limits `n` to 20.

**Line 6**
```cpp
int r, c;
```
Stores the row and column of the fixed first queen.

### Checking whether a square is safe

**Line 8**
```cpp
bool isSafe(int row, int col) {
```
Defines a function that checks whether a queen can be placed at `(row, col)`. It returns `true` if safe and `false` if another queen could attack it.

**Lines 9–12**
```cpp
for (int i = 0; i < n; i++) {
    if (a[row][i] || a[i][col])
        return false;
}
```
Checks the candidate square’s entire row and column. If either already contains a queen, the square is unsafe.

**Lines 14–19**
```cpp
for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
        if (a[i][j] && abs(i - row) == abs(j - col))
            return false;
    }
}
```
Looks through every board square. If a square has a queen and the row distance equals the column distance, the queens share a diagonal, so the candidate square is unsafe.

For example, a queen at `(0, 1)` is diagonal to `(1, 2)`: both row and column differ by 1.

**Lines 21–22**
```cpp
return true;
}
```
If none of the checks found a conflict, the candidate square is safe.

### Searching for a solution

**Line 24**
```cpp
bool solve(int row) {
```
Defines a recursive function that tries to place queens, starting with the given row. It returns whether a complete solution was found.

**Lines 25–26**
```cpp
if (row == n)
    return true;
```
If `row` has reached `n`, all board rows have been handled. A solution is complete.

**Lines 28–29**
```cpp
if (row == r)
    return solve(row + 1);
```
If this is the row containing the fixed queen, skip it: that queen was already placed, so the function moves to the next row.

**Lines 31–40**
```cpp
for (int col = 0; col < n; col++) {
    if (isSafe(row, col)) {
        a[row][col] = 1;

        if (solve(row + 1))
            return true;

        a[row][col] = 0;
    }
}
```
Tries each column in the current row:

1. If the square is safe, place a queen there.
2. Recursively try to solve the next row.
3. If that leads to a solution, return `true`.
4. If it does not, remove the queen (`a[row][col] = 0`) and try another column. This is called **backtracking**.

**Lines 42–43**
```cpp
return false;
}
```
If no column works in this row, report failure so the previous row can try a different position.

### Reading input and printing the board

**Line 45**
```cpp
int main() {
```
The program starts running here.

**Lines 46–47**
```cpp
cout << "Enter board size: ";
cin >> n;
```
Prompts for the board size and reads it.

**Lines 49–52**
```cpp
if (n < 1 || n > 20) {
    cout << "Invalid board size";
    return 0;
}
```
Rejects sizes below 1 or above 20, since the board array is 20×20. `return 0` ends the program.

**Lines 54–55**
```cpp
cout << "Enter first queen position (row and column): ";
cin >> r >> c;
```
Prompts for the fixed queen’s row and column and reads both numbers. For example, `1 2` means row 1, column 2.

**Lines 57–60**
```cpp
if (r < 1 || r > n || c < 1 || c > n) {
    cout << "Invalid position";
    return 0;
}
```
Checks that the entered position is inside the board. The user enters positions starting at 1, so row and column must each be between 1 and `n`.

**Lines 62–63**
```cpp
r--;
c--;
```
Converts the user’s position to the array’s indexing. People count rows and columns from 1; C++ arrays count indexes from 0. So input `1 2` becomes array position `[0][1]`.

**Line 65**
```cpp
a[r][c] = 1;
```
Places the fixed queen on the board.

**Line 67**
```cpp
if (solve(0)) {
```
Starts searching from row index 0. If `solve` finds a complete arrangement, print it.

**Lines 68–74**
```cpp
cout << "Solution:\n";

for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++)
        cout << a[i][j] << " ";
    cout << endl;
}
```
Prints `Solution:` and then each board row. A `1` represents a queen; a `0` represents an empty square.

**Lines 75–77**
```cpp
} else {
    cout << "No solution";
}
```
If the search fails, prints `No solution`.

**Lines 79–80**
```cpp
return 0;
}
```
Ends the program successfully.

For your input, `n = 4` and the first queen is at row 1, column 2. The program keeps that queen in place, then uses `solve` and `isSafe` to find positions for the other three queens.