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

template <typename _Key, typename _Tp>
using umap = unordered_map<_Key, _Tp>;
template <typename _Value>
using uset = unordered_set<_Value>;

static const ll mod1 = 1'000'000'007;
static const ll mod2 = 2'147'483'647;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.precision(8);
    cout.setf(ios::fixed);
    
    int n;
    cin >> n;
    vector<long double> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    vector<long double> prefs(n);
    prefs[0] = log(a[0]);

    for (int i = 1; i < n; ++i) {
        prefs[i] = log(a[i]) + prefs[i - 1];
    }

    // for (int i = 0; i < n; ++i) {
    //     cout << prefs[i] << "HERE" << endl;
    // }

    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;

        // cout << l << ' ' << r << endl;

        cout << exp((prefs[r] - (l - 1 >= 0 ? prefs[l - 1] : 0)) / (r - l + 1)) << '\n';
    }
    
    

    return 0;
}