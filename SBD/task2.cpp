#include <bits/stdc++.h>

using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    
    int ptr = 0;
    string a;
    string b;
    string c;

    cin >> a;
    cin >> c;

    for (int i = 0; i < c.size(); ++i) {
        if ('a' <= c[i] && c[i] <= 'z') {
            b.insert(ptr, 1, c[i]);
            ++ptr;
        } else {
            
            ++i;

            if (c[i] == 'l') {
                if (ptr > 0) --ptr;
                i += 4;

            } else if (c[i] == 'r') {

                if (ptr < b.size()) ++ptr;
                i += 5;

            } else if (c[i] == 'd') {

                if (ptr < b.size()) b.erase(b.begin() + ptr);
                i += 6;

            } else if (c[i] == 'b') {
                
                if (ptr > 0) b.erase(b.begin() + --ptr);
                i += 6;
            }
        }
    }

    if (a == b) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }

    return 0;
}