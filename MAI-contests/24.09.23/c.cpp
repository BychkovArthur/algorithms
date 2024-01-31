#include <bits/stdc++.h>

using namespace std;

int main() {

    int n;
    cin >> n;
    vector<int> red(n);
    vector<int> blue(n);
    for (int i = 0; i < n; i++) {
        cin >> red[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> blue[i];
    }

    sort(red.begin(), red.end());
    sort(blue.begin(), blue.end(), greater<int>());
    
    long long int mx = -1e10, mn = 1e10;
    for (int i = 0; i < n; i++) {
        if (red[i] + blue[i] > mx) {
            mx = red[i] + blue[i];
        }
        if (red[i] + blue[i] < mn) {
            mn = red[i] + blue[i];
        }
    }
    cout << mx - mn << endl;
}