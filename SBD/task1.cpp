#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    string s;

    cin >> s;

    bool have_big_letter = false;
    bool have_small_letter = false;
    bool have_digit = false;

    for (int i = 0; i < s.size(); ++i) {
        if ('a' <= s[i] && s[i] <= 'z') {
            have_small_letter = true;
        } 

        if ('A' <= s[i] && s[i] <= 'Z') {
            have_big_letter = true;
        }

        if ('0' <= s[i] && s[i] <= '9') {
            have_digit = true;
        }
    }


    if (s.size() >= 8 && have_big_letter && have_small_letter && have_digit) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}