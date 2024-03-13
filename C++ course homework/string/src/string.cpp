#include "string.hpp"

#include <iostream>
#include <cstring>
#include <algorithm>

static const size_t DEFAULT_STRING_CAPACITY = 15;

String::String(size_t sz, size_t cap) : 
    arr(static_cast<char*>(new char[cap + 1])),
    sz(sz),
    cap(cap + 1)
    {
        arr[sz] = '\0';
    }

String::String(size_t n) : String(n, n) {}

String::String() : String(0, DEFAULT_STRING_CAPACITY) {}

String::String(const char* c_str) : String(strlen(c_str)) {
    std::copy(c_str, c_str + sz, arr);
}

String::String(size_t n, char c) : String(n) {
    std::fill(arr, arr + sz, c);
}

String::String(const String& other) : String(other.sz, other.cap) {
    std::copy(other.arr, other.arr + sz, arr);
}

String::~String() {
    delete[] arr;
}

String& String::operator=(const String& other) {
    if (this != &other) {
        String copy(other);
        swap(copy);
    }
    return *this;
}

char& String::operator[](size_t ind) {
    return arr[ind];
}

// const char& String::operator[](size_t ind) const {
//     return static_cast<const char>(arr[ind]);
// }

char& String::front() {
    return arr[0];
}

// const char& String::front() const {
//     return static_cast<const char>(arr[0]);
// }

char& String::back() {
    return arr[sz - 1];
}

// const char& String::back() const {
//     return static_cast<const char>(arr[sz - 1]);
// }


void String::push_back(char c) {
    if (sz == cap - 1) {
        cap *= 2;
        char* new_arr = static_cast<char*>(new char[cap]);
        std::copy(arr, arr + sz, new_arr);
        delete[] arr;
        arr = new_arr;
    }
    arr[sz++] = c;
}

void String::pop_back() {
    arr[--sz] = '\0';
}

String& String::operator+=(char c) {
    push_back(c);
    return *this;
}


String& String::operator+=(const String& other) {
    
}



size_t String::size() const {
    return sz;
}

size_t String::length() const {
    return sz;
}


/*
    capacity тут без учёта '\0'
    Т.е. capacity означает, каков максимальный
    размер полезных данных можно хранить.
*/
size_t String::capacity() const {
    return cap - 1;
}

bool String::empty() const {
    return sz == 0;
}


char* String::data() {
    return arr;
}

const char* String::data() const {
    return static_cast<const char*>(arr);
}

void String::clear() {
    sz = 0;
    arr[sz] = '\0';
}


bool String::operator<(const String& other) const {
    return std::memcmp(arr, other.arr, std::min(sz, other.sz) + 1) < 0;
}

bool String::operator>(const String& other) const {
    return other < *this;
}

bool String::operator<=(const String& other) const {
    return !(*this > other);
}

bool String::operator>=(const String& other) const {
    return !(*this < other);
}

bool String::operator==(const String& other) const {
    return sz == other.sz && (std::memcmp(arr, other.arr, std::min(sz, other.sz)) == 0);
}

bool String::operator!=(const String& other) const {
    return !(*this == other);
}


std::ostream& operator<<(std::ostream& os, const String& str) {
    for (size_t i = 0; i < str.size(); ++i) {
        os << str.data()[i];
    }
    return os;
}

void String::swap(String& other) {
    std::swap(arr, other.arr);
    std::swap(cap, other.cap);
    std::swap(sz, other.sz);
}

String operator+(char c, const String& str) {
    String sum(str.size() + 1);
    sum[0] = c;
    std::copy(str.data(), str.data() + str.size(), sum.data() + 1);
    return sum;
}

String operator+(const String& str, char c) {
    String sum(str.size() + 1);
    std::copy(str.data(), str.data() + str.size(), sum.data());
    sum[sum.size() - 1] = c;
    return sum;
}

// String operator+(const String& str1, const String& str2) {
//     return;
// }


