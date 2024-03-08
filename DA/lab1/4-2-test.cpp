#include <iostream>
#include <string>
#include <vector>
#include <array>

/*
    DATE START
*/

class Date {

    friend std::ostream& operator<<(std::ostream& os, const Date& date);
    friend std::istream& operator>>(std::istream& is, Date& date);

private:
    uint8_t day = 1;
    uint8_t month = 1;
    uint16_t year = 1;
    std::string date;

    void parse_string();

public:
    Date() = default;
    Date(Date&&) = default;
    Date(const Date& other);
    Date(const std::string& _date);

    Date& operator=(Date&&) = default;
    Date& operator=(Date& other);

    uint8_t get_day();
    uint8_t get_month();
    uint16_t get_year();
    size_t merge_date();
};

void Date::parse_string() {
    bool is_left_dot = true;
    size_t current_number = 0;

    for (size_t i = 0; i < date.size(); ++i) {
        if (date[i] == '.') {

            if (is_left_dot) { // Левая точка - день
                is_left_dot = false;
                day = current_number;
            } else { // Между первой и второй - месяц
                month = current_number;
            }
            current_number = 0;

        } else {
            current_number *= 10;
            current_number += (date[i] - '0');
        }

        year = current_number; // Остался год
    }
}

Date::Date(const std::string& _date) : date(_date) {
    parse_string();
}

Date::Date(const Date& other) : day(other.day), month(other.month), year(other.year), date(other.date) {std::cout << "COPY????" << std::endl;}

Date& Date::operator=(Date& other) {
    if (this == &other) {
        return *this;
    }

    day = other.day;
    month = other.month;
    year = other.year;
    date = other.date;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Date& _date) {
    os << _date.date;
    return os;
}

std::istream& operator>>(std::istream& is, Date& _date) {
    is >> _date.date;
    _date.parse_string();
    return is;
}

uint8_t Date::get_day() {
    return day;
}

uint8_t Date::get_month() {
    return month;
}

uint16_t Date::get_year() { 
    return year;
}

size_t Date::merge_date() {
    return day + month * 100 + year * 10'000;
}
/*
    DATE END
*/




/*
    DATA START
*/

struct Data {
    friend std::ostream& operator<<(std::ostream& os, const Data& data);
    friend std::istream& operator>>(std::istream& is, Data& data);

    Date key;
    std::string value;

    Data() = default;
    Data(Data&&) = default;
    Data(const Date& key, const std::string& value);
    Data(const Data& other);

    Data& operator=(Data& other);
    Data& operator=(Data&&) = default;
};

Data::Data(const Date& key, const std::string& value) : key(key), value(value) {}
Data::Data(const Data& other) : key(other.key), value(other.value) {std::cout << "COPY????" << std::endl;}

std::ostream& operator<<(std::ostream& os, const Data& data) {
    os << data.key << '\t' << data.value;
    return os;
}
std::istream& operator>>(std::istream& is, Data& data) {
    is >> data.key >> data.value;
    return is;
}

Data& Data::operator=(Data& other) {
    if (this == &other) {
        return *this;
    }

    key = other.key;
    value = other.value;
    return *this;
}

/*
    DATA END
*/


void LSD(std::vector<Data>& vct) {
    std::array<size_t, 256> counting_sort = {};
    size_t n = vct.size();
    std::vector<Data> other(n);

    size_t max = vct[0].key.merge_date();
    size_t base = 255;
    size_t digit_number = 0;

    for (Data& el : vct) {
        max = el.key.merge_date() > max ? el.key.merge_date() : max;
    }

    
    // 1) Выполнить сортировку подсчётом по разряду
    // 2) тут же посчитать преффиксную сумму этого массива
    // 3) Записать в другой массив результат

    // (base <= max) || (base > max && max & base) = 
    // A || ~A && B = A || B, т.е. base <= max || max & base
    while ((base <= max) || (max & base)) {
        
        for (Data& el : vct) { // Сортировка подсчётом
            size_t digit = (el.key.merge_date() & base) >> (8 * digit_number); // Конкретная цифра в 256 системе
            ++counting_sort[digit];
        }


        for (size_t i = 1; i < 256; ++i) { // Считаем префиксы
            counting_sort[i] += counting_sort[i - 1];
        }

        for (ssize_t i = n - 1; i >= 0; --i) { // Упорядочиваем.
            size_t digit = (vct[i].key.merge_date() & base) >> (8 * digit_number);
            size_t index = --counting_sort[digit];
            other[index] = std::move(vct[i]);
        }

        for (size_t& el : counting_sort) { // Зануляем массив для сортировки подсчётом.
            el = 0;
        }

        std::swap(vct, other);
        base <<= 8;
        ++digit_number;

        if (digit_number == 8) { // Сделали 8 сдвигов.
            break;               // Тем самым вышли за 8 байтное число
        }                        // Дальше нет смысла ничего делать.

    }

    
}


int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);


    std::vector<Data> data;

    for (size_t i = 0;;++i) {
        Data item;
        if (std::cin >> item) {
            data.push_back(std::move(item));
        } else {
            break;
        }
    }

    if (data.size() == 0) {
        return 0;
    }
    
    LSD(data);

    for (size_t i = 0; i < data.size(); ++i) {
        std::cout << data[i] << '\n';
    }
}