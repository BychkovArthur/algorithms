#include "mtf.hpp"

#include <cstddef>
#include <cassert>

#include <utils.hpp>
#include <treap.hpp>
#include <map>

//std::vector<uint8_t> MTF::Encode(const std::vector<uint8_t>& text) {
//    auto arr = GetInitialOrder<uint8_t>();
//    std::vector<uint8_t> result;
//    result.reserve(text.size());
//
//    for (auto byte : text) {
//        result.push_back(arr[byte]);
//        for (size_t i = 0; i < kAlphabetSize; ++i) {
//            if (arr[i] < arr[byte]) {
//                ++arr[i];
//            }
//        }
//        arr[byte] = 0;
//    }
//    return result;
//}

std::vector<uint8_t> MTF::Encode(const std::vector<uint8_t>& text) {
    auto byte_value = GetInitialOrder<int64_t>(); // Изначально каждому байту X в куреве соответствует его значение
    Treap treap;
    for (int byte = 0; byte < kAlphabetSize; ++byte) {
        treap.insert(byte);
    }

    int64_t min_byte = -1;
    std::vector<uint8_t> result;
    result.reserve(text.size());

    for (const auto byte : text) {
        auto lower_than = treap.calculate_count_of_lower(byte_value[byte]);

        assert(0 <= lower_than && lower_than < kAlphabetSize);
        result.push_back(lower_than);
        treap.erase(byte_value[byte]);
        byte_value[byte] = min_byte;
        treap.insert(min_byte--);
    }
    return result;
}

std::vector<uint8_t> MTF::Decode(const std::vector<uint8_t>& encoded) {
    auto arr = GetInitialOrder<uint8_t>();
    std::vector<uint8_t> result;
    result.reserve(encoded.size());

    for (auto byte : encoded) {
        size_t index_to_skip = -1;

        for (size_t i = 0; i < kAlphabetSize; ++i) {
            if (arr[i] == byte) {
                result.push_back(i);
                arr[i] = 0;
                index_to_skip = i;
                break;
            }
        }

        for (size_t i = 0; i < kAlphabetSize; ++i) {
            if (i == index_to_skip) continue;
            if (arr[i] < byte) {
                ++arr[i];
            }
        }
    }

    return result;
}

//std::vector<uint8_t> MTF::Decode(const std::vector<uint8_t>& encoded) {
////    auto arr = GetInitialOrder<int64_t>();
//    std::map<int64_t, uint8_t> byte_mapping;
//    Treap treap;
//    for (int byte = 0; byte < kAlphabetSize; ++byte) {
//        treap.insert(byte);
//        byte_mapping[byte] = byte;
//    }
//
//    std::vector<uint8_t> result;
//    result.reserve(encoded.size());
//    int64_t min_byte = -1;
//
//    for (auto byte : encoded) {
//        auto encoded_ = treap.get_kth_order_statistic(byte + 1); // Это значение из дерева. Не то, что нужно выписывать в ответ
//        auto encoded_byte = byte_mapping[encoded_]; // А вот это уже верный байт.
//
//        // Удаляем из обоих деревьев
//        byte_mapping.erase(encoded_);
//        treap.erase(encoded_);
//
//        // Добавляем в оба дерева
//        byte_mapping[min_byte] = encoded_byte;
//        treap.insert(min_byte);
//        --min_byte;
//
//        result.push_back(encoded_byte);
//    }
//
//    return result;
//}
