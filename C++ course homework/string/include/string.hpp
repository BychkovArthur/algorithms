#pragma once
#include <iostream>


/*
    TODO:
        - Добавить док стринги ко всем методам. Научиться комментировать методы и их параметры.
        - Насколько хорошая практика использовать делигирующие конструкторы? Не много ли будет вызовов функции?
        - Спросить, в const data нужно ли вообще делать static/const cast? Ведь когда мы в const объекте там поле char* const, а мы хотим его закастовать в const char*
        - Чем std::fill и std::copy лучше наивной реализации?
        - В каком порядке стоит описывать поля в классе? Есть ли регламмент на то, в каком лучше порядке определять поля в классе
        - Сделать две реализации сравнения: без spaceship и с ним.

        - Почему у челика realloc и malloc, а не new и delete? Что лучше использоват???
        - Стоит ли что-то специально выносить из класса? Например, operator< и остальные 5???

        - Нормально ли в одном тесте прописывать несколько assert'ов? Например, в проверке конструктора.
        - Переписать find и rfind на линейный алгоритм.

        - Можно уменьшить количество созданий в operator=. Если размер текущей >= размер другой, мы можем просто std::copy. Однако, у строк будут разные capacity. 
*/

class String {
private:
    char* arr;
    size_t sz;
    size_t cap;

    explicit String(size_t sz, size_t cap);
    explicit String(size_t n);

    void swap(String& other);
    void realloc_to_new_cap();

    friend String operator+(char c, const String& other);
    friend String operator+(const String& other, char c);

    size_t search(const String& substr, bool is_left_search);
public:
    String();
    String(const char* c_str);
    String(size_t n, char c);
    String(const String& other);
    ~String();
    String& operator=(const String& other);

    char& operator[](size_t ind);
    const char& operator[](size_t ind) const;
    char& front();
    const char& front() const;
    char& back();
    const char& back() const;

    void push_back(char c);
    void pop_back();
    String& operator+=(char c);
    String& operator+=(const String& other);
    String substr(size_t start, size_t count);

    size_t find(const String& substr);
    size_t rfind(const String& substr);

    size_t size() const;
    size_t length() const;
    size_t capacity() const;
    bool empty() const;
    char* data();
    const char* data() const;
    void clear();
    void shrink_to_fit();
};


String operator+(char c, const String& str);
String operator+(const String& str, char c);
String operator+(const String& str1, const String& str2);

bool operator<(const String& str1, const String& str2);
bool operator>(const String& str1, const String& str2);
bool operator<=(const String& str1, const String& str2);
bool operator>=(const String& str1, const String& str2);
bool operator==(const String& str1, const String& str2);
bool operator!=(const String& str1, const String& str2);
bool operator==(const char* str1, const String& str2);
bool operator==(const String& str1, const char* str2);

std::ostream& operator<<(std::ostream& os, const String& str);
std::istream& operator>>(std::istream& is, String& str);