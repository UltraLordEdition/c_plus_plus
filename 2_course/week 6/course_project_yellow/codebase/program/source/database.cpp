#include "database.h"
#include <algorithm>

void Database::Add(const Date& date, const string& event) {
    storage[date].insert(event);
}

void Database::Print(ostream& date_stream) const {
    for (auto it = begin(storage); it != end(storage); ++it) {
        for (auto it_set = it->second.begin(); it_set != it->second.end(); ++it_set) {
            date_stream << it->first << " " << *it_set << endl;
        }
    }
}

int Database::RemoveIf(function<const bool&(const Date&, const string&)> predicate) {
    int event_count = 0;
    for (auto it = begin(storage); it != end(storage);) {
        for (auto it_set = it->second.begin(); it_set != it->second.end();) {
            if (predicate(it->first, *it_set) == true) {
                ++event_count;
                it_set = it->second.erase(it_set);
            }
            else {
                ++it_set;
            }
        }
        if (it->second.size() == 0u) {
            it = storage.erase(it);
        }
        else {
            ++it;
        }
    }
    return event_count;
}

vector<string> Database::FindIf(function<const bool&(const Date&, const string&)> predicate) {
    string str;
    stringstream str_stream;
    vector<string> v;
    for (auto it = begin(storage); it != end(storage); ++it) {
        for (auto it_set = it->second.begin(); it_set != it->second.end(); ++it_set) {
            if (predicate(it->first, *it_set) == true) {
                str_stream << it->first << " " << *it_set << endl;
                getline(str_stream, str);
                v.push_back(str);
            }
        }
    }
    return v;
}

string Database::Last(const Date& date) {
    string stream;
    return stream;
}