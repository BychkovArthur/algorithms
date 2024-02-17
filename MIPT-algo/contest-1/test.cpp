#include <iostream>
#include <vector>
#include <array>
#include <cstdint>

using ull = uint64_t;

using namespace std;

void radix(std::vector<ull>& vct) {
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
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    size_t n;
    std::cin >> n;

    std::vector<ull> vct(n);


    for (size_t i = 0; i < n; ++i) {
        std::cin >> vct[i];
    }

    radix(vct);

    for (size_t i = 0; i < n; ++i) {
        std::cout << vct[i] << '\n';
    }

    return 0;
}