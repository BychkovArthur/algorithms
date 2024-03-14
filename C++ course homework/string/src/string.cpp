#include "../include/string.hpp"

#include <iostream>
#include <cstring>
#include <algorithm>

static const size_t DEFAULT_STRING_CAPACITY = 15;

String::String(size_t sz, size_t cap) : 
    arr(static_cast<char*>(new char[cap])),
    sz(sz),
    cap(cap)
    {
        arr[sz] = '\0';
    }

String::String(size_t n) : String(n, n + 1) {}

String::String() : String(0, DEFAULT_STRING_CAPACITY + 1) {}

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

const char& String::operator[](size_t ind) const {
    return arr[ind];
}

char& String::front() {
    return arr[0];
}

const char& String::front() const {
    return arr[0];
}

char& String::back() {
    return arr[sz - 1];
}

const char& String::back() const {
    return arr[sz - 1];
}

void String::push_back(char c) {
    if (sz == cap - 1) {
        cap *= 2;
        realloc_to_new_cap();
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
    size_t new_size = sz + other.sz;
    bool cap_was_updated = false;

    while (cap - 1 < new_size) {
        cap *= 2;
        cap_was_updated = true;
    }

    if (cap_was_updated) {
        realloc_to_new_cap();
    }

    std::copy(other.arr, other.arr + other.sz + 1, arr + sz);
    sz += other.sz;
    return *this;
}

String String::substr(size_t start, size_t count) {
    if (start > sz) {
        throw std::out_of_range("Invalid start");
    }
    size_t new_string_size = std::min(sz, start + count) - start;
    String result(new_string_size);
    std::copy(arr + start, arr + start + new_string_size, result.arr);
    result[result.sz] = '\0';
    return result;
}

size_t String::search(const String& substr, bool is_left_search) {
    size_t substr_len = substr.length();

    if (!substr_len) {
        return is_left_search ? 0 : sz;
    }

    if (substr_len > sz) {
        return sz;
    }

    ssize_t start = is_left_search ? 0 : sz - substr_len;
    ssize_t end = is_left_search ? sz - substr_len + 1 : -1;
    ssize_t step = is_left_search ? 1 : -1;

    for (ssize_t i = start; i != end; i += step) {
        if (!std::memcmp(arr + i, substr.data(), substr_len)) {
            return i;
        }
    }
    return sz;
}

size_t String::find(const String& substr) {
    return search(substr, true);
}

size_t String::rfind(const String& substr) {
    return search(substr, false);
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
    return arr;
}

void String::clear() {
    sz = 0;
    arr[sz] = '\0';
}

void String::shrink_to_fit() {
    if (sz < cap - 1) {
        cap = sz + 1;
        realloc_to_new_cap();
    }
}

bool operator<(const String& str1, const String& str2) {
    return std::memcmp(str1.data(), str2.data(), std::min(str1.size(), str2.size()) + 1) < 0;
}

bool operator>(const String& str1, const String& str2) {
    return str2 < str1;
}

bool operator<=(const String& str1, const String& str2) {
    return !(str1 > str2);
}

bool operator>=(const String& str1, const String& str2) {
    return !(str1 < str2);
}

bool operator==(const String& str1, const String& str2) {
    return str1.size() == str2.size() && (std::memcmp(str1.data(), str2.data(), std::min(str1.size(), str2.size())) == 0);
}

bool operator!=(const String& str1, const String& str2) {
    return !(str1 == str2);
}

bool operator==(const char* str1, const String& str2) {
    return str2.size() == strlen(str1) && (std::memcmp(str1, str2.data(), str2.size()) == 0);
}

bool operator==(const String& str1, const char* str2) {
    return str2 == str1;
}

std::ostream& operator<<(std::ostream& os, const String& str) {
    for (size_t i = 0; i < str.size(); ++i) {
        os << str.data()[i];
    }
    return os;
}

std::istream& operator>>(std::istream& is, String& str) {
    char c;
    bool string_found = false;
    str.clear();

    while (is.get(c)) {
        if (c == '\n') {
            break;
        }

        if (!string_found && (c == '\t' || c == ' ')) {
            continue;
        }
        
        string_found = true;
        if (c != ' ' && c != '\t') {
            str.push_back(c);
        } else {
            break;
        }
    }
    return is;
}

void String::swap(String& other) {
    std::swap(arr, other.arr);
    std::swap(cap, other.cap);
    std::swap(sz, other.sz);
}

void String::realloc_to_new_cap() {
    char* new_arr = static_cast<char*>(new char[cap]);
    std::copy(arr, arr + sz + 1, new_arr);
    std::swap(arr, new_arr);
    delete[] new_arr;
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

String operator+(const String& str1, const String& str2) {
    String sum(str1);
    sum += str2;
    return sum;
}