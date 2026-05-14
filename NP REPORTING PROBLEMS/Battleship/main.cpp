#include <iostream>
using namespace std;

int n, k, totalSolutions = 0;
int board[20][20] = {0};

bool isSafe(int r, int c) {
    // Check all 8 surrounding neighbors
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int nr = r + i;
            int nc = c + j;
            // If neighbor is within bounds and has a ship
            if (nr >= 0 && nr < n && nc >= 0 && nc < n) {
                if (board[nr][nc] == 1) return false;
            }
        }
    }
    return true;
}

void solve(int count, int r, int c) {
    if (count == k) {
        totalSolutions++;
        return;
    }

    // Traverse the board cell by cell
    for (int i = r; i < n; i++) {
        // Start from 'c' only for the current row to avoid redundant combinations
        for (int j = (i == r ? c : 0); j < n; j++) {
            if (isSafe(i, j)) {
                board[i][j] = 1;
                // Move to the next cell (j + 1)
                solve(count + 1, i, j + 1);
                board[i][j] = 0; // Backtrack
            }
        }
    }
}

int main() {
    cout << "Board Size (N) and Ships (K): ";
    cin >> n >> k;

    // Start solving from 0 ships at position (0,0)
    solve(0, 0, 0);

    cout << "Total Solutions: " << totalSolutions << endl;
    return 0;
}