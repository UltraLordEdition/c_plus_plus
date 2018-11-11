#include "database.h"
#include <algorithm>

void List::AddEvents(const string& events) {
	list_events.insert(events);
	last.push_back(events);
}

void Database::Add(const Date& date, const string& event) {
	storage[date].AddEvents(event);
}

void Database::Print(ostream& date_stream) const {
    for (auto it = begin(storage); it != end(storage); ++it) {
        for (auto it_set = it->second.list_events.begin(); it_set != it->second.list_events.end(); ++it_set) {
            date_stream << it->first << " " << *it_set << endl;
        }
    }
}

int Database::RemoveIf(function<const bool&(const Date&, const string&)> predicate) {
    int event_count = 0;
    for (auto it = begin(storage); it != end(storage);) {
        for (auto it_set = it->second.list_events.begin(); it_set != it->second.list_events.end();) {
            if (predicate(it->first, *it_set) == true) {
                ++event_count;
                it_set = it->second.list_events.erase(it_set);
			}
            else {
                ++it_set;
            }
        }
        if (it->second.list_events.size() == 0u) {
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
        for (auto it_set = it->second.list_events.begin(); it_set != it->second.list_events.end(); ++it_set) {
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
    stringstream str_stream;
	auto it = storage.lower_bound(date);
	//it = prev(it);
	str_stream << it->first << " " << *storage[it->first].last.rbegin();
    return str_stream.str();
}