#include "bwt.hpp"

#include <array>
#include <cassert>
#include <algorithm>

#include <suffix_array.hpp>
#include <const.hpp>
#include <utils.hpp>


std::vector<uint8_t> BWT::CalculateEncodedText(const std::vector<uint8_t>& text, const std::vector<std::size_t>& suffix_array) {
    auto n = text.size();
    std::vector<uint8_t> result;
    result.reserve(n);

    for (const auto& i : suffix_array) {
        if (i == n) continue; // Пропускаем элемент суффиксного массива, который соответствуе сентинелу

        // Это последний байт в каждом циклическом сдвиге.
        uint8_t last_byte = text[(i + (n - 1)) % n];

        result.push_back(last_byte);
    }
    return result;
}

size_t BWT::CalculateEncodedIndex(const std::vector<std::size_t>& suffix_array) {
    return std::find(suffix_array.begin(), suffix_array.end(), 0) - suffix_array.begin() - 1;
}

std::vector<size_t> BWT::GetDecodingPermutation(const std::vector<uint8_t>& first, const std::vector<uint8_t>& last) {
    std::array<size_t, kAlphabetSize> counter;
    std::vector<size_t> result(first.size());

    assert(first.size() > 0);
    assert(first.size() == last.size());

    for (size_t i = 0; i < first.size(); ++i) {
        uint8_t byte = first[i];
        counter[byte] = i;
    }

    for (ssize_t i = first.size() - 1; i >= 0; --i) {
        uint8_t byte = last[i];
        result[counter[byte]--] = i;
    }
    return result;
}

std::vector<int32_t> BWT::ConvertToVectorWithSentinel(const std::vector<uint8_t>& text) {
    std::vector<int32_t> result(text.begin(), text.end());
    result.push_back(-1);
    for (auto& elem : result) ++elem; // Чтобы не было -1. И сентинелом стал 0.
    return result;
}


BWT::Encoded BWT::Encode(const std::vector<uint8_t>& text) {
    SuffixArray suffix_array_factory(ConvertToVectorWithSentinel(text));
    const auto& suffix_array = suffix_array_factory.GetSuffixArray();

    assert(text.size() + 1 == suffix_array.size());

    return {
        .text = CalculateEncodedText(text, suffix_array),
        .index = CalculateEncodedIndex(suffix_array)
    };
}

std::vector<uint8_t> BWT::Decode(const BWT::Encoded& encoded) {
    auto first = CountSort(encoded.text);
    auto last = encoded.text;

    /*
     * TODO: Зачем я это делал и что делает эта функция?)))
     */
    auto permutation = GetDecodingPermutation(first, last);

    size_t index = encoded.index;
    std::vector<uint8_t> result;
    result.reserve(first.size());

    result.push_back(first[index]);
    for (size_t i = 0; i < first.size() - 1; ++i) { // вот здесь мб проблема с индексом будет
        index = permutation[index];
        result.push_back(first[index]);
    }

    return result;
}
