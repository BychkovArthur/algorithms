#include <bits/stdc++.h>
using namespace std;

using ll = int64_t;
using ull = uint64_t;
using vi = vector<int>;
using vll = vector<ll>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;


void radix_sort(std::vector<ull>& vct) {
    ull max = 0;
    size_t n = vct.size();

    std::array<size_t, 256> arr{};
    std::vector<ull> other(n);

    for (size_t i = 0; i < n; ++i) {
        max = vct[i] > max ? vct[i] : max;
    }

    // 1) Выполнить сортировку подсчётом по разряду
    // 2) тут же посчитать преффиксную сумму этого массива
    // 3) Записать в другой массив результат

    ull digit = 255;
    ull numberOfDigit = 0;

    while ((digit <= max) || (digit & max)) {
        
        // Сортировка подсчётом
        for (size_t i = 0; i < n; ++i) {
            ull remainder = (vct[i] & digit) >> (8 * numberOfDigit);
            ++arr[remainder];
        }
        
        // Префиксные суммы
        for (size_t i = 1; i < 256; ++i) {
            arr[i] += arr[i - 1];
        }

        // Сортируем массив по k-й с конца цифре в 256 сс
        for (ssize_t i = n - 1; i >= 0; --i) {
            ull remainder = ((vct[i] & digit) >> (8 * numberOfDigit));
            --arr[remainder];
            other[arr[remainder]] = vct[i];
        }

        /*
            Занулять надо.
            Для каждого числа мы вычтем только то, сколько раз само это число встречается.
            Но, т.к. у нас в arr хранятся префиксные суммы, то занулится только наименьшая цифра.
        */
        for (size_t i = 0; i < 256; ++i) {
            arr[i] = 0;
        }

        ++numberOfDigit;
        digit <<= 8;
        std::swap(vct, other);

        if (numberOfDigit == 8) { // Сделали 8 сдвигов
            break;                // По идее, при 7 не должно работать, но оно заходит.
                                  // Проверить на числах, которые отличаются самым старшим байтом
        }
    }
}

int main() {

    size_t n = 1'000'000;
    size_t times = 1;
    size_t radix_time = 0;
    size_t quick_time = 0;

    for (size_t _i = 0; _i < times; ++_i) {

        vector<ull> quick(n);
        vector<ull> radix(n);
        std::srand(std::time(NULL));

        for (size_t i = 0; i < n; ++i) {
            ll x = std::rand();

            quick[i] = x;
            radix[i] = x;
        }

        cout << "start sorting" << endl;

        auto begin_quick = std::chrono::steady_clock::now();
        sort(quick.begin(), quick.end());
        auto end_quick = std::chrono::steady_clock::now();

        auto begin_radix = std::chrono::steady_clock::now();
        radix_sort(radix);
        auto end_radix = std::chrono::steady_clock::now();

        bool is_equal = true;
        for (size_t i = 0; i < n; ++i) {
            if (quick[i] != radix[i]) {
                is_equal = false;
                break;
            }
        }

        if (is_equal) {
            cout << "Test " << _i + 1 << " passed" << endl;
        } else {
            cout << "error..." << endl;
        } 

        quick_time += std::chrono::duration_cast<std::chrono::microseconds>(end_quick - begin_quick).count();
        radix_time += std::chrono::duration_cast<std::chrono::microseconds>(end_radix - begin_radix).count();

    }

    cout << "Radix time: " << radix_time << endl;
    cout << "Quick time: " << quick_time << endl;

}