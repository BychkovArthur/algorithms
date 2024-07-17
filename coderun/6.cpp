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
using vll = vector<ll>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using matrix = vector<vector<int>>;
using matrixll = vector<vector<ll>>;

template <typename _Key, typename _Tp>
using umap = unordered_map<_Key, _Tp>;
template <typename _Value>
using uset = unordered_set<_Value>;

static const ll mod1 = 1'000'000'007;
static const ll mod2 = 2'147'483'647;

/*
    IO
*/

template<typename T, typename V>
ostream& operator<<(ostream& os, pair<T, V> pr) {
    os << pr.first << ", " << pr.second;
    return os;
}

/*
    IO
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    cin >> m;
    vector<int> b(m + 1);
    for (int i = 1; i <= m; ++i) cin >> b[i];

    matrix dp(n + 1, vi(m + 1, 0));
    vi ans;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (a[i] == b[j]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }





    int i = n, j = m;
    while (i && j) {
        if (a[i] == b[j]) {
            ans.push_back(a[i]);
            --i;
            --j;
        } else {
            if (dp[i - 1][j] > dp[i][j - 1]) {
                --i;
            } else {
                --j;
            }
        }
    }

    if (!ans.size()) return 0;

    for (int i = ans.size() - 1; i >= 0; --i) {
        cout << ans[i] << ' ';
    }

    return 0;
}