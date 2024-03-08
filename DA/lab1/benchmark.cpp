#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <chrono>
#include <fstream>
#include <algorithm>

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

    uint8_t get_day() const;
    uint8_t get_month() const;
    uint16_t get_year() const;
    size_t merge_date();
};

void Date::parse_string() {
    bool is_left_dot = true;
    size_t current_number = 0;

    for (size_t i = 0; i < date.size(); ++i) {
        if (date[i] == '.') {

            if (is_left_dot) { // Left dot - day
                is_left_dot = false;
                day = current_number;
            } else { // Between the first and second - a month
                month = current_number;
            }
            current_number = 0;

        } else {
            current_number *= 10;
            current_number += (date[i] - '0');
        }

        year = current_number; // Left year
    }
}

Date::Date(const std::string& _date) : date(_date) {
    parse_string();
}

Date::Date(const Date& other) : day(other.day), month(other.month), year(other.year), date(other.date) {}

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

uint8_t Date::get_day() const {
    return day;
}

uint8_t Date::get_month() const {
    return month;
}

uint16_t Date::get_year() const { 
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
Data::Data(const Data& other) : key(other.key), value(other.value) {}

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

    /*
     1) Sort by counting by digit.
     2) Immediately calculate the prefix sum of this array.
     3) Write the result to another array.
    */

    /*
     (base <= max) || (base > max && max & base) ==
     A || ~A && B ==
     A || B       =>
     base <= max || max & base
    */
    while ((base <= max) || (max & base)) {
        
        for (Data& el : vct) { // Sorting by counting
            size_t digit = (el.key.merge_date() & base) >> (8 * digit_number); // Specific number in the 256 system
            ++counting_sort[digit];
        }


        for (size_t i = 1; i < 256; ++i) { // Counting prefixes
            counting_sort[i] += counting_sort[i - 1];
        }

        for (ssize_t i = n - 1; i >= 0; --i) { // Sorting
            size_t digit = (vct[i].key.merge_date() & base) >> (8 * digit_number);
            size_t index = --counting_sort[digit];
            other[index] = std::move(vct[i]);
        }

        for (size_t& el : counting_sort) { // We zero the array for counting sorting.
            el = 0;
        }

        std::swap(vct, other);
        base <<= 8;
        ++digit_number;

        if (digit_number == 8) { // We made 8 shifts.
            break;               // Thus, we exceeded the 8-byte number.
        }
    }
}

bool operator<(const Data& lhs, const Data& rhs) {
    if (lhs.key.get_year() != rhs.key.get_year()) {
        return lhs.key.get_year() < rhs.key.get_year();
    }
    if (lhs.key.get_month() != rhs.key.get_month()) {
        return lhs.key.get_month() < rhs.key.get_month();
    }
    if (lhs.key.get_day() != rhs.key.get_day()) {
        return lhs.key.get_day() < rhs.key.get_day();
    }
    return false;
}


int main() {
    // std::ios::sync_with_stdio(false);
    // std::cin.tie(0);

    std::ofstream lsd_out;
    std::ofstream stable_sort_out;
    lsd_out.open("LSD.txt");
    stable_sort_out.open("stable_sort.txt");
    if (!lsd_out.is_open() || !stable_sort_out.is_open()) {
        return 1;
    }

    std::vector<Data> lsd_vector;

    for (size_t i = 0;;++i) {
        Data item;
        if (std::cin >> item) {
            lsd_vector.push_back(std::move(item));
        } else {
            break;
        }
    }

    std::vector<Data> stable_sort_vector(lsd_vector.size());
    for (size_t i = 0; i < lsd_vector.size(); ++i) {
        stable_sort_vector[i] = lsd_vector[i];
    }

    auto begin = std::chrono::steady_clock::now();
    LSD(lsd_vector);
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    for (size_t i = 0; i < lsd_vector.size(); ++i) {
        lsd_out << lsd_vector[i] << '\n';
    }
    lsd_out << "Time: " << elapsed_ms.count() << "ms" << std::endl;


    begin = std::chrono::steady_clock::now();
    std::stable_sort(stable_sort_vector.begin(), stable_sort_vector.end());
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    for (size_t i = 0; i < lsd_vector.size(); ++i) {
        stable_sort_out << lsd_vector[i] << '\n';
    }
    stable_sort_out << "Time: " << elapsed_ms.count() << "ms" << std::endl;


    lsd_out.close();
    stable_sort_out.close();

}