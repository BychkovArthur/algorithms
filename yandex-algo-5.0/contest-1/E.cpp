#include <iostream>
#include <string>

using namespace std;


int main() {

    long long int n, k, d;
    cin >> n >> k >> d;

    string number = to_string(n);
    
    long long int r = n % k;

    bool is_bad = false;


    for (long long int i = 0; i < d; ++i) {
        r *= 10;
        bool new_digit_find = false;
        for (long long int new_digit = 0; new_digit <= 9; ++new_digit) {
            if ((r + new_digit) % k == 0) {
                number.push_back('0' + new_digit);
                r = 0;
                new_digit_find = true;
                break;
            }
        }

        if (!new_digit_find) {
            is_bad = true;
            break;
        }

    }

    if (is_bad) {
        cout << -1 << endl;
    } else {
        cout << number << endl;
    }

    return 0;
}