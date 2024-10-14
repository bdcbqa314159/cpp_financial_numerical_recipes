#include "date.hpp"

int date::day() const
{
    return day_;
}

int date::month() const
{
    return month_;
}

int date::year() const
{
    return year_;
}

void date::set_day(const int &day)
{
    day_ = day;
}

void date::set_month(const int &month)
{
    month_ = month;
}

void date::set_year(const int &year)
{
    year_ = year;
}

bool date::is_valid() const
{
    if (year_ < 0)
        return false;
    if (month_ < 1 || month_ > 12)
        return false;
    if (day_ < 1 || day_ > 31)
        return false;

    if ((day_ == 31) && (month_ == 2 || month_ == 4 || month_ == 6 || month_ == 9 || month_ == 11))
        return false;
    if ((day_ == 30) && (month_ == 2))
        return false;
    // if ((day_ == 29) && (month_ == 2) && (year_ % 4 != 0))
    //     return false;
    return true;
}

bool operator==(const date &lhs, const date &rhs)
{
    if (!lhs.is_valid() || !rhs.is_valid())
        return false;
    return lhs.year() == rhs.year() && lhs.month() == rhs.month() && lhs.day() == rhs.day();
}

bool operator!=(const date &lhs, const date &rhs)
{
    return !(lhs == rhs);
}

bool operator<(const date &lhs, const date &rhs)
{
    if (!lhs.is_valid() || !rhs.is_valid())
        return false;

    if (lhs.year() == rhs.year())
    {
        if (lhs.month() == rhs.month())
        {
            return lhs.day() < rhs.day();
        }
        return lhs.month() < rhs.month();
    }

    else
    {
        return lhs.year() < rhs.year();
    }
}

bool operator>(const date &lhs, const date &rhs)
{
    return rhs < lhs;
}

bool operator<=(const date &lhs, const date &rhs)
{
    return !(lhs > rhs);
}

bool operator>=(const date &lhs, const date &rhs)
{
    return !(lhs < rhs);
}

date next_date(const date &d)
{
    if (!d.is_valid())
        return date{};
    date ndat = date(d.year(), d.month(), d.day() + 1);
    if (ndat.is_valid())
        return ndat;
    ndat = date(d.year(), d.month() + 1, 1);
    if (ndat.is_valid())
        return ndat;
    ndat = date(d.year() + 1, 1, 1);
    return ndat;
}

date previous_date(const date &d)
{
    if (!d.is_valid())
        return date{};
    date pdat = date(d.year(), d.month(), d.day() - 1);
    if (pdat.is_valid())
        return pdat;
    pdat = date(d.year(), d.month() - 1, 31);
    if (pdat.is_valid())
        return pdat;

    pdat = date(d.year(), d.month() - 1, 30);
    if (pdat.is_valid())
        return pdat;

    pdat = date(d.year(), d.month() - 1, 29);
    if (pdat.is_valid())
        return pdat;

    pdat = date(d.year(), d.month() - 1, 28);
    if (pdat.is_valid())
        return pdat;

    pdat = date(d.year() - 1, 12, 31);
    if (pdat.is_valid())
        return pdat;

    return pdat;
}

date &date::operator++()
{
    *this = next_date(*this);
    return *this;
}

date date::operator++(int)
{
    date temp = *this;
    ++(*this);
    return temp;
}

date &date::operator--()
{
    *this = previous_date(*this);
    return *this;
}

date date::operator--(int)
{
    date temp = *this;
    --(*this);
    return temp;
}

std::ostream &operator<<(std::ostream &os, const date &d)
{
    if (!d.is_valid())
    {
        os << "Invalid date";
        return os;
    }
    os << d.year() << "/" << d.month() << "/" << d.day();
    return os;
}
