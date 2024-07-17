#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() 
{
	int a, b, c, d, e;
    cin >> a >> b >> c >> d >> e;

    vector<int> aa = {d, e};
    vector<int> bb = {a, b, c};

    sort(aa.begin(), aa.end());
    sort(bb.begin(), bb.end());

    if (bb[0] <= aa[0] && bb[1] <= aa[1]) {
        cout << YES;
    } else {
        cout << NO;
    }

	return 0;
}
