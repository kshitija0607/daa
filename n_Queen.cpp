#include <iostream>
#include <vector>
using namespace std;

// Function to check if placing a queen at board[row][col] is safe
bool isSafe(vector<vector<int>>& board, int row, int col, int N) {
    // Check the column
    for (int i = 0; i < row; i++)
        if (board[i][col])
            return false;

    // Check the upper left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    // Check the upper right diagonal
    for (int i = row, j = col; i >= 0 && j < N; i--, j++)
        if (board[i][j])
            return false;

    return true;
}

void printSolution(const vector<vector<int>>& board, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j])
                cout << " Q" << i+1 ;
            else
                cout << " 0 ";
        }
        cout << endl;
    }
    cout << endl;
}

// Backtracking function 
bool solveNQueens(vector<vector<int>>& board, int row, int N) {
    // If all queens are placed, return true
    if (row == N) {
        printSolution(board, N);
        return true;
    }

    bool success = false;

    // Try placing a queen in each column for the current row
    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col, N)) {
            // Place the queen at board[row][col]
            board[row][col] = 1;

            // Recur to place the rest of the queens
            success = solveNQueens(board, row + 1, N) || success;

            // Backtrack by removing the queen from board[row][col]
            board[row][col] = 0;
        }
    }

    return success;
}

int main() {
    int N;

    cout << "Enter the number of queens (N): ";
    cin >> N;

    vector<vector<int>> board(N, vector<int>(N, 0));

    if (!solveNQueens(board, 0, N)) {
        cout << "No solution exists for " << N << " queens." << endl;
    }

    return 0;
}
