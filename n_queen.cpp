#include <vector>
#include <string>
#include <iostream>

using namespace std;

// Function to check if placing a queen at (row, col) is valid
bool isValid(const vector<string>& board, int row, int col) {
    int n = board.size();
    
    // Check column
    for (int i = 0; i < row; ++i) {
        if (board[i][col] == 'Q') return false;
    }
    
    // Check upper left diagonal
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j) {
        if (board[i][j] == 'Q') return false;
    }
    
    // Check upper right diagonal
    for (int i = row - 1, j = col + 1; i >= 0 && j < n; --i, ++j) {
        if (board[i][j] == 'Q') return false;
    }
    
    return true;
}

// Recursive function to solve N-Queens
void solveNQueensHelper(int row, int n, vector<string>& board, vector<vector<string>>& solutions) {
    if (row == n) {
        solutions.push_back(board);
        return;
    }
    
    for (int col = 0; col < n; ++col) {
        if (isValid(board, row, col)) {
            board[row][col] = 'Q';
            solveNQueensHelper(row + 1, n, board, solutions);
            board[row][col] = '.';
        }
    }
}

// Main function to solve N-Queens
vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> solutions;
    vector<string> board(n, string(n, '.'));
    solveNQueensHelper(0, n, board, solutions);
    return solutions;
}

// Function to print all solutions
void printSolutions(const vector<vector<string>>& solutions) {
    for (const auto& solution : solutions) {
        for (const string& row : solution) {
            cout << row << endl;
        }
        cout << "----------------" << endl;
    }
}

int main() {
    // int n = 4;
    int n;
    cin >> n;
    vector<vector<string>> solutions = solveNQueens(n);
    
    cout << "Solutions for " << n << "-Queens problem:" << endl;
    printSolutions(solutions);
    
    return 0;
}