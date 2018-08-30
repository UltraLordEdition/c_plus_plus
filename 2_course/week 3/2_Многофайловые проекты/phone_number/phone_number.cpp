#include "phone_number.h"
#include <sstream>
#include <exception>

using namespace std;

PhoneNumber::PhoneNumber(const string &international_number)
{
    stringstream in(international_number);
    bool ok = true;
    
    int country_code;
    ok = ok && (in.peek() == '+');
    ok = ok && (in >> country_code);

    int city_code;
    ok = ok && (in.peek() == '-');
    in.ignore(1);
    ok = ok && (in >> city_code);

    string local_number;
    ok = ok && (in.peek() == '-');
    in.ignore(1);
    ok = ok && (in >> local_number);
    ok = ok && in.eof();

    if (!ok)
    {
        throw invalid_argument("Invalid_argument: " + international_number);
    }
    
    country_code_ = to_string(country_code);
    city_code_ = to_string(city_code);
    local_number_ = local_number;
}

string PhoneNumber::GetCountryCode() const
{
    return country_code_;
}

string PhoneNumber::GetCityCode() const
{
    return city_code_;
}

string PhoneNumber::GetLocalNumber() const
{
    return local_number_;;
}

string PhoneNumber::GetInternationalNumber() const
{
    return "+" + country_code_ + "-" + city_code_ + "-" + local_number_;
}