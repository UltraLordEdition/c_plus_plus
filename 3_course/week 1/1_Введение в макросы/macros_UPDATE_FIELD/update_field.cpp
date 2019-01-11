#include "airline_ticket.h"
#include "test_runner.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <map>

using namespace std;

// Реализуйте этот макрос, а также необходимые операторы для классов Date и Time
#define UPDATE_FIELD(ticket, field, values)  \
    if (values.count(#field)) {              \
        istringstream is(values.at(#field)); \
        is >> ticket.field;                  \
    }

//Оператор ввода для Date
istringstream& operator>>(istringstream& stream, Date& date) {
    stream >> date.year;
    stream.ignore(1);
    stream >> date.month;
    stream.ignore(1);
    stream >> date.day;
    return stream;
}

//Оператор ввода для Time
istringstream& operator>>(istringstream& stream, Time& time) {
    stream >> time.hours;
    stream.ignore(1);
    stream >> time.minutes;
    return stream;
}

// Оператор вывода для Date
ostream& operator<<(ostream& stream, const Date& date) {
    stream  << setw(4) << setfill('0') << date.year <<
        "-" << setw(2) << setfill('0') << date.month <<
        "-" << setw(2) << setfill('0') << date.day;
    return stream;
}

// Оператор вывода для Time
ostream& operator<<(ostream& stream, const Time& time) {
     stream << setw(2) << setfill('0') << time.hours <<
        ":" << setw(2) << setfill('0') << time.minutes;
    return stream;
}

// Оператор == для Date
bool operator==(const Date& lhs, const Date& rhs) {
    return make_tuple(lhs.year, lhs.month, lhs.day) == make_tuple(rhs.year, rhs.month, rhs.day);
}

// Оператор == для Time
bool operator==(const Time& lhs, const Time& rhs) {
    return make_tuple(lhs.hours, lhs.minutes) == make_tuple(rhs.hours, rhs.minutes);
}

void TestUpdate() {
  AirlineTicket t;
  t.price = 0;
  
  const map<string, string> updates1 = {
    {"departure_date", "2018-2-28"},
    {"departure_time", "17:40"},
  };
  UPDATE_FIELD(t, departure_date, updates1);
  UPDATE_FIELD(t, departure_time, updates1);
  UPDATE_FIELD(t, price, updates1);

  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 0);
  
  const map<string, string> updates2 = {
    {"price", "12550"},
    {"arrival_time", "20:33"},
  };
  UPDATE_FIELD(t, departure_date, updates2);
  UPDATE_FIELD(t, departure_time, updates2);
  UPDATE_FIELD(t, arrival_time, updates2);
  UPDATE_FIELD(t, price, updates2);

  // updates2 не содержит ключей "departure_date" и "departure_time", поэтому
  // значения этих полей не должны измениться
  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 12550);
  ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
 
  const map<string, string> updates3 = {
    {"from", "DME"},
    {"to", "AER"},
  };
  UPDATE_FIELD(t, from, updates3); 
  UPDATE_FIELD(t, to, updates3);
  UPDATE_FIELD(t, price, updates3);

  ASSERT_EQUAL(t.from, ("DME"));
  ASSERT_EQUAL(t.to, ("AER"));
  ASSERT_EQUAL(t.price, 12550);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestUpdate);
}
