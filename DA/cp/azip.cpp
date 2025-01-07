#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

#include <encoders/bwt.hpp>
#include <encoders/mtf.hpp>
#include <encoders/huffman.hpp>

#include <bitio.hpp>
#include <hashing.hpp>
#include <optional>

#include <chrono>
#include <cstring>
#include <fmt/format.h>

/* TODO:
 * 1) -lr <dir>: вывести информацию по всем файлам.
 * 2) -1 (просто Huffman), -9 (bwt + mtf + huffman)
 *
 *   
 *
 */

/*
 * 1) 4 bytes checksum
 * 2) Meta info table:
 *      a) compressed size (size_t)
 *      b) uncompressed size (size_t)
 *      c) ratio (???) - Можно и не хранить
 *      d) uncompressed_name (char[50] - тут надо будет еще обрезать(((( )
 * 3) type: fast (Huffman); slow (BWT + MTF + Huffman)
 * 4) (Если Huffman):
 *      a) SerializedTree
 *      b) alignment
 * 4) (Если BWT + MTF + Huffman)
 *      a) SerializedTree
 *      b) alignment
 *      c) BWT index
*/

bool to_stdout = false;
bool from_stdin = false;
bool decompress = false;
bool keep_input = false;
bool list_info = false;
bool recursive = false;
bool test_integrity = false;
size_t input_file_size = 0;
CompressionLevel compression_level = CompressionLevel::kSlow;
constexpr char* kCompressedFileSuffix = ".az";

size_t CalculateEncodedSize(const CompressedFile& compressed_file, const std::string& uncompressed_filename) {
    return (compressed_file.compressed_file.size() * sizeof(compressed_file.compressed_file[0])) +
           (compressed_file.serialized_huffman_tree.size() * sizeof(compressed_file.serialized_huffman_tree[0])) +
           sizeof (compressed_file.alignment) +
           (compressed_file.BWT_index.has_value() ? sizeof(compressed_file.BWT_index.value()) : 0) +

           sizeof (compression_level) +

           /* MetaInfo */
           uncompressed_filename.size() * sizeof (uncompressed_filename[0]) +
            sizeof(size_t) +              /* compressed_size*/
            sizeof(size_t) +              /* uncompressed_size */
            sizeof(size_t) +              /* uncompressed_filename_length */

            /* CheckSum */
            + sizeof(uint32_t );
}

//std::ifstream::pos_type filesize(const std::string& filename)
//{
//    std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
//    return in.tellg();
//}

CompressedFile CompressFile(const std::string& filename) {
    std::vector<uint8_t> input_file;

    if (!from_stdin) {
        std::ifstream ifs(filename, std::ios::binary);
        if (!ifs.is_open()) {
            throw std::runtime_error("Can't open file");
        }
        if (ifs.bad()) {
            throw std::runtime_error("File is bad");
        }
        if (ifs.eof()) {
            throw std::runtime_error("File is empty");
        }

        // Reading input file
        uint8_t byte;
        while (ifs.read(reinterpret_cast<char*>(&byte), sizeof (byte))) {
            input_file.push_back(byte);
            ++input_file_size;
        }
        ifs.close();
    } else {
        // Reading input file
        uint8_t byte;
        while (std::cin.read(reinterpret_cast<char*>(&byte), sizeof (byte))) {
            input_file.push_back(byte);
            ++input_file_size;
        }
    }

    std::optional<size_t> BWT_index;
    if (compression_level == CompressionLevel::kSlow) {
        BWT bwt;
        MTF mtf;

        // Encoding by BWT
        auto start = std::chrono::steady_clock::now();
        auto BWT_encoded = bwt.Encode(input_file);
        auto end = std::chrono::steady_clock::now();


        // Encoding by MTF
        start = std::chrono::steady_clock::now();
        auto MTF_encoded = mtf.Encode(BWT_encoded.text);
        end = std::chrono::steady_clock::now();

        BWT_index = BWT_encoded.index;
        input_file = std::move(MTF_encoded);
    }
    Huffman huffman;

    // Encoding by Huffman
    const auto& start = std::chrono::steady_clock::now();
    auto huffman_encoded = huffman.Encode(input_file);
    const auto& end = std::chrono::steady_clock::now();

    return {
        .compressed_file = std::move(huffman_encoded.text),
        .serialized_huffman_tree = Serialize(huffman_encoded.model),
        .alignment = huffman_encoded.alignment,
        .BWT_index = BWT_index
    };
}

