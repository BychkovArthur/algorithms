#include <bits/stdc++.h>
#include <cstdint>
#include <vector>

using namespace std;

void FloydWarshall(vector<vector<int64_t>>& matrix) {
    auto n = matrix.size();
    auto buffer = matrix;

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][k] == INT64_MAX || matrix[k][j] == INT64_MAX) continue;

                if (matrix[i][j] > matrix[i][k] + matrix[k][j]) {
                    buffer[i][j] = matrix[i][k] + matrix[k][j];
                }
            }
        }

        matrix = buffer;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);


    int n;
    cin >> n;
    vector<vector<int64_t>> weights(n, vector<int64_t>(n, INT64_MAX));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> weights[i][j];
        }
    }

    FloydWarshall(weights);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << weights[i][j] << ' ';
        }
        cout << '\n';
    }
}