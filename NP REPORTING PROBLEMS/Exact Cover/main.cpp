#include <iostream>
using namespace std;

int rows, cols;
int matrix[20][20];
bool colCovered[20] = {false};
int solution[20], solSize = 0;

// Checks if picking this row would "Double Cover" any column
bool isSafe(int r) {
    for (int j = 0; j < cols; j++) {
        if (matrix[r][j] == 1 && colCovered[j]) return false;
    }
    return true;
}

bool solve() {
    // 1. FIND: Find the first uncovered column
    int targetCol = -1;
    for (int j = 0; j < cols; j++) {
        if (!colCovered[j]) {
            targetCol = j;
            break;
        }
    }

    // Base Case: All columns are covered
    if (targetCol == -1) return true;

    // 2. FIT: Try every row that can cover this targetCol
    for (int i = 0; i < rows; i++) {
        if (matrix[i][targetCol] == 1 && isSafe(i)) {
            
            // 3. FILL: Mark all columns covered by this row
            for (int j = 0; j < cols; j++) 
                if (matrix[i][j] == 1) colCovered[j] = true;
            
            solution[solSize++] = i;

            if (solve()) return true;

            // Backtrack
            solSize--;
            for (int j = 0; j < cols; j++) 
                if (matrix[i][j] == 1) colCovered[j] = false;
        }
    }
    return false;
}

int main() {
    cout << "Rows and Cols: "; cin >> rows >> cols;
    cout << "Enter Binary Matrix:\n";
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++) cin >> matrix[i][j];

    if (solve()) {
        cout << "Rows picked for Exact Cover: ";
        for (int i = 0; i < solSize; i++) cout << solution[i] << " ";
    } else cout << "No Exact Cover found.";

    return 0;
}