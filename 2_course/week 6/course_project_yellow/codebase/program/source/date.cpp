#include "date.h"

Date::Date(int new_year, int new_month, int new_day) : year_(new_year), month_(new_month), day_(new_day) {
}

int Date::GetYear() const {
    return year_;
}

int Date::GetMonth() const {
    return month_;
}

int Date::GetDay() const {
    return day_;
}

Date ParseDate(istringstream& date_stream) {
    bool ok = true;

    int year;
    ok = ok && (date_stream >> year);
    ok = ok && (date_stream.peek() == '-');
    date_stream.ignore(1);

    int month;
    ok = ok && (date_stream >> month);
    ok = ok && (date_stream.peek() == '-');
    date_stream.ignore(1);

    int day;
    ok = ok && (date_stream >> day);
    ok = ok && (~date_stream.eof());
    date_stream.ignore(1);

    if (!ok) {
        throw logic_error("Wrong date format: " + date_stream.str());
    }
    return Date(year, month, day);
}

// даты будут по умолчанию выводиться в нужном формате
ostream& operator<<(ostream& stream, const Date& date) {
    stream << setw(4) << setfill('0') << date.GetYear() <<
       "-" << setw(2) << setfill('0') << date.GetMonth() <<
       "-" << setw(2) << setfill('0') << date.GetDay();
    return stream;
}

bool operator<(const Date& lhs, const Date& rhs) {
    return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} < vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}