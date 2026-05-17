#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<vector<string>> results;

    bool isSafe(vector<string>& board, int row, int col, int n) {
        // Check same column
        for (int i = 0; i < row; i++) {
            if (board[i][col] == 'Q')
                return false;
        }

        // Check upper-left diagonal
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
            if (board[i][j] == 'Q')
                return false;
        }

        // Check upper-right diagonal
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
            if (board[i][j] == 'Q')
                return false;
        }

        return true;
    }

    void solve(vector<string>& board, int row, int n) {
        if (row == n) {
            results.push_back(board);
            return;
        }

        for (int col = 0; col < n; col++) {
            if (isSafe(board, row, col, n)) {
                board[row][col] = 'Q';
                solve(board, row + 1, n);
                board[row][col] = '.';
            }
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        vector<string> board(n, string(n, '.'));
        solve(board, 0, n);
        return results;
    }
};

int main() {
    Solution sol;
    int n;
    cout << " Enter the number of queens: " << endl;
    cin >> n;
    vector<vector<string>> answers = sol.solveNQueens(n);
    if(answers.size() == 0) cout << "!!!!!!!!No possible solution!!!!" << endl;
    for (auto board : answers) {
        for (auto row : board) {
            cout << row << endl;
        }
        cout << "---------" << endl;
    }

    return 0;
}