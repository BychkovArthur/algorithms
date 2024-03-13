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

        - Нормально ли в одном тесте прописывать несколько assert'ов? Например, в проверке конструктора
*/

class String {
private:
    char* arr;
    size_t sz;
    size_t cap;

    explicit String(size_t sz, size_t cap);
    explicit String(size_t n);

    void swap(String& other);

    friend String operator+(char c, const String& other);
    friend String operator+(const String& other, char c);
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

    size_t find(const String& other);
    size_t rfind(const String& other);

    size_t size() const;
    size_t length() const;
    size_t capacity() const;
    bool empty() const;
    char* data();
    const char* data() const;
    void clear();

    bool operator<(const String& other) const;
    bool operator>(const String& other) const;
    bool operator<=(const String& other) const;
    bool operator>=(const String& other) const;
    bool operator==(const String& other) const;
    bool operator!=(const String& other) const;

};