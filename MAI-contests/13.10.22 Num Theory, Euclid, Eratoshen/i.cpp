#include <vector>
#include <cstdint>
#include <iostream>
#include <unordered_set>

using namespace std;
using ll = int64_t;

ll N = 4 * (ll)1e7;
// ll N = 100;
vector<int> primeDivsCount(N + 1, 0);
// vector<int> minPrimeDiv(N + 1, -1);


void sieve() {
    for (ll i = 2; i <= N; ++i) {
        if (primeDivsCount[i] > 0) continue;
        for (ll j = 2 * i; j <= N; j += i) {
            // if (minPrimeDiv[j] == -1) minPrimeDiv[j] = i;
            ++primeDivsCount[j];
        }
    }
}

// ll countPrimeDivs(ll num) {
//     unordered_set<ll> st;
    
//     while (minPrimeDiv[num] != -1) {
//         st.insert(minPrimeDiv[num]);
//         num /= minPrimeDiv[num];
//     }
//     st.insert(num);
//     return st.size();
// }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    sieve();
    ll n;
    cin >> n;

    for (ll i = 0; i < n; ++i) {
        ll num;
        cin >> num;

        if (num == 1) {
            cout << 0 << '\n';
            continue;
        }
        if (primeDivsCount[num] == 0) {
            cout << "Prime\n";
        } else {
            cout << primeDivsCount[num] << '\n';
        }

    }
}