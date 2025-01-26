#include "hashing.hpp"
#include <iostream>

uint32_t crc = 0xFFFFFFFF;
constexpr uint32_t polynomial = 0xEDB88320;

void update_crc(const char* bytes, size_t n) {
    for (size_t j = 0; j < n; ++j) {
        crc ^= bytes[j];
        for (int i = 0; i < 8; ++i) {
            if (crc & 1) {
                crc = (crc >> 1) ^ polynomial;
            } else {
                crc >>= 1;
            }
        }
    }
}

uint32_t calculate_crc32(const MetaInfo& meta, const CompressionLevel& level, const CompressedFile& file) {
    crc = 0xFFFFFFFF;
    update_crc(reinterpret_cast<const char*>(&meta.compressed_size), sizeof (meta.compressed_size));
    update_crc(reinterpret_cast<const char*>(&meta.uncompressed_size), sizeof (meta.uncompressed_size));
    update_crc(reinterpret_cast<const char*>(&meta.uncompressed_filename_length), sizeof (meta.uncompressed_filename_length));
    update_crc(reinterpret_cast<const char*>(meta.uncompressed_filename.c_str()), meta.uncompressed_filename_length * sizeof (meta.uncompressed_filename[0]));
    update_crc(reinterpret_cast<const char*>(&level), sizeof (level));
    update_crc(reinterpret_cast<const char*>(&file.serialized_huffman_tree[0]), file.serialized_huffman_tree.size() * sizeof (file.serialized_huffman_tree[0]));
    update_crc(reinterpret_cast<const char*>(&file.alignment), sizeof (file.alignment));
    if (file.BWT_index.has_value()) { // Не будет ли тут проблем?
        update_crc(reinterpret_cast<const char*>(&file.BWT_index.value()), sizeof (file.BWT_index.value()));
    }
    update_crc(
            reinterpret_cast<const char*>(&file.compressed_file[0]),
            file.compressed_file.size() * sizeof(file.compressed_file[0])
           );

    return ~crc;
}

uint32_t calculate_crc32(std::istream& ifs) {
    uint32_t crc = 0xFFFFFFFF;
    constexpr uint32_t polynomial = 0xEDB88320;

    char byte;
    while (ifs.read(reinterpret_cast<char*>(&byte), sizeof(byte))) {
        crc ^= byte;
        for (int i = 0; i < 8; ++i) {
            if (crc & 1) {
                crc = (crc >> 1) ^ polynomial;
            } else {
                crc >>= 1;
            }
        }
    }

    return ~crc;
}