#pragma once

#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <tuple>

using namespace std;

class Date {
public:
   
    Date(int new_year, int new_month, int new_day); 

    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;

private:
    const int year_;
    const int month_;
    const int day_;
};

Date ParseDate(istream& date_stream);

// ���� ����� �� ��������� ���������� � ������ �������
ostream& operator<<(ostream& stream, const Date& date);

// ���������� ��������� ��� ��� ���������� ��� ������������� �� � �������� ������ �������
bool operator<(const Date& lhs, const Date& rhs);

bool operator<=(const Date& lhs, const Date& rhs);

bool operator>(const Date& lhs, const Date& rhs);

bool operator>=(const Date& lhs, const Date& rhs);

bool operator==(const Date& lhs, const Date& rhs);

bool operator!=(const Date& lhs, const Date& rhs);