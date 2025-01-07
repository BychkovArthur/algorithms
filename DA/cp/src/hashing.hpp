#pragma once

#include <vector>
#include <cstdint>
#include <optional>
#include <string>
#include <fstream>

struct MetaInfo {
    size_t compressed_size;
    size_t uncompressed_size;
    size_t uncompressed_filename_length;
    std::string uncompressed_filename;
};

enum class CompressionLevel : uint8_t {
    kFast = 0,
    kSlow = 1,
};

struct CompressedFile {
    std::vector<uint8_t> compressed_file;
    std::vector<int16_t> serialized_huffman_tree;
    uint8_t alignment;
    std::optional<size_t> BWT_index;
};

uint32_t calculate_crc32(const MetaInfo& meta, const CompressionLevel& level, const CompressedFile& file);
uint32_t calculate_crc32(std::ifstream& ifs);