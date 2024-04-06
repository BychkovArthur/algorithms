#include <bits/stdc++.h>


using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);


    int p, m;
    cin >> p >> m;


    if (p == m) {
        if (p <= 18) {
            cout << 24 << endl;
        } else {
            
        }
    }


    int mn = min(p, m), mx = max(p, m);

    vector<pair<int, int>> ans;
    
    if (mn > 13) {
        ans.push_back({mn - 1, mn - 1 - 12});
    }
    if (mx < 23) {

    }

}