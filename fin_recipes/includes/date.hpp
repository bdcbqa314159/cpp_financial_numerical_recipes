#pragma once
#include <iostream>

class date
{
protected:
    int year_{}, month_{}, day_{};

public:
    date() = default;
    date(const int &year, const int &month, const int &day) : year_{year}, month_{month}, day_{day} {}
    ~date() = default;

    bool is_valid() const;

    int day() const;
    int month() const;
    int year() const;

    void set_day(const int &day);
    void set_month(const int &month);
    void set_year(const int &year);

    date &operator++();
    date operator++(int);
    date &operator--();
    date operator--(int);
};

bool operator==(const date &lhs, const date &rhs);
bool operator!=(const date &lhs, const date &rhs);
bool operator<(const date &lhs, const date &rhs);
bool operator>(const date &lhs, const date &rhs);
bool operator<=(const date &lhs, const date &rhs);
bool operator>=(const date &lhs, const date &rhs);

date next_date(const date &d);
date previous_date(const date &d);

std::ostream &operator<<(std::ostream &os, const date &d);
