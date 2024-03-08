#include <bits/stdc++.h>

#define all(x) (x).begin(), (x).end()
#define max2(x, y) (x > y ? x : y)
#define min2(x, y) (x < y ? x : y)
#define max3(x, y, z) (x > max2(y, z) ? x : max2(y, z))
#define min3(x, y, z) (x < min2(y, z) ? x : min2(y, z))

using namespace std;

using ll = int64_t;
using ull = uint64_t;
using vi = vector<int>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m, l;
    cin >> n >> m >> l;
    vector<vi> A(n, vi(l, 0));
    vector<vi> B(m, vi(l, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < l; ++j) {
            cin >> A[i][j];
        }
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < l; ++j) {
            cin >> B[i][j];
        }
    }
    

    int q;
    cin >> q;

    for (int k = 0; k < q; ++k) {
        int i, j;
        cin >> i >> j;

        // cout << "INPUT = " << i << " " << j << endl;

        // vi& A[i - 1] = A[i - 1];
        // vi& B[j - 1] = B[j - 1];

        if (A[i - 1][l - 1] <= B[j - 1][l - 1]) {
            cout << l << '\n'; 
        } else if (A[i - 1][0] >= B[j - 1][0]) {
            cout << 1 << '\n';
        } else {

            int left = 0;
            int right = l - 1;

            while (left < right - 1) {
                int middle = (left + right) / 2;

                if (A[i - 1][middle] - B[j - 1][middle] < 0) {
                    left = middle;
                } else {
                    right = middle;
                }
            }

            if (max2(A[i - 1][left], B[j - 1][left]) < max2(A[i - 1][right], B[j - 1][right])) {
                cout << left + 1 << '\n';
            } else {
                cout << right + 1 << '\n';
            }

            // cout << "left = " << left << ", right = " << right << endl;
            // cout << A[i - 1][left] << " " << A[i - 1][right] << endl;            

        }
    }

    return 0;
}