void WriteCompressedFileToCout(const std::string& filename) {
    const auto& compressed_file = CompressFile(filename);
//    const auto input_file_size = filesize(filename);

    MetaInfo meta;
    meta.uncompressed_filename = filename;
    meta.uncompressed_filename_length = meta.uncompressed_filename.size();
    meta.uncompressed_size = input_file_size;
    meta.compressed_size = CalculateEncodedSize(compressed_file, filename);

    // Writing: checksum
    uint32_t check_sum = calculate_crc32(meta, compression_level, compressed_file);
    std::cout.write(reinterpret_cast<char*>(&check_sum), sizeof (check_sum));

    // Writing: metainfo
    std::cout.write(reinterpret_cast<const char*>(&meta.compressed_size), sizeof (meta.compressed_size));
    std::cout.write(reinterpret_cast<const char*>(&meta.uncompressed_size), sizeof (meta.uncompressed_size));
    std::cout.write(reinterpret_cast<const char*>(&meta.uncompressed_filename_length), sizeof (meta.uncompressed_filename_length));
    std::cout.write(reinterpret_cast<const char*>(meta.uncompressed_filename.c_str()), meta.uncompressed_filename_length * sizeof (meta.uncompressed_filename[0]));

    // Writing: compression_level
    std::cout.write(reinterpret_cast<char*>(&compression_level), sizeof(compression_level));

    // Writing: serialized_huffman_tree
    for (const auto& bytes : compressed_file.serialized_huffman_tree) {
        std::cout.write(reinterpret_cast<const char*>(&bytes), sizeof(bytes));
    }

    // Writing: alignment
    std::cout.write(reinterpret_cast<const char*>(&compressed_file.alignment), sizeof(compressed_file.alignment));

    // Writing: BWT_index
    if (compressed_file.BWT_index.has_value()) {
        std::cout.write(reinterpret_cast<const char*>(&compressed_file.BWT_index.value()), sizeof(compressed_file.BWT_index.value()));
    }

    // Writing: file
    std::cout.write(
            reinterpret_cast<const char*>(&compressed_file.compressed_file[0]),
            compressed_file.compressed_file.size() * sizeof(compressed_file.compressed_file[0])
    );
}

void WriteCompressedFile(const std::string& filename) {
    if (to_stdout) {
        WriteCompressedFileToCout(filename);
        return;
    }

    const auto& compressed_file = CompressFile(filename);
//    const auto input_file_size = filesize(filename);

    std::ofstream ofs;
    if (keep_input) {
        const auto new_filename = filename + kCompressedFileSuffix;
        ofs.open(new_filename, std::ios::binary);
    } else {
        ofs.open(filename, std::ios::binary);
    }

    if (!ofs.is_open()) {
        throw std::runtime_error("Can't open file");
    }
    if (ofs.bad()) {
        throw std::runtime_error("File is bad");
    }
    if (ofs.eof()) {
        throw std::runtime_error("File is empty");
    }


    MetaInfo meta;
    meta.uncompressed_filename = filename;
    meta.uncompressed_filename_length = meta.uncompressed_filename.size();
    meta.uncompressed_size = input_file_size;
    meta.compressed_size = CalculateEncodedSize(compressed_file, filename);

    // Writing: checksum
    uint32_t check_sum = calculate_crc32(meta, compression_level, compressed_file);
    ofs.write(reinterpret_cast<char*>(&check_sum), sizeof (check_sum));

    // Writing: metainfo
    ofs.write(reinterpret_cast<const char*>(&meta.compressed_size), sizeof (meta.compressed_size));
    ofs.write(reinterpret_cast<const char*>(&meta.uncompressed_size), sizeof (meta.uncompressed_size));
    ofs.write(reinterpret_cast<const char*>(&meta.uncompressed_filename_length), sizeof (meta.uncompressed_filename_length));
    ofs.write(reinterpret_cast<const char*>(meta.uncompressed_filename.c_str()), meta.uncompressed_filename_length * sizeof (meta.uncompressed_filename[0]));

    // Writing: compression_level
    ofs.write(reinterpret_cast<char*>(&compression_level), sizeof(compression_level));

    // Writing: serialized_huffman_tree
    for (const auto& bytes : compressed_file.serialized_huffman_tree) {
        ofs.write(reinterpret_cast<const char*>(&bytes), sizeof(bytes));
    }

    // Writing: alignment
    ofs.write(reinterpret_cast<const char*>(&compressed_file.alignment), sizeof(compressed_file.alignment));

    // Writing: BWT_index
    if (compressed_file.BWT_index.has_value()) {
        ofs.write(reinterpret_cast<const char*>(&compressed_file.BWT_index.value()), sizeof(compressed_file.BWT_index.value()));
    }

    // Writing: file
    ofs.write(
            reinterpret_cast<const char*>(&compressed_file.compressed_file[0]),
            compressed_file.compressed_file.size() * sizeof(compressed_file.compressed_file[0])
    );
    ofs.close();

    if (!keep_input) {
        const auto new_filename = filename + kCompressedFileSuffix;
        std::rename(filename.c_str(), new_filename.c_str());
    }
}

