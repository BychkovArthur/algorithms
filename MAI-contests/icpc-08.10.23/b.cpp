#include <bits/stdc++.h>

using namespace std;

int main() {
    int k;
    cin >> k;
    
    long long int sm = 0;

    for (int i = 0; i < k; ++i) {
        long long int val;
        cin >> val;
        sm += val;
    }
    long long int mn = -1;
    long long int mx = -1;

    if ( -180 * k + sm + 360 < 0) {
        cout << -1 << endl;
        return 0;
    }

    if ( k >= 3 && (k - 2) * 180 == sm ) {
        mn = k;
    } else {
        long double res1 = (long double) (sm + 360 - 180 * k) / (long double) 179 + k;
        mn = (long long int ) ceil(res1);
    }
    mx = (sm + 360 - 180 * k) + k;

    cout << mn << " " << mx << endl;


}