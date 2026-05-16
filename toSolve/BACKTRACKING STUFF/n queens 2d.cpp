#include <iostream>
#include <vector>
using namespace std;

int solCount = 0;

void printBoard(vector<vector<int>> &board) {
    cout << "SOLUTION FOUND:\n";
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.size(); j++) {
            if (board[i][j] == 1)
                cout<<"Q  ";
            else
                cout<<".  ";
        }
        cout<<"\n";
    }
    cout<<"\n";
}

bool isValid(vector<vector<int>> &board, int row, int col) {
    for (int i = 0; i < board.size(); i++)
        if (board[i][col] == 1) return false;

    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j] == 1) return false;

    for (int i = row, j = col; i >= 0 && j < board.size(); i--, j++)
        if (board[i][j] == 1) return false;

    return true;
}

void solve(vector<vector<int>> &board, int row) {
    if (row == board.size()) {
        solCount++;
        printBoard(board);
    }

    for (int i = 0; i < board.size(); i++) {
        if (isValid(board, row, i)) {
            board[row][i] = 1;
            solve(board, row + 1);
            board[row][i] = 0;
        }
    }
}

int main() {
    int size;
    cout << "Enter the size of the board: ";
    cin>>size;
    vector<vector<int>> board (size, vector<int>(size, 0));
    solve(board, 0);
    cout<<"Number of solutions: " << solCount;
}