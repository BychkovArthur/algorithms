#include <bits/stdc++.h>

using namespace std;


int main() {

    int n;
    cin >> n;
    vector<vector<int>> board(n, vector<int> (n));
    for (int i =0; i < n; i ++) {
        string line;
        cin >> line;
        for (int j = 0; j < n; j++) {
            if (line[j] == 'B') {
                board[i][j] = 0;
            } else {
                board[i][j] = 1;
            }
        }

    }
    int ans;
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < n; j++) {
            if (board[i][j]and board[i][j - 1]) {
                ans++;
                board[i][j] = 0;
                board[i][j - 1] = 0;
            }
        }
    }
    cout << ans << endl;

}