MetaInfo ReadMetaInfo(std::istream& ifs) {
    MetaInfo meta;

    ifs.read(reinterpret_cast<char*>(&meta.compressed_size), sizeof (meta.compressed_size));
    ifs.read(reinterpret_cast<char*>(&meta.uncompressed_size), sizeof (meta.uncompressed_size));
    ifs.read(reinterpret_cast<char*>(&meta.uncompressed_filename_length), sizeof (meta.uncompressed_filename_length));
    meta.uncompressed_filename.resize(meta.uncompressed_filename_length);
    ifs.read(reinterpret_cast<char*>(&meta.uncompressed_filename[0]), meta.uncompressed_filename_length * sizeof (char));

    return meta;
}

std::vector<uint8_t> DecompressFromStdin() {
    auto& ifs = std::cin;

    // Reading: checksum
    uint32_t check_sum;
    ifs.read(reinterpret_cast<char*>(&check_sum), sizeof (check_sum));


    // Reading: meta_info
    ReadMetaInfo(ifs);


    // Reading: compression_level
    CompressionLevel level;
    ifs.read(reinterpret_cast<char*>(&level), sizeof (level));


    // Reading: serialized_huffman_tree
    auto serialized_huffman_tree = Deserialize(ifs);


    // Reading: alignment
    uint8_t alignment;
    ifs.read(reinterpret_cast<char*>(&alignment), sizeof (alignment));


    //  Reading: BWT_index
    std::optional<size_t> BWT_index;
    if (level == CompressionLevel::kSlow) {
        size_t index;
        ifs.read(reinterpret_cast<char*>(&index), sizeof (index));
        BWT_index = index;
    }


    // Reading: encoded_file
    std::vector<uint8_t> encoded_file;
    uint8_t byte;
    while (ifs.read(reinterpret_cast<char*>(&byte), sizeof (byte))) {
        encoded_file.push_back(byte); // Вот здесь можно сначала узанть размер файла, чтобы не было лишних реалокаций
    }


    // Decoding by Huffman
    Huffman huffman;
    Huffman::Encoded huffman_encoded{
            .model = std::move(serialized_huffman_tree),
            .text = std::move(encoded_file),
            .alignment = alignment
    };
    auto start = std::chrono::steady_clock::now();
    auto decoded_file = huffman.Decode(huffman_encoded);
    auto end = std::chrono::steady_clock::now();


    if (level == CompressionLevel::kSlow) {
        BWT bwt;
        MTF mtf;

        // Decoding by MTF
        start = std::chrono::steady_clock::now();
        auto mtf_decoded = mtf.Decode(decoded_file);
        end = std::chrono::steady_clock::now();

        // Decoding by BWT
        start = std::chrono::steady_clock::now();
        auto bwt_decoded = bwt.Decode({
                                              .text = std::move(mtf_decoded), // по идее, без мува тоже копирования не будет
                                              .index = BWT_index.value()
                                      });
        end = std::chrono::steady_clock::now();
        decoded_file = std::move(bwt_decoded);
    }

    return decoded_file;
}


