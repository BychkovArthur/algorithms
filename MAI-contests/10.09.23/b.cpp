#include <bits/stdc++.h>
 
using namespace std;
using ll = long long int;


int main() {

	ios::sync_with_stdio(false);
	cin.tie(0);

    int t;
    cin >> t;
    for (int _ = 0; _ < t; _ ++) {
        int n;
        cin >> n;
        vector<int> a;
        vector<int> b;
        for (int i = 0; i < n; i ++) {
            int value;
            cin >> value;
            a.push_back(value);
        }
        for (int i = 0; i < n; i ++) {
            int value;
            cin >> value;
            b.push_back(value);
        }
        int gcd_a = a[0];
        int gcd_b = b[0];
        for (int i = 1; i < n; i ++) {
            gcd_a = gcd(gcd_a, a[i]);
            gcd_b = gcd(gcd_b, b[i]);
        }
        if (gcd_a == gcd_b) {
            cout << "0" << endl;
        } else {
            if (gcd_a % gcd_b == 0 or gcd_b % gcd_a == 0) {
                cout << "1" << endl;
            } else {
                cout << "2" << endl;
            }
        }
    }
}
