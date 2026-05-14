#include <iostream>
#include <vector>

using namespace std;

// Size of the grid
#define N 9


//Helper to print the grid in a readable format

void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            cout << grid[row][col] << " ";
        }
        cout << endl;
    }
}

//Checks if it's legal to assign num to the given row, col

bool isSafe(int grid[N][N], int row, int col, int num) {
    // 1. Check if 'num' is already in the row
    for (int x = 0; x < N; x++) if (grid[row][x] == num) return false;
    // 2. Check if 'num' is already in the column
    for (int x = 0; x < N; x++) if (grid[x][col] == num) return false;

    // 3. Check if 'num' is in the specific 3x3 box
    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (grid[i + startRow][j + startCol] == num) return false;

    return true;
}

bool solveSudoku(int grid[N][N]) {
    int row = -1, col = -1;
    bool isEmpty = false;

    //1. Find an empty slot
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == 0) {
                //Record row and column if we have found one
                row = i;
                col = j;
                isEmpty = true;
                break;
            }
        }
        //Break outside nested loop
        if (isEmpty) {
            break;
        }
    }
    //If board is no longer empty, we have found a solution
    if (!isEmpty) return true;

    //2. We find a candidate number, test if it is valid, and backtrack if it doesnt work
    for (int i = 1; i <= N; i++) {
        if (isSafe(grid, row, col, i)) {
            grid[row][col] = i;

            if (solveSudoku(grid))
                return true;
            else
                grid[row][col] = 0; //Backtrack
        }
    }
 
    //Board is not solvable
    return false;
}

int main() {
    //Test case
    int grid[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solveSudoku(grid)) {
        printGrid(grid);
    } else {
        cout << "No solution exists" << endl;
    }

    return 0;
}