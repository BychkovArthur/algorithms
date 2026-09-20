#include "counting_sort.h"

#include <algorithm>


void CountingSort(std::vector<uint64_t>& a) {
    if (a.empty()) {
        return;
    }

    const auto maxElem = *std::max_element(a.begin(), a.end());
    std::vector<size_t> cnt(maxElem + 1);

    for (auto elem : a) {
        ++cnt[elem];
    }

    for (size_t i = 1; i < cnt.size(); ++i) {
        cnt[i] += cnt[i - 1];
    }

    std::vector<size_t> result(a.size());
    for (ssize_t i = a.size() - 1; i >= 0; --i) {
        result[--cnt[a[i]]] = a[i];
    }

    a = result;
}
