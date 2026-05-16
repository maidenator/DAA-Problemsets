#include <iostream>
using namespace std;

int n, solCount = 0;
int board[20]; // board[row] = column_index

void printBoard() {
    cout<<"Solution found:\n";
    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            cout<<(board[r] == c ? "Q " : ". ");
        }
        cout<<"\n";
    }
    cout<<"\n";
}

bool isSafe(int r, int c) {
    for (int i = 0; i < r; i++) {
        // Check column and diagonals
        if (board[i] == c || abs(i - r) == abs(board[i] - c))
            return false;
    }
    return true;
}

void solve(int r) {
    if (r == n) {
        printBoard();
        solCount++;
        return;
    }
    for (int c = 0; c < n; c++) {
        if (isSafe(r, c)) {
            board[r] = c;     // Place
            solve(r + 1);     // Recurse
            board[r] = -1;    // Backtrack (Optional with 1D)
        }
    }
}

int main() {
    cout << "Enter size: "; cin >> n;
    solve(0);
    cout << "Solutions: " << solCount;
    return 0;
}