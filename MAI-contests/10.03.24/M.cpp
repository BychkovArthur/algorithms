#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int w1, w2, w3;
int p1, p2, p3;

int calc_delivery(vector<int>& a) {
    int res = 0;

    for (auto weight : a) {

        if (weight < 5) {
            res += p1;
        } else if (weight < 10) {
            res += p2;
        } else {
            res += p3;
        }
    }
    return res;
}

int main() {
    
    
    cin >> w1 >> w2 >> w3;
    
    cin >> p1 >> p2 >> p3;

    vector<int> a1 = {w1, w2, w3};
    vector<int> a2 = {w1 + w2, w3};
    vector<int> a3 = {w1, w2 + w3};
    vector<int> a4 = {w1 + w3, w2};
    vector<int> a5 = {w1 + w2 + w3};

    vector<int> result = {
        calc_delivery(a1),
        calc_delivery(a2),
        calc_delivery(a3),
        calc_delivery(a4),
        calc_delivery(a5),
    };

    // for (int i = 0; i < 5; ++i) {
    //     cout << "RES = " << result[i] << endl;
    // }


    cout << *min_element(result.begin(), result.end()) << endl;
}