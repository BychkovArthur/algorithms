#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <vector>
#include <algorithm>
#include <numeric>
#include <array>


constexpr size_t kAlphabetSize = 256;

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T> vct) {
    for (std::size_t i = 0; i < vct.size(); ++i) {
        os << vct[i];
        if (i != vct.size() - 1) {
            os << ", ";
        }
    }
    return os;
}

template <>
std::ostream& operator<<(std::ostream& os, const std::vector<uint8_t> vct) {
    for (std::size_t i = 0; i < vct.size(); ++i) {
        os << (int)vct[i];
        if (i != vct.size() - 1) {
            os << ", ";
        }
    }
    return os;
}


class SuffixArray {
private:
    const std::vector<int32_t> text_;
    std::size_t n_;
    std::vector<std::size_t> array_;

    static constexpr std::size_t different_chars = 256;

    inline bool is_sorted(const std::vector<std::size_t>& eq) const {
        /* Сортировку суффиксов можно завершать тогда,
        * когда в массиве eq все числа [0 ... n - 1]
        */
        return (n_ * (n_ - 1) / 2) == std::reduce(eq.begin(), eq.end());
    }

    void build() {
        std::size_t sz = 1;
        std::vector<std::size_t> count_sort(std::max(different_chars, n_), 0);
        std::vector<std::size_t> eq(n_, 0);
        std::vector<std::size_t> eq_buffer(n_, 0);
        std::vector<std::size_t> array_buffer(n_);
        
        /*Первоначальная сортировка подсчетом*/
        for (std::size_t i = 0; i < n_; ++i) {
            ++count_sort[text_[i]];
        }
        for (std::size_t i = 1; i < std::max(different_chars, n_); ++i) {
            count_sort[i] += count_sort[i - 1];
        }
        for (ssize_t i = n_ - 1; i >= 0; --i) {
            array_[--count_sort[text_[i]]] = i;
        }
        /*Первоначальная сортировка подсчетом*/


        /*Первоначальный подсчет eq*/
        for (std::size_t i = 1; i < n_; ++i) {
            if (text_[array_[i]] != text_[array_[i - 1]]) {
                eq[array_[i]] = eq[array_[i - 1]] + 1;
            } else {
                eq[array_[i]] = eq[array_[i - 1]];
            }
        }
        /*Первоначальный подсчет eq*/

        while (!is_sorted(eq)) {
            std::fill(count_sort.begin(), count_sort.end(), 0);
            eq_buffer = eq;
            
            /* Подсчет p'*/
            for (std::size_t i = 0; i < n_; ++i) {
                array_buffer[i] = (array_[i] + n_ - sz) % n_;
            }
            /* Подсчет p'*/

            /* Подсчет p''*/
            for (std::size_t i = 0; i < n_; ++i) {
                ++count_sort[eq[array_buffer[i]]];
            }
            for (std::size_t i = 1; i < n_; ++i) {
                count_sort[i] += count_sort[i - 1];
            }
            for (ssize_t i = n_ - 1; i >= 0; --i) {
                array_[--count_sort[eq[array_buffer[i]]]] = array_buffer[i];
            }
            /* Подсчет p''*/
            
            /* Подсчет eq*/
            eq[0] = 0;
            for (std::size_t i = 1; i < n_; ++i) {
                if (
                    eq_buffer[array_[i - 1]] < eq_buffer[array_[i]] ||
                    eq_buffer[array_[i - 1]] == eq_buffer[array_[i]] && eq_buffer[(array_[i - 1] + sz) % n_] < eq_buffer[(array_[i] + sz) % n_]
                ) {
                    eq[array_[i]] = eq[array_[i - 1]] + 1;
                } else {
                    eq[array_[i]] = eq[array_[i - 1]];
                }
            }
            /* Подсчет eq*/

            sz <<= 1;
        }
    }

public:

    SuffixArray(const std::vector<int32_t>& text) : text_(text), n_(text_.size()), array_(n_, -1) {
        build();
    }

    const std::vector<std::size_t>& get_suffix_array() {
        return array_;
    }
};

std::vector<uint8_t> CountSort(const std::vector<uint8_t>& text) {
    std::array<size_t, kAlphabetSize> counter{};

    for (auto character : text) {
        ++counter[character];
    }

    std::vector<uint8_t> result;
    result.reserve(text.size());
    for (size_t i = 0; i < kAlphabetSize; ++i) {
        for (size_t j = 0; j < counter[i]; ++j) {
            result.push_back(static_cast<uint8_t>(i));
        }
    }
    return result;
}

class BWT {

    std::vector<uint8_t> CalculateEncodedText(const std::vector<uint8_t>& text, const std::vector<std::size_t>& suffix_array) {
        auto n = suffix_array.size();
        std::vector<uint8_t> result;
        result.reserve(n);

        for (const auto& i : suffix_array) {
            // Это последний байт в каждом циклическом сдвиге.
            uint8_t last_byte = text[(i + (n - 1)) % n];
            // result.push_back(last_byte == '\0' ? '$' : last_byte);   // На 3
            result.push_back(last_byte);                             // На 5
        }
        return result;
    }

    // size_t CalculateEncodedIndex5(const std::vector<std::size_t>& suffix_array) {
    //     return std::find(suffix_array.begin(), suffix_array.end(), 0) - suffix_array.begin();
    // }
    size_t CalculateEncodedIndex(const std::vector<uint8_t>& encoded) {
        return std::find(encoded.begin(), encoded.end(), 0) - encoded.begin();
    }

