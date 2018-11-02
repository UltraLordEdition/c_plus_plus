#pragma once

#include "date.h"
#include "node.h"
#include <iostream>
#include <string>
#include <set>
#include <map>
#include <functional>

using namespace std;

class Database
{
public:
    void Add(const Date& date, const string& event);
       
    void Print(ostream& date_stream) const;
    
    int RemoveIf(function<const bool&(const Date&, const string&)> predicate);
    //void FindIf();
    //void Last();

private:
    map<Date, set<string>> storage;
};