#include <iostream>
#include <string>
#include <vector> 


using namespace std;

vector<int> prefix_function (string s) {
	int n = (int) s.length();
	vector<int> pi (n);
	for (int i=1; i<n; ++i) {
		int j = pi[i-1];
		while (j > 0 && s[i] != s[j])
			j = pi[j-1];
		if (s[i] == s[j])  ++j;
		pi[i] = j;
	}
	return pi;
}

int main()
{
	int n;
    string pattern, str;
    cin >> n >> pattern >> str;
    int size = pattern.length() + str.length() + 1;
    string new_str = pattern + "#" + str;
    vector<int> a = prefix_function(new_str);
    for (int i = 0; i < size; ++i) {
        cout << a[i] << " " << new_str[i] << endl;
    }

	return 0;
}