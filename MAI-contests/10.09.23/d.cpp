#include <bits/stdc++.h>
 
using namespace std;
using ll = long long int;


int main() {

	ios::sync_with_stdio(false);
	cin.tie(0);

    int t;
    cin >> t;
    for (int _ = 0; _ < t; ++_) {
        int x, y;
        cin >> x >> y;
        if (y == 100) {
            cout << -1 << endl;
        } else {
            for (int sm = x; sm <= x * 105; ++sm) {
                int y_sum = sm - x;
                // cout << y_sum << " " << sm << endl;
                if (y_sum * 100 >= y * sm) {
                    cout << sm << endl;
                    break;
                }
            }
        }
    }
}
