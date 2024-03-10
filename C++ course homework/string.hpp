#pragma once
#include <iostream>

class String {
private:
    char* arr;
    size_t sz;
    size_t cap;

    explicit String(size_t n);
public:
    String();
    String(const char* c_str);
    String(size_t n, char c);


    size_t size() const;
    size_t length() const;
    size_t capacity() const;
    char* data();
    const char* data() const;

};