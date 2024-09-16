#include <bits/stdc++.h>

using namespace std;



int main() {

    int l, t;
    cin >> l >> t;

    int winner = t;
    int loser = l - t;

    cout << winner - loser << endl;

    return 0;
}