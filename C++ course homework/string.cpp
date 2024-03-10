#include "string.hpp"

#include <iostream>
#include <cstring>
#include <algorithm>

static const size_t DEFAULT_STRING_CAPACITY = 15;

String::String(size_t n) : 
    arr(static_cast<char*>(new char[n + 1])),
    sz(n),
    cap(n + 1)
    {
        arr[sz] = '\0';
    }


String::String() : 
    arr(static_cast<char*>(new char[DEFAULT_STRING_CAPACITY + 1])),
    sz(0),
    cap(DEFAULT_STRING_CAPACITY + 1) 
    {
        arr[sz] = '\0';
    }

String::String(const char* c_str) : String(strlen(c_str)) {
    std::copy(c_str, c_str + sz, arr);
}

String::String(size_t n, char c) : String(n) {
    std::fill(arr, arr + sz, c);
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

char* String::data() {
    return arr;
}

const char* String::data() const {
    return arr;
}


std::ostream& operator<<(std::ostream& os, const String& str) {
    for (size_t i = 0; i < str.size(); ++i) {
        os << str.data()[i];
    }
    return os;
}


int main() {

    String str1;

    std::cout << str1.length() << std::endl;
    std::cout << str1.size() << std::endl;
    std::cout << str1.capacity() << std::endl;
    std::cout << str1 << '|' << std::endl;
    std::cout << "____________________________________" << std::endl;


    String str2("abobabeba");

    std::cout << str2.length() << std::endl;
    std::cout << str2.size() << std::endl;
    std::cout << str2.capacity() << std::endl;
    std::cout << str2 << '|' << std::endl;
    std::cout << "____________________________________" << std::endl;


    String str3(10, 'a');

    std::cout << str3.length() << std::endl;
    std::cout << str3.size() << std::endl;
    std::cout << str3.capacity() << std::endl;
    std::cout << str3 << '|' << std::endl;
    std::cout << "____________________________________" << std::endl;

}

