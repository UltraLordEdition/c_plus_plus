#include "database.h"

void Database::Add(const Date& date, const string& event) {
    storage[date].insert(event);
}

void Database::Print(ostream& date_stream) const {
    for (const auto& item : storage)
    {
        for (const string& event : item.second)
        {
            date_stream << item.first << " " << event << endl;
        }
    }
}