    std::vector<size_t> GetDecodingPermutation(const std::vector<uint8_t>& first, const std::vector<uint8_t>& last) {
        std::array<size_t, kAlphabetSize> counter;
        std::vector<size_t> result;
        result.reserve(first.size());

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

    std::vector<int32_t> ConvertToVectorWithSentinel(const std::vector<uint8_t>& text) {
        std::vector<int32_t> result(text.begin(), text.end());
        // result.push_back(-1);
        return result;
    }

public:

    std::vector<uint8_t> Encode(const std::vector<uint8_t>& text) {
        SuffixArray suffix_array_factory(ConvertToVectorWithSentinel(text));
        const auto& suffix_array = suffix_array_factory.get_suffix_array();

        // assert(text.size() + 1 == suffix_array.size()); // для байт
        assert(text.size() == suffix_array.size());

        return CalculateEncodedText(text, suffix_array);
    }

    std::vector<uint8_t> Decode(const std::vector<uint8_t>& encoded) {
        auto first = CountSort(encoded);
        auto last = encoded;

        auto permutation = GetDecodingPermutation(first, last);

        // Это в случае с заданием на 3
        size_t index = CalculateEncodedIndex(encoded);
        std::vector<uint8_t> result;
        result.reserve(first.size());

        result.push_back(first[index]);
        for (size_t i = 0; i < first.size() - 2; ++i) { // вот здесь мб проблема с индексом будет
            index = permutation[index];
            result.push_back(first[index]);
        }

        return result;
    }
};


class MTF {
    // std::array<uint8_t, kAlphabetSize> GetInitialOrder() {
    //     std::array<uint8_t, kAlphabetSize> result;
    //     for (size_t i = 0; i < kAlphabetSize; ++i) {
    //         result[i] = i;
    //     }
    //     return result;
    // }

    std::array<uint8_t, 27> GetInitialOrder() {
        std::array<uint8_t, 27> result;
        for (size_t i = 0; i < 27; ++i) {
            result[i] = i;
        }
        return result;
    }

public:

    std::vector<uint8_t> Encode(const std::vector<uint8_t>& text) {
        auto arr = GetInitialOrder();
        std::vector<uint8_t> result;
        result.reserve(text.size());

        for (auto byte : text) {
            if ('a' <= byte && byte <= 'z') {
                byte -= 'a';
                byte += 1;
            }
            result.push_back(arr[byte]);

            for (size_t i = 0; i < 27; ++i) {
                if (arr[i] < arr[byte]) {
                    ++arr[i];
                }
                
            }
            arr[byte] = 0;
        }
        return result;
    }

    std::vector<uint8_t> Decode(const std::vector<uint8_t>& encoded) {
        auto arr = GetInitialOrder();
        std::vector<uint8_t> result;
        result.reserve(encoded.size());

        for (auto byte : encoded) {
            size_t index_to_skip = -1;

            for (size_t i = 0; i < 27; ++i) {
                if (arr[i] == byte) {
                    result.push_back(i);
                    arr[i] = 0;
                    index_to_skip = i;
                    break;
                }
            }
            
            for (size_t i = 0; i < 27; ++i) {
                if (i == index_to_skip) continue;
                if (arr[i] < byte) {
                    ++arr[i];
                }
            }
        }

        // Это только для 27
        for (auto& elem : result) {
            if (elem > 0) {
                elem += ('a' - 1);
            }
        }

        return result;
    }
};

class RLE {

public:
    struct Encoded {
        size_t count;
        uint8_t byte;
    };

    std::vector<Encoded> Encode(const std::vector<uint8_t>& text) {
        std::vector<Encoded> result;

        for (size_t i = 0; i < text.size();) {
            size_t j = i + 1;
            while (j < text.size() && text[i] == text[j]) ++j;
            result.push_back(Encoded{
                .count = j - i,
                .byte = text[i],
            });
            i = j;
        }
        return result;
    }

    std::vector<uint8_t> Decode(const std::vector<Encoded>& encoded) {
        std::vector<uint8_t> result;

        for (const auto& data : encoded) {
            for (size_t i = 0; i < data.count; ++i) {
                result.push_back(data.byte);
            }
        }
        return result;
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    BWT bwt; // вообще можно их от базового интерфейса унаследовать
    MTF mtf;
    RLE rle;

    std::string type;
    std::cin >> type;

    if (type == "compress") {
        std::string text;
        std::cin >> text;

        std::vector<uint8_t> bytes;
        bytes.reserve(text.size());
        for (int i = 0; i <= text.size(); ++i) {
            bytes.push_back(text[i]);
        }

        auto encoded = rle.Encode(mtf.Encode(bwt.Encode(bytes)));
        for (const auto& data : encoded) {
            std::cout << data.count << ' ' << (int)data.byte << '\n';
        }
    } else {
        std::vector<RLE::Encoded> encoded;
        size_t count;
        size_t byte;
        while (std::cin >> count && std::cin >> byte) encoded.push_back(RLE::Encoded{.count = count, .byte = (uint8_t)byte});

        auto decoded = bwt.Decode(mtf.Decode(rle.Decode(encoded)));
        std::string result;
        for (const auto& d : decoded) {
            result.push_back(d);
        }

        std::cout << result << '\n';
    }
}