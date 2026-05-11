#include <iostream>
#include <vector>
using namespace std;

//Global counter for solutions
int count = 0;

void printBoard(vector<vector<int>> &board) {
    cout << "SOLUTION FOUND:\n";
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.size(); j++) {
            cout << board[i][j]<<"  ";
        }
        cout<<"\n";
    }
    cout<<"\n";
}

bool checkQueenPlacement(vector<vector<int>> &board, int row, int col) {
    for (int i = 0; i < row; i++)
        if (board[i][col] == 1) return false;

    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j] == 1 ) return false;

    for (int i = row, j = col; i >= 0 && j < board.size(); i--, j++)
        if (board[i][j] == 1 ) return false;

    return true;
}

void solve(vector<vector<int>> &board, int row) {
    if (row == board.size()) {
        //If problem asks just for 1 solution change solve to a bool and return true here xd
        count++;
        printBoard(board);
    }
    for (int i = 0; i < board.size(); i++) {
        if (checkQueenPlacement(board, row, i)) {
            board[row][i] = 1; //Place queen
            solve(board, row + 1);
            board[row][i] = 0; //Backtrack
        }
    }
}

int main() {
    int size;
    cout << "Enter size of board: ";
    cin >> size;
    vector<vector<int>> board(size, vector<int>(size, 0));
    solve(board, 0);
    cout << "Solutions found " << count;
}