std::vector<uint8_t> DecompressFile(const std::string& filename) {
    std::ifstream ifs(filename, std::ios::binary);
    if (!ifs.is_open()) {
        throw std::runtime_error("Can't open file");
    }
    if (ifs.bad()) {
        throw std::runtime_error("File is bad");
    }
    if (ifs.eof()) {
        throw std::runtime_error("File is empty");
    }


    // Reading: checksum
    uint32_t check_sum;
    ifs.read(reinterpret_cast<char*>(&check_sum), sizeof (check_sum));


    // Reading: meta_info
    ReadMetaInfo(ifs);


    // Reading: compression_level
    CompressionLevel level;
    ifs.read(reinterpret_cast<char*>(&level), sizeof (level));


    // Reading: serialized_huffman_tree
    auto serialized_huffman_tree = Deserialize(ifs);


    // Reading: alignment
    uint8_t alignment;
    ifs.read(reinterpret_cast<char*>(&alignment), sizeof (alignment));


    //  Reading: BWT_index
    std::optional<size_t> BWT_index;
    if (level == CompressionLevel::kSlow) {
        size_t index;
        ifs.read(reinterpret_cast<char*>(&index), sizeof (index));
        BWT_index = index;
    }


    // Reading: encoded_file
    std::vector<uint8_t> encoded_file;
    uint8_t byte;
    while (ifs.read(reinterpret_cast<char*>(&byte), sizeof (byte))) {
        encoded_file.push_back(byte); // Вот здесь можно сначала узанть размер файла, чтобы не было лишних реалокаций
    }


    // Decoding by Huffman
    Huffman huffman;
    Huffman::Encoded huffman_encoded{
        .model = std::move(serialized_huffman_tree),
        .text = std::move(encoded_file),
        .alignment = alignment
    };
    auto start = std::chrono::steady_clock::now();
    auto decoded_file = huffman.Decode(huffman_encoded);
    auto end = std::chrono::steady_clock::now();


    if (level == CompressionLevel::kSlow) {
        BWT bwt;
        MTF mtf;

        // Decoding by MTF
        start = std::chrono::steady_clock::now();
        auto mtf_decoded = mtf.Decode(decoded_file);
        end = std::chrono::steady_clock::now();

        // Decoding by BWT
        start = std::chrono::steady_clock::now();
        auto bwt_decoded = bwt.Decode({
            .text = std::move(mtf_decoded), // по идее, без мува тоже копирования не будет
            .index = BWT_index.value()
        });
        end = std::chrono::steady_clock::now();
        decoded_file = std::move(bwt_decoded);
    }
    
    return decoded_file;
}

void WriteDecompressedFile(const std::string& filename) {
    if (!filename.ends_with(kCompressedFileSuffix) && filename != "-") {
        throw std::runtime_error("Filename must ends with '.az'");
    }

    std::vector<uint8_t> bytes;
    if (from_stdin) {
        bytes = DecompressFromStdin();
    } else {
        bytes = DecompressFile(filename);
    }

    if (!to_stdout) {
        const auto& new_filename = filename.substr(0, filename.size() - std::strlen(kCompressedFileSuffix));

        if (!keep_input) {
            std::rename(filename.c_str(), new_filename.c_str());
        }


        std::ofstream ofs(new_filename, std::ios::binary);
        if (!ofs.is_open()) {
            throw std::runtime_error("Can't open file");
        }
        if (ofs.bad()) {
            throw std::runtime_error("File is bad");
        }
        if (ofs.eof()) {
            throw std::runtime_error("File is empty");
        }

        ofs.write(
            reinterpret_cast<const char*>(&bytes[0]),
            bytes.size() * sizeof(bytes[0])
        );
    } else {
        std::cout.write(
            reinterpret_cast<const char*>(&bytes[0]),
            bytes.size() * sizeof(bytes[0])
        );
    }
}


