#include "bwt.hpp"

#include <array>
#include <cassert>
#include <algorithm>

#include <suffix_tree.hpp>
#include <suffix_array.hpp>
#include <const.hpp>
#include <utils.hpp>


std::vector<uint8_t> BWT::CalculateEncodedText(const std::vector<uint8_t>& text, const std::vector<std::size_t>& suffix_array) {
//    auto n = text.size();
    auto n = suffix_array.size();
    std::vector<uint8_t> result;
    result.reserve(n);

    size_t sentinel_index = -1;

    int cnt = 0;

    for (const auto& i : suffix_array) {
//        if (i == n) continue; // Пропускаем элемент суффиксного массива, который соответствуе сентинелу

        // Это последний байт в каждом циклическом сдвиге.
        auto index =  (i + (n - 1)) % n;
        uint8_t last_byte = 0x00;
        if (index != n - 1) {
            last_byte = text[index];
        } else {
            ++cnt;
            sentinel_index = result.size();
        }


        result.push_back(last_byte);
    }

    assert(cnt == 1);

    return result;
}

size_t BWT::CalculateEncodedIndex(const std::vector<std::size_t>& suffix_array) {
    return std::find(suffix_array.begin(), suffix_array.end(), 0) - suffix_array.begin();
}

std::vector<size_t> BWT::GetDecodingPermutation(const std::vector<uint16_t>& first, const std::vector<uint16_t>& last) {
    std::array<size_t, kAlphabetSize + 1> counter;
    std::vector<size_t> result(first.size());

    assert(first.size() > 0);
    assert(first.size() == last.size());

    for (size_t i = 0; i < first.size(); ++i) {
        uint16_t byte = first[i];
        assert(byte <= kAlphabetSize);
        counter[byte] = i;
    }

    for (ssize_t i = first.size() - 1; i >= 0; --i) {
        uint16_t byte = last[i];
        assert(byte <= kAlphabetSize);
        result[counter[byte]--] = i;
    }
    return result;
}

std::vector<int32_t> BWT::ConvertToVectorWithSentinel(const std::vector<uint8_t>& text) {
    std::vector<int32_t> result(text.begin(), text.end());
    result.push_back(-1);
    for (auto& elem : result) ++elem; // Чтобы не было -1. И сентинелом стал 0.

//    std::cout << "With sentinel: " << result << std::endl;

    return result;
}


BWT::Encoded BWT::Encode(const std::vector<uint8_t>& text) {
    SuffixArray suffix_array_factory(ConvertToVectorWithSentinel(text));
    const auto& suffix_array = suffix_array_factory.GetSuffixArray();
//    SuffTree st(ConvertToVectorWithSentinel(text));
//    std::cout << "Start building" << std::endl;
//    st.Build();
//    std::cout << "End building" << std::endl;
//    const auto& suffix_array = st.BuildSuffixArray();
//    std::cout << "Build suff array" << std::endl;

//    std::cout << "SA = " << suffix_array << std::endl;

    assert(text.size() + 1 == suffix_array.size());

    return {
        .text = CalculateEncodedText(text, suffix_array),
        .index = CalculateEncodedIndex(suffix_array),
    };
}

std::vector<uint8_t> BWT::Decode(const BWT::Encoded& encoded) {
    std::vector<uint16_t> encoded_with_sentinel(encoded.text.size());
    for (size_t i = 0; i < encoded.text.size(); ++i) {
        encoded_with_sentinel[i] = encoded.text[i] + 1;
    }
    encoded_with_sentinel[encoded.index] = 0;

//    std::cout << "Encoded with sentinel: " << encoded_with_sentinel << std::endl;

    auto first = CountSort(encoded_with_sentinel);
    auto& last = encoded_with_sentinel;

//    std::cout << "First: " << first << std::endl;
//    std::cout << "Last: " << last << std::endl;

    /*
     * TODO: Зачем я это делал и что делает эта функция?)))
     */
    auto permutation = GetDecodingPermutation(first, last);

//    std::cout << "Permutation: " << permutation << std::endl;

    size_t index = encoded.index;
    std::vector<uint8_t> result;
    result.reserve(first.size());

    assert(0 <= first[index] - 1 && first[index] - 1 < kAlphabetSize);
    result.push_back(first[index] - 1);

    int assert_cnt = 0;
    for (size_t i = 0; i < first.size() - 1; ++i) { // вот здесь мб проблема с индексом будет
        index = permutation[index];
        if (index == 0) {
            ++assert_cnt;
            assert(first[index] == 0);
            assert(i == first.size() - 2);
            continue;
        }
        auto to_push = first[index] - 1;
//        std::cout << "Pushing: " << to_push << " index = " << index << std::endl;
        assert(0 <= to_push && to_push < kAlphabetSize);
        result.push_back(to_push);
    }
    assert(assert_cnt == 1);

    return result;
}
