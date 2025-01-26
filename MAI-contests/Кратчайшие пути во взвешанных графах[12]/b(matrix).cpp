#include <bits/stdc++.h>
#include <cstddef>
#include <cstdint>
#include <vector>

using namespace std;

void FindPathsWichGreaterOnOneEdge(vector<vector<int64_t>>& l, vector<vector<int64_t>>& l_buffer, const vector<vector<int64_t>>& weights) {
    int64_t n = l.size() - 1;

    /* В теории, здесь надо 
     * l_buffer = l;
     * 
     * Но, т.к. я в циклах не делаю проверку `if (k == i || k == j) continue`, то
     * в какой-то момент, у меня будет k = j =>
     * в этот момент, if (l[i][k] == INT64_MAX || weights[k][j] == INT64_MAX) не сработает, т.к.
     * l[i][k] = l[i][j] уже не ноль, следовательно все ок
     * w[k][j] = w[j][j] = 0 всегда
    **/
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            for (int k = 1; k <= n; ++k) {
                if (l[i][k] == INT64_MAX || weights[k][j] == INT64_MAX) {
                    continue;
                }
                l_buffer[i][j] = min(l_buffer[i][j], l[i][k] + weights[k][j]);
            }
        }
    }
    swap(l, l_buffer);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);


    int n;
    cin >> n;
    vector<vector<int64_t>> weights(n + 1, vector<int64_t>(n + 1, INT64_MAX));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> weights[i][j];
        }
    }

    auto l = weights;
    auto l_buffer = weights;

    // Solution with Time Complexity: O(V^4)
    // for (int i = 1; i <= n - 1; ++i) {
    //     FindPathsWichGreaterOnOneEdge(l, l_buffer, weights);
    // }

    // Solution with Time Complexity: O(V^3 * logV)
    size_t m = 1;
    while (m < n - 1) {
        FindPathsWichGreaterOnOneEdge(l, l_buffer, weights);
        weights = l;
        m *= 2;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cout << l[i][j] << ' ';
        }
        cout << '\n';
    }
}