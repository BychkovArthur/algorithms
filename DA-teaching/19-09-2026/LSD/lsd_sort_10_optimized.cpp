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

template <size_t N>
void MakePrefixSum(std::array<size_t, N>& cnt) {
    for (size_t i = 1; i < N; ++i) {
        cnt[i] += cnt[i - 1];
    }
}

}  // namespace


/*
    O(d(n+k)), где
        n - количество элементов
        k - основание СС (в этом случае 10)
        d - количество разрядов в максимальном числе
*/
void LSD(std::vector<size_t>& a) {
    const auto n = a.size();
    const auto iterations = GetIterationsCount(a);
    size_t divider = 1;

    std::vector<size_t> result = a;
    std::vector<size_t> buffer(n);

    for (size_t it = 0; it < iterations; ++it) {
        std::array<size_t, BASE> cnt{};

        for (size_t i = 0; i < n; ++i) {
            ++cnt[result[i] / divider % BASE];
        }

        MakePrefixSum(cnt);

        // ssize_t = -1, 0, 1, 2, 3, 4, .... 2^64-1
        for (ssize_t i = n - 1; i >= 0; --i) {
            buffer[--cnt[result[i] / divider % BASE]] = result[i];
        }

        // А если идти с начала?
        // size_t preFirst = 0;
        // for (size_t i = 0; i < n; ++i) {
        //     const auto digit = result[i] / divider % BASE;
        //     if (digit > 0) {
        //         buffer[cnt[digit - 1]++] = result[i];
        //     } else {
        //         buffer[preFirst++] = result[i];
        //     }
        // }

        result = buffer;
        divider *= BASE;
    }

    a = result;
}
