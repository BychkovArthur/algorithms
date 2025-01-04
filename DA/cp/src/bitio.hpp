#pragma once

#include <cstdint>
#include <cstddef>

#include <vector>

#include <fstream>
#include <iostream>


class BitIO {
private:

    constexpr static uint8_t kByteSize = 8;

    std::vector<uint8_t>& output_;

    size_t current_byte = 0;
    size_t bits_readed_ = 0;


    uint8_t output_byte_ = 0x00;
    uint8_t bits_filled_ = 0;

    std::fstream stream_;

    void SetBitToZero(const size_t num) {
        output_byte_ = output_byte_ & (~( ((uint8_t)1) << ( kByteSize - num - 1 ) ));
    }

    void SetBitToOne(const size_t num) {
        output_byte_ = output_byte_ | ( ((uint8_t)1) << ( kByteSize - num - 1 ) ); 
    }

    uint8_t GetBit(const size_t num) {
        return (output_[current_byte] >> (kByteSize - 1 - num)) & 0b00000001;
    }

    void MoveByteToOutput() {
        for (size_t bit_number = bits_filled_; bit_number < kByteSize; ++bit_number) {
            SetBitToZero(bit_number);
        }

        output_.push_back(output_byte_);
        bits_filled_ = 0;
    }

public:
    enum class Bit : uint8_t {
        kZero = 0,
        kOne = 1,
    };

    BitIO(std::vector<uint8_t>& output) : output_(output) {}

    void Write(const Bit bit) {
        if (bits_filled_ == kByteSize) {
            MoveByteToOutput();
        }

        if (bit == Bit::kZero) {
            SetBitToZero(bits_filled_);
        } else {
            SetBitToOne(bits_filled_);
        }
        ++bits_filled_;
    }

    Bit Read() {
        if (bits_readed_ == kByteSize) {
            ++current_byte;
            bits_readed_ = 0;
        }

        const auto bit = GetBit(bits_readed_++);
        return bit == 0 ? Bit::kZero : Bit::kOne;
    }

    bool Eof() {
        if (bits_readed_ == kByteSize) {
            ++current_byte;
            bits_readed_ = 0;
        }

        return current_byte == output_.size();
    }

    void FlushOutput() {
        if (bits_filled_ > 0) {
            MoveByteToOutput();
        }
    }

    ~BitIO() {
        FlushOutput();
    }

};