void print_help() {
    std::cout << "Usage: azip [options] [files]\n"
              << "Options:\n"
              << "  -         Read from standard input.\n"
              << "  -c        Write output to standard output.\n"
              << "  -d        Decompress the input file.\n"
              << "  -k        Keep input files after processing.\n"
              << "  -l        List information about compressed files.\n"
              << "  -r        Process files recursively (if directories are specified).\n"
              << "  -t        Test the integrity of compressed files.\n"
              << "  -1        Use fast compression (less compression).\n"
              << "  -9        Use best compression (slower).\n"
              << "  -h        Display this help message.\n";
}

void PrintFileMeta(const std::string& filename) {
    int32_t checksum;
    if (!from_stdin) {
        std::ifstream ifs(filename, std::ios::binary);
        ifs.read(reinterpret_cast<char*>(&checksum), sizeof (checksum));
        auto meta = ReadMetaInfo(ifs);
        auto ratio = (1.L - ((double)  meta.compressed_size / meta.uncompressed_size)) * 100;
        std::cout << fmt::format("{:>20} {:>20} {:>19.1f}% {:>40}", meta.compressed_size, meta.uncompressed_size, ratio, meta.uncompressed_filename) << std::endl;
    } else {
        auto& ifs = std::cin;
        ifs.read(reinterpret_cast<char*>(&checksum), sizeof (checksum));
        auto meta = ReadMetaInfo(ifs);
        auto ratio = (1.L - ((double)  meta.compressed_size / meta.uncompressed_size)) * 100;
        std::cout << fmt::format("{:>20} {:>20} {:>19.1f}% {:>40}", meta.compressed_size, meta.uncompressed_size, ratio, meta.uncompressed_filename) << std::endl;
    }

}

void TestIntegrity(const std::string& filename) {
    if (!from_stdin) {
        std::ifstream ifs(filename, std::ios::binary);
        uint32_t expected_crc;
        ifs.read(reinterpret_cast<char*>(&expected_crc), sizeof (expected_crc));
        uint32_t actual_crc = calculate_crc32(ifs);

        if (expected_crc != actual_crc) {
            throw std::runtime_error(fmt::format("Файл {} битый", filename));
        }
    } else {
        auto& ifs = std::cin;
        uint32_t expected_crc;
        ifs.read(reinterpret_cast<char*>(&expected_crc), sizeof (expected_crc));
        uint32_t actual_crc = calculate_crc32(ifs);

        if (expected_crc != actual_crc) {
            throw std::runtime_error(fmt::format("Файл {} битый", filename));
        }
    }

}


// Функция для обработки флагов и файлов
void process_files(const std::vector<std::string>& files) {
    if (list_info) {
        std::cout << fmt::format("{:>20} {:>20} {:>20} {:>40}", "compressed", "uncompressed", "ratio", "uncompressed_name") << std::endl;
    }
    for (const auto& file : files) {
        if (list_info) {
            PrintFileMeta(file);
            continue;
        }

        if (test_integrity) {
            TestIntegrity(file);
            continue;
        }

        if (decompress) {
            WriteDecompressedFile(file);
        } else {
            WriteCompressedFile(file);
        }

    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        print_help();
        return 1;
    }

    std::vector<std::string> files;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-c") {
            to_stdout = true;
        } else if (arg == "-d") {
            decompress = true;
        } else if (arg == "-k") {
            keep_input = true;
        } else if (arg == "-l") {
            list_info = true;
        } else if (arg == "-r") {
            recursive = true;
        } else if (arg == "-t") {
            test_integrity = true;
        } else if (arg == "-1") {
            compression_level = CompressionLevel::kFast;
        } else if (arg == "-9") {
            compression_level = CompressionLevel::kSlow;
        } else if (arg == "-h") {
            print_help();
            return 0;
        } else if (arg == "-") {
            from_stdin = true;
            files.push_back("-");
        } else if (arg[0] == '-' && arg.size() > 1) {
            std::cerr << "Unknown option: " << arg << "\n";
            print_help();
            return 1;
        } else {
            files.push_back(arg);
        }
    }

    if (files.empty()) {
        std::cerr << "No files specified. Use '-' for standard input.\n";
        return 1;
    }

    process_files(files);

    return 0;
}
