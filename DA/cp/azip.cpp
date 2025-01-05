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

struct MetaInfo {
    size_t compressed_size;
    size_t uncompressed_size;
    uint8_t uncompressed_name[50];
};

enum class CompressionLevel : uint8_t {
    kFast = 0,
    kSlow = 1,
};

struct FastAlgorithmAdditionalInfo {
    std::vector<uint8_t> serialized_model;
    uint8_t alignment;
};

struct SlowAlgorithmAdditionalInfo {
    std::vector<uint8_t> serialized_model;
    uint8_t alignment;
    size_t BWT_index;
};

struct CompressedFile {
    std::vector<uint8_t> compressed_file;
    std::vector<int16_t> serialized_huffman_tree;
    uint8_t alignment;
    std::optional<size_t> BWT_index;
};

bool to_stdout = false;
bool decompress = false;
bool keep_input = false;
bool list_info = false;
bool recursive = false;
bool test_integrity = false;
CompressionLevel compression_level = CompressionLevel::kSlow;

CompressedFile CompressFile(const std::string& filename) {
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
    std::vector<uint8_t> input_file;
    uint8_t byte;
    while (ifs.read(reinterpret_cast<char*>(&byte), sizeof (byte))) {
        input_file.push_back(byte);
    }
    ifs.close();


    std::optional<size_t> BWT_index;
    if (compression_level == CompressionLevel::kSlow) {
        BWT bwt;
        MTF mtf;


        // Encoding by BWT
        std::cout << "Started: BWT encoding" << std::endl;
        auto start = std::chrono::steady_clock::now();
        auto BWT_encoded = bwt.Encode(input_file);
        auto end = std::chrono::steady_clock::now();
        std::cout << "Encoded: BWT; Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;


        // Encoding by MTF
        std::cout << "Started: MTF encoding" << std::endl;
        start = std::chrono::steady_clock::now();
        auto MTF_encoded = mtf.Encode(BWT_encoded.text);
        end = std::chrono::steady_clock::now();
        std::cout << "Encoded: MTF; Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;

        BWT_index = BWT_encoded.index;
        input_file = std::move(MTF_encoded);
    }
    Huffman huffman;

    // Encoding by Huffman
    std::cout << "Started: Huffman encoding" << std::endl;
    const auto& start = std::chrono::steady_clock::now();
    auto huffman_encoded = huffman.Encode(input_file);
    const auto& end = std::chrono::steady_clock::now();
    std::cout << "Encoded: Huffman; Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;

    return {
        .compressed_file = std::move(huffman_encoded.text),
        .serialized_huffman_tree = Serialize(huffman_encoded.model),
        .alignment = huffman_encoded.alignment,
        .BWT_index = BWT_index
    };
}

