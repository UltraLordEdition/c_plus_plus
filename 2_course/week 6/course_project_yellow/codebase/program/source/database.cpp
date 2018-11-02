#include "database.h"
#include <algorithm>

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

int Database::RemoveIf(function<const bool&(const Date&, const string&)> predicate) {
    set<int> a = { 1,2,3 };

    cout << a.erase(a.begin(), a.end());
    
    
    
    
    int event_count = 0;
    for (const auto& key : storage) {
        if (predicate(key.first, "") == true) {
            event_count += storage[key.first].size();
            storage.erase(key.first);
        }
    }
   
    return 1;
}