#include <iostream>
#include <stdio.h>
#include <cstring>
#include <cassert>
#include <algorithm>

class String {
private:
  char* str;
  size_t sz, cap;

public:
  explicit String(size_t n) : str(static_cast<char *>(malloc(n + 1))), sz(n), cap(n + 1) {
    str[sz] = '\0';
  }

  String(): String(static_cast<size_t>(0)) {
  }

  void swap(String& other) {
    std::swap(sz, other.sz);
    std::swap(cap, other.cap);
    std::swap(str, other.str);
  }

  String(const String& other): String(other.sz) {
    std::copy(other.str, other.str + sz, str);
  }

  String& operator=(String other) {
    swap(other);
    return *this;
  }

  ~String() {
    free(str);
  }

  explicit String(size_t n, char ch): String(n) {
    std::fill(str, str + n, ch);
  }

  String(char ch) : String(static_cast<size_t>(1)) {
    str[0] = ch;
  }

  String(const char* instr) {
    int curindex = strlen(instr);

    //str = new char[curindex + 1];
    str = static_cast<char*>(malloc(curindex + 1));
    sz = curindex;
    cap = sz + 1;
    std::copy(instr, instr + curindex, str);
    str[sz] = '\0';
  }

  char& operator[](int index) {
    return str[index];
  }

  const char& operator[](int index) const {
    return str[index];
  }

  size_t length() const {
    return sz;
  }

  size_t size() const {
    return sz;
  }

  size_t capacity() const {
    return cap - 1;
  }

  void push_back(char ch) {
    if (cap - 1 > sz) {
      str[sz++] = ch;
      str[sz] = '\0';
      return;
    }
    cap = (cap * 2) + 1;
    str = static_cast<char *>(realloc(str, cap));
    str[sz++] = ch;
    str[sz] = '\0';
  }

  void pop_back() {
    sz--;
    str[sz] = '\0';
  }

  char& front() {
    return str[0];
  }

  char& back() {
    return str[sz - 1];
  }

  const char& front() const {
    return str[0];
  }

  const char& back() const {
    return str[sz - 1];
  }

  String& operator+=(const String& other) {
    if (str == nullptr) {
      *this = other;
      return *this;
    }
    int start = sz;
    while (cap - 1 < other.sz + sz) {
      cap = 2 * cap + 1;
    }
    str = static_cast<char *>(realloc(str, cap));
    sz += other.sz;
    std::copy(other.str, other.str + other.sz, str + start);
    str[sz] = '\0';
    return *this;
  }

  void clear() {
    sz = 0;
    str[sz] = '\0';
  }
private:
  size_t search(const String& other, size_t start, size_t finish, int step) const {
    for (size_t i = start; i != finish; i += step) {
      if (memcmp(str + i, other.str, other.sz) == 0) {
        return i;
      }
    }
    return sz;
  }
public:
  size_t find(const String& other) const {
    if (sz == 0 || other.sz == 0 || sz < other.sz) {
      return sz;
    }
    return search(other, 0, sz - other.sz + 1, 1);
  }

  size_t rfind(const String& other) const {
    if (sz < other.sz || other.sz == 0)
      return sz;
    return search(other, sz - other.sz, 0, -1);
  }

  String substr(int start, size_t cnt) const {
    cnt = std::min(cnt, sz - start);
    String result(cnt);
    std::copy(str + start, str + start + cnt, result.str);
    return result;
  }

  bool empty() const {
    return sz == 0;
  }

  void shrink_to_fit() {
    String newstring(sz);
    std::copy(str, str + sz, newstring.str);
    swap(newstring);
  }

  const char* data() const {
    return str;
  }

  char* data() {
    return str;
  }
};

String operator+(const String& a, const String& b) {
  String result(a);
  result += b;
  return result;
}

String operator+(char a, const String& b) {
  String result(a);
  result += b;
  return result;
}

String operator+(const String& a, char b) {
  String result(a);
  result += String(b);
  return result;
}
 
bool operator==(const String& a, const String& b) {
  if (a.size() != b.size()) {
    return false;
  }
  int val = memcmp(a.data(), b.data(), a.size());
  if (val == 0)
    return true;
  return false;
}

bool operator!=(const String& a, const String& b) {
  return !operator==(a, b);
}

bool operator<(const String& a, const String& b) {
  int val = memcmp(a.data(), b.data(), std::min(a.size(), b.size()));
  if (val < 0) {
    return true;
  } else if (val > 0) {
    return false;
  }
  return a.size() < b.size();
}

bool operator>(const String& a, const String& b) {
  return (b < a);
}

bool operator>=(const String& a, const String& b) {
  return !(a < b);
}

bool operator<=(const String& a, const String& b) {
  return !(a > b);
}

std::istream& operator>>(std::istream& in, String& str) {
  char ch;
  str.clear();
  in.get(ch);
  while (isspace(ch) && !in.eof())
    in.get(ch);
  while (!isspace(ch) && !in.eof()) {
    str.push_back(ch);
    if (in.eof())
      return in;
    in.get(ch);
  }
  return in;
}

std::ostream& operator<<(std::ostream& out, const String& str) {
  size_t curindex = 0;
  if (str.data() == nullptr) {
    return out;
  }
  while (curindex < str.size()) {
    out << str.data()[curindex++];
  }
  return out;
}
