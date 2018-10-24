#pragma once

#include "date.h"
#include "node.h"
#include <iostream>
#include <string>
#include <set>
#include <map>

using namespace std;

class Database
{
public:
    void Add(const Date& date, const string& event);
       
    void Print(ostream& date_stream) const;
    
    int RemoveIf(shared_ptr<Node>& predicate);
    //void FindIf();
    //void Last();

private:
    map<Date, set<string>> storage;
};