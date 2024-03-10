#include <iostream>

using namespace std;


int main() {
    int p, v, q, m;
    cin >> p >> v >> q >> m;

    int left_vasya = p - v;
    int right_vasya = p + v;
    int left_masha = q - m;
    int right_masha = q + m;

    if (right_vasya < left_masha || right_masha < left_vasya) {
        cout << right_vasya - left_vasya + 1 + right_masha - left_masha + 1 << endl;
    } else {
        cout << max(right_masha, right_vasya) -  min(left_vasya, left_masha) + 1 << endl;
    }

    return 0;
}