void WriteCompressedFile(const std::string& filename) {
    std::ofstream ofs("aboba.bin", std::ios::binary);
    if (!ofs.is_open()) {
        throw std::runtime_error("Can't open file");
    }
    if (ofs.bad()) {
        throw std::runtime_error("File is bad");
    }
    if (ofs.eof()) {
        throw std::runtime_error("File is empty");
    }

    // TODO: Writing: metainfo + checksum

    // TODO: Writing: checksum + metainfo


    // Writing: compression_level
    ofs.write(reinterpret_cast<char*>(&compression_level), sizeof(compression_level));
    std::cout << "Wrote: compression_level: " << (int)compression_level << std::endl;

    // Writing: serialized_huffman_tree
    const auto& compressed_file = CompressFile(filename);
    for (const auto& bytes : compressed_file.serialized_huffman_tree) {
        ofs.write(reinterpret_cast<const char*>(&bytes), sizeof(bytes));
    }
    std::cout << "Wrote: serialized_huffman_tree" << std::endl;

    // Writing: alignment
    ofs.write(reinterpret_cast<const char*>(&compressed_file.alignment), sizeof(compressed_file.alignment));
    std::cout << "Wrote: alignment = " << (int)compressed_file.alignment << std::endl;

    // Writing: BWT_index
    if (compressed_file.BWT_index.has_value()) {
        ofs.write(reinterpret_cast<const char*>(&compressed_file.BWT_index.value()), sizeof(compressed_file.BWT_index.value()));
        std::cout << "Wrote:  BWT_index = " << compressed_file.BWT_index.value() << std::endl;
    }

    // Writing: file
    ofs.write(
            reinterpret_cast<const char*>(&compressed_file.compressed_file[0]),
            compressed_file.compressed_file.size() * sizeof(compressed_file.compressed_file[0])
    );
    std::cout << "Wrote: " << compressed_file.compressed_file.size() << " bytes of file" << std::endl;
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


    // TODO: Reading: checksum


    // TODO: Reading: meta_info


    // Reading: compression_level
    CompressionLevel level;
    ifs.read(reinterpret_cast<char*>(&level), sizeof (level));
    std::cout << "Read: compression_level = " << (int)level << std::endl;


    // Reading: serialized_huffman_tree
    auto serialized_huffman_tree = Deserialize(ifs);
    std::cout << "Read: serialized_huffman_tree" << std::endl;


    // Reading: alignment
    uint8_t alignment;
    ifs.read(reinterpret_cast<char*>(&alignment), sizeof (alignment));
    std::cout << "Read: alignment = " << (int)alignment << std::endl;


    //  Reading: BWT_index
    std::optional<size_t> BWT_index;
    if (level == CompressionLevel::kSlow) {
        size_t index;
        ifs.read(reinterpret_cast<char*>(&index), sizeof (index));
        BWT_index = index;
        std::cout << "Read: BWT_index = " << index << std::endl;
    }


    // Reading: encoded_file
    std::vector<uint8_t> encoded_file;
    uint8_t byte;
    while (ifs.read(reinterpret_cast<char*>(&byte), sizeof (byte))) {
        encoded_file.push_back(byte); // Вот здесь можно сначала узанть размер файла, чтобы не было лишних реалокаций
    }
    std::cout << "Read: encoded_file" << std::endl;


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
    std::cout << "Decoded: Huffman; Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;


    if (level == CompressionLevel::kSlow) {
        BWT bwt;
        MTF mtf;

        // Decoding by MTF
        start = std::chrono::steady_clock::now();
        auto mtf_decoded = mtf.Decode(decoded_file);
        end = std::chrono::steady_clock::now();
        std::cout << "Decoded: MTF; Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;

        // Decoding by BWT
        start = std::chrono::steady_clock::now();
        auto bwt_decoded = bwt.Decode({
            .text = std::move(mtf_decoded), // по идее, без мува тоже копирования не будет
            .index = BWT_index.value()
        });
        end = std::chrono::steady_clock::now();
        std::cout << "Decoded: BWT; Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << std::endl;
        decoded_file = std::move(bwt_decoded);
    }
    
    return decoded_file;
}

void WriteDecompressedFile(const std::string& filename) {
    const auto& bytes = DecompressFile(filename);

    std::ofstream ofs("decoded.mkv", std::ios::binary);
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
    std::cout << "File decompressed. Size = " << bytes.size() << " bytes" << std::endl;
}


void print_help() {
    std::cout << "Usage: azip [options] [files]\n"
              << "Options:\n"
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

// Функция для обработки флагов и файлов
void process_files(const std::vector<std::string>& files) {
    for (const auto& file : files) {
        if (file == "-") {
            std::cout << "Processing standard input...\n";
            // Обработка stdin
        } else {
            std::cout << "Processing file: " << file << "\n";
            
            if (decompress) {
                std::cout << "Decompressing " << file << "...\n";
                WriteDecompressedFile("aboba.bin");
            } else {
                std::cout << "Compressing " << file << " with level " << (compression_level == CompressionLevel::kSlow ? "slow" : "fast") << "...\n";
                WriteCompressedFile(file);
            }

            if (list_info) {
                std::cout << "Listing information about: " << file << "\n";
                // Добавьте логику вывода информации о файле
            }

            if (test_integrity) {
                std::cout << "Testing integrity of: " << file << "\n";
                // Добавьте логику проверки целостности
            }

            if (!keep_input) {
                std::cout << "Removing input file: " << file << "\n";
                // Удаление исходного файла
            }
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
