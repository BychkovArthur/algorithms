#pragma once

#include <cstdint>
#include <cstddef>

#include <array>

#include <fstream>
#include <iostream>


class BitIO {
private:

    constexpr static size_t kBufferSize = 16 * 1024;
    constexpr static uint8_t kByteSize = 8;

    std::array<uint8_t, kBufferSize> output_buffer_;
    size_t bytes_in_output_buffer_ = 0;

    uint8_t input_byte_ = 0x00;
    size_t bits_readed_ = 0;
    bool first_byte_readed_ = false;


    uint8_t output_byte_ = 0x00;
    uint8_t bits_filled_ = 0;

    std::fstream stream_;

    void FlushOutputBuffer() {
        if (bytes_in_output_buffer_ > 0) {
            stream_.write(reinterpret_cast<char*>(&output_buffer_[0]), bytes_in_output_buffer_);
            stream_.flush();
        }
        bytes_in_output_buffer_ = 0;
    }

    void SetBitToZero(const size_t num) {
        output_byte_ = output_byte_ & (~( ((uint8_t)1) << ( kByteSize - num - 1 ) ));
    }

    void SetBitToOne(const size_t num) {
        output_byte_ = output_byte_ | ( ((uint8_t)1) << ( kByteSize - num - 1 ) ); 
    }

    uint8_t GetBit(const size_t num) {
        return (input_byte_ >> (kByteSize - 1 - num)) & 0b00000001;
    }

    void MoveByteToOutputBuffer() {
        for (size_t bit_number = bits_filled_; bit_number < kByteSize; ++bit_number) {
            SetBitToZero(bit_number);
        }

        output_buffer_[bytes_in_output_buffer_++] = output_byte_;
        bits_filled_ = 0;
    }

public:
    enum class Bit : uint8_t {
        kZero = 0,
        kOne = 1,
    };

    BitIO(std::fstream&& stream) : output_buffer_{}, stream_(std::move(stream)) {}

    void Write(const Bit bit) {
        if (bytes_in_output_buffer_ == kBufferSize) {
            FlushOutputBuffer();
        }
        if (bits_filled_ == kByteSize) {
            MoveByteToOutputBuffer();
        }

        if (bit == Bit::kZero) {
            SetBitToZero(bits_filled_);
        } else {
            SetBitToOne(bits_filled_);
        }
        ++bits_filled_;
    }

    Bit Read() {
        if (!first_byte_readed_) {
            stream_ >> input_byte_;
            first_byte_readed_ = true;
        }
        if (bits_readed_ == kByteSize) {
            stream_ >> input_byte_;
            bits_readed_ = 0;
        }

        const auto bit = GetBit(bits_readed_++);
        return bit == 0 ? Bit::kZero : Bit::kOne;
    }

    bool Eof() {
        if (!first_byte_readed_) {
            stream_ >> input_byte_;
            first_byte_readed_ = true;
        }
        if (bits_readed_ == kByteSize) {
            stream_ >> input_byte_;
            bits_readed_ = 0;
        }

        return stream_.eof();
    }

    void FlushOutput() {
        FlushOutputBuffer();
        if (bits_filled_ > 0) {
            MoveByteToOutputBuffer();
            FlushOutputBuffer();
        }
    }

    void Close() {
        stream_.close();
    }

    ~BitIO() {
        FlushOutput();
    }

};