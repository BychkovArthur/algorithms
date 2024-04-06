#include <bits/stdc++.h>

using namespace std;



int main() {
    int n;
    cin >> n;

    int res = 1;

    string str;

    int prev_s = -1;

    for (int i = 0; i < n; ++i) {
        cin >> str;
        
        int h = (str[0] - '0') * 10 + (str[1] - '0');
        int m = (str[3] - '0') * 10 + (str[4] - '0');
        int s = (str[6] - '0') * 10 + (str[7] - '0');

        s += m * 60 + h * 60 * 60;
        
        if (s <= prev_s) {
            ++res;
        }
        prev_s = s;
    }

    cout << res << endl;
}