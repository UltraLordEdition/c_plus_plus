#pragma once

#include "date.h"
#include "node.h"
#include <iostream>
#include <string>
#include <set>
#include <map>
#include <functional>

using namespace std;

class List {
public:
	void AddEvents(const string& event);
	set<string> list_events;
	vector<string> last;
};

class Database {
public:
    void Add(const Date& date, const string& event);
       
    void Print(ostream& date_stream) const;
    
    int RemoveIf(function<const bool&(const Date&, const string&)> predicate);
    
    vector<string> FindIf(function<const bool&(const Date&, const string&)> predicate);
    
    string Last(const Date& date);

private:
    map<Date, List> storage;
};