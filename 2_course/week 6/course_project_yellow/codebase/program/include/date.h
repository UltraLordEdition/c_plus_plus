#pragma once

#include <sstream>
#include <iomanip>
#include <string>

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

Date ParseDate(istringstream& date_stream);

// даты будут по умолчанию выводиться в нужном формате
ostream& operator<<(ostream& stream, const Date& date);