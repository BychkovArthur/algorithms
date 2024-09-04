#include <iostream>
#include <vector>
#include <cstdint>

using namespace std;

using ll = int64_t;
ll N = 15485863;
vector<int> vct(N + 1, 1);
vector<int> primes;

void sieve() {
    vct[0] = 0;
    vct[1] = 0;
    for (ll i = 2; i * i <= N; ++i) {
        if (!vct[i]) continue;
        for (ll j = i * i; j <= N; j += i) {
            vct[j] = 0;
        }
    }
}

int main() {
    sieve();
    primes.reserve(1e6 + 1);
    primes.push_back(0);
    for (ll i = 2; i <= N; ++i) {
        if (vct[i]) primes.push_back(i);
    }

    // cout << "BACK = " << primes.back() << endl;
    // cout << "SIZE = " << primes.size() << endl;

    ll n, m;
    cin >> n >> m;
    ll sum = 0;
    for (ll i = n; i <= m; ++i) {
        sum += primes[i];
    }
    cout << sum;
}