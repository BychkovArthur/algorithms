#include <bits/stdc++.h>

using namespace std;

int main() {
    
    std::string num;
    cin >> num;

    int r = 0;

    for (char c : num) {
        r = r * 10 + c - '0';
        r %= 97;
    }
    r %= 97;

    if (!r) {
        cout << "YES";
    } else {
        cout << "NO";
    }
}