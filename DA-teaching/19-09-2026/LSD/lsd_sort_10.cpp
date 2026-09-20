#include <algorithm>


static constexpr size_t BASE = 10;


namespace {  // анонимный неймспейс

// Если максимальный элемент = 0, то итераций 0 и ничего не будет
size_t GetIterationsCount(const std::vector<size_t>& a) {
    if (a.empty()) {
        return 0;
    }

    size_t maxElem = *std::max_element(a.begin(), a.end());
    size_t iterations = 0;
    while (maxElem > 0) {
        ++iterations;
        maxElem /= BASE; // BASE = 10
    }

    return iterations;
}


// GetIthDigit(5234, 2)
// 523
// 52
// 52 % 10 = 2
size_t GetIthDigit(size_t number, size_t i) {
    for (size_t _ = 0; _ < i; ++_) {
        number /= BASE;
    }
    return number % BASE;
}


template <size_t N>
void MakePrefixSum(std::array<size_t, N>& cnt) {
    for (size_t i = 1; i < N; ++i) {
        cnt[i] += cnt[i - 1];
    }
}

}  // namespace


/*
    O(d(dn+k)), где
        n - количество элементов
        k - основание СС (в этом случае 10)
        d - количество разрядов в максимальном числе
    
    * Множитель d около n появляется из-за функции GetIthDigit. Она работает за O(d)
*/
void LSD(std::vector<size_t>& a) {
    const auto n = a.size();
    const auto iterations = GetIterationsCount(a);

    std::vector<size_t> result = a;
    std::vector<size_t> buffer(n);

    for (size_t it = 0; it < iterations; ++it) {
        std::array<size_t, BASE> cnt{};

        for (size_t i = 0; i < n; ++i) {
            ++cnt[GetIthDigit(result[i], it)];
        }

        MakePrefixSum(cnt);

        // ssize_t = -1, 0, 1, 2, 3, 4, .... 2^64-1
        for (ssize_t i = n - 1; i >= 0; --i) {
            buffer[--cnt[GetIthDigit(result[i], it)]] = result[i];
        }

        // А если идти с начала?
        // size_t preFirst = 0;
        // for (size_t i = 0; i < n; ++i) {
        //     const auto digit = GetIthDigit(result[i], it);
        //     if (digit > 0) {
        //         buffer[cnt[digit - 1]++] = result[i];
        //     } else {
        //         buffer[preFirst++] = result[i];
        //     }
        // }

        result = buffer;
    }

    a = result;
}
