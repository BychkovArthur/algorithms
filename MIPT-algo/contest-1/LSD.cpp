#include <array>
#include <iostream>
#include <vector>

void radix(std::vector<size_t>& vct) {
    size_t max = 0;
    size_t n = vct.size();

    std::array<size_t, 256> arr{};
    std::vector<size_t> other(n);

    for (size_t i = 0; i < n; ++i) {
        max = vct[i] > max ? vct[i] : max;
    }

    // 1) Выполнить сортировку подсчётом по разряду
    // 2) тут же посчитать преффиксную сумму этого массива
    // 3) Записать в другой массив результат

    size_t digit = 255;
    size_t numberOfDigit = 0;

    while ((digit <= max) || (digit & max)) {

        // Сортировка подсчётом
        for (size_t i = 0; i < n; ++i) {
            size_t remainder = (vct[i] & digit) >> (8 * numberOfDigit);
            ++arr[remainder];
        }

        // Префиксные суммы
        for (size_t i = 1; i < 256; ++i) {
            arr[i] += arr[i - 1];
        }

        // Сортируем массив по k-й с конца цифре в 256 сс
        for (ssize_t i = n - 1; i >= 0; --i) {
            size_t remainder = ((vct[i] & digit) >> (8 * numberOfDigit));
            --arr[remainder];
            other[arr[remainder]] = vct[i];
        }

        /*
            Занулять надо.
            Для каждого числа мы вычтем только то, сколько раз само это число
           встречается. Но, т.к. у нас в arr хранятся префиксные суммы, то
           занулится только наименьшая цифра.
        */
        for (size_t i = 0; i < 256; ++i) {
            arr[i] = 0;
        }

        ++numberOfDigit;
        if (numberOfDigit ==
            7) {  // Иначе будет сдвиг на 64 бита. Т.е. digit станет нулём.
            break;
        }

        digit <<= 8;
        std::swap(vct, other);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    size_t n;
    std::cin >> n;

    std::vector<size_t> vct(n);

    for (size_t i = 0; i < n; ++i) {
        std::cin >> vct[i];
    }

    radix(vct);

    for (size_t i = 0; i < n; ++i) {
        std::cout << vct[i] << '\n';
    }

    return 0;
}