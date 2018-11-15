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

	set<string> events;
	vector<string> last;
};

class Database {
public:
    
    void Add(const Date& date, const string& event);
       
    void Print(ostream& date_stream) const;
    
    int RemoveIf(function<bool(const Date&, const string&)> predicate);
    
    vector<string> FindIf(function<bool(const Date&, const string&)> predicate) const;
    
    string Last(const Date& date) const;

private:
    map<Date, List> storage;
};

template<typename P>
void getPrint(const Date& date, const List& list, P& parametr);

template<typename P>
stringstream getFindIf(const Date& date, const List& list, P& parametr);

template<typename P>
int getRemoveIf(const Date& date, List& list, P& parametr);