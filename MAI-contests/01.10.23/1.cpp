#include <iostream>

using namespace std;


int main() {
    int t;
    cin >> t;
    for (int _ = 0; _ < t; ++_) {
        double a, d;
        cin >> a >> d;
        double b = 100 - a;
        double res1 = (b / a ) * (100 - d) / 100;
        double res2 = (a / b) * (100 - d) / 100;
        cout.precision(10);
        cout << res1 + 1 << " " << res2 + 1 << endl;
    }


}