#include "database.h"
#include <algorithm>

template<typename P>
void getPrint(const Date& date, const List& list, P& parametr) {
    for (auto it = begin(list.last); it != end(list.last); ++it) {
        parametr << date << " " << *it << endl;           
    }
}

template<typename P>
stringstream getFindIf(const Date& date, const List& list, P& parametr) {
    stringstream str_stream;    
    for (auto it = begin(list.last); it != end(list.last); ++it) {
        if(parametr(date, *it) == true) {
            str_stream << date << " " << *it << endl;            
        }
    }
return str_stream;
}

template<typename P>
int getRemoveIf(const Date& date, List& list, P& parametr) {
    int event_count = 0;
    for (auto it = begin(list.events); it != end(list.events);) {
        if (parametr(date, *it) == true) {
            ++event_count;
            it = list.events.erase(it);
        }
        else {
            ++it;
        }
    }
    for (auto it_v = begin(list.last); it_v != end(list.last);) {
        if (parametr(date, *it_v) == true) {
            it_v = list.last.erase(it_v);
        }
        else {
            ++it_v;
        }
    }
    return event_count;
}

void List::AddEvents(const string& event) {
    if (events.count(event) == false) {
        events.insert(event);
        last.push_back(event);
    }
}

void Database::Add(const Date& date, const string& event) {
	storage[date].AddEvents(event);
}

void Database::Print(ostream& date_stream) const {
    for (auto it = begin(storage); it != end(storage); ++it) {
        getPrint(it->first, it->second, date_stream);
    }
}

int Database::RemoveIf(function<bool(const Date&, const string&)> predicate) {
    int event_count = 0;
    for (auto it = begin(storage); it != end(storage);) {
        event_count += getRemoveIf(it->first, it->second, predicate);
        if (it->second.events.size() == 0u) {
            it = storage.erase(it);
		}
        else {
            ++it;
        }
    }
    return event_count;
}

vector<string> Database::FindIf(function<bool(const Date&, const string&)> predicate) const {
    string str;
    vector<string> v_str;
    stringstream stream;
    for (auto it = begin(storage); it != end(storage); ++it) {
        stream = getFindIf(it->first, it->second, predicate);
        while (getline(stream, str)) {
            v_str.push_back(str);
        }
    }
    return v_str;
}

string Database::Last(const Date& date) const {
    stringstream str_stream;
	auto it = storage.upper_bound(date);
    if (it == storage.begin()) {
        throw invalid_argument("sad");        
    } else {
        it = prev(it);
        str_stream << it->first << " " << *it->second.last.rbegin();
        return str_stream.str();
    }    
}