#include <iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
 
using namespace std;
using ll = long long int;
const ll INF = 1e18;
 
 
vector<int> z_func(const string & s) {
	int n = s.size();
	vector<int> z(n);
	z[0] = n;
	int l = 0, r = 0;
	
	for (int i = 1; i < n;i ++) {
		if (i < r) {
			z[i] = min(z[i - l], r - i);
		}
		while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
			++z[i];
		}
		if (i + z[i] > r) {
			l = i;
			r = i + z[i];
		}
	}
	return z;
}

 
int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);


	int n;
    cin >> n;
	string temp, s;
    cin >> temp >> s;


    string str = temp + "#" + s;
    vector<int> z = z_func(str);
    int sz = str.size();
    // KMP(s, temp);

    ll res = 0;
    ll count = 0;

    int start = temp.size() + 1;
    vector<string> answer;
    vector<int> decimals;
    // for (int i = 0; i < sz; ++i) {
    //     cout << z[i] << " " << str[i] << endl;
    // }

    bool isChecking = 0;
    int prevNumber = -1;
    int prevIndex = 0;


    for (int i = start; i < sz; ++i) {
        if (isChecking) {
            if (i <= prevIndex + prevNumber - 1) {
                if (z[i] > prevNumber) {
                    z[prevIndex] = 0;
                    isChecking = 0;
                } else if (i == prevIndex + prevNumber - 1) {
                    isChecking = 0;
                }
            }
        }

        if (z[i] != 0 && z[i] > n && isChecking == 0) {
            isChecking = 1;
            prevNumber = z[i];
            prevIndex = i;
        }
    }

	for (int i = start; i < sz; ++i) {
        
        if (z[i] != 0 && z[i] > n) {

            string a = "=";
            res += n;
            decimals.push_back(z[i]);
            answer.push_back(a);
            i += z[i] - 1;
        } else {
            string a = "+";
            a += str[i];
            answer.push_back(a);
            ++res;
        }
        ++count;
    }


    int i = 0;
    cout << res << " " << count << endl;
    for (string a : answer) {
        if (a == "=") {
            cout << "=" << decimals[i] << endl;
            ++i;
        } else {

        cout << a << endl;
        }
    }
}