#include "profile.h"
#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <map>

using namespace std;

string MakeString() {
    return string(100'000'000, 'a');
}

vector<int> MakeVector() {
    return vector<int>(100'000'000, 0);
}

int main() {
    //с копированием 167ms
    {  LOG_DURATION("assigment, with variable");
        string target_string = "old value";
        string source_value = MakeString();
        target_string = source_value;
    }
    //без копирования 59ms
    {  LOG_DURATION("assigment, without variable");
        string target_string = "old value";
        target_string = MakeString();
    }
    //for set 102ms
    {  LOG_DURATION("set::insert, with variable");
        set<string> strings;
        string heavy_string = MakeString();
        strings.insert(heavy_string);
    }
    //for set 51ms
    {  LOG_DURATION("set::insert, without variable");
        set<string> strings;
        strings.insert(MakeString());
    }
    //for set 3980ms
    {  LOG_DURATION("set::insert for vector, with variable");
        set<vector<int>> vectors;
        vector<int> heavy_vector = MakeVector();
        vectors.insert(heavy_vector);
    }
    //for set 3681ms
    {  LOG_DURATION("set::insert for vector, without variable");
        set<vector<int>> vectors;
        vectors.insert(MakeVector());
    }
    //for map 213ms
    {  LOG_DURATION("map::operator[], with variables");
        map<string, string> strings;
        string key = MakeString();
        string value = MakeString();
        strings[key] = value;
    }
    //for map 100ms
    {  LOG_DURATION("map::operator[], without variables");
        map<string, string> strings;
        strings[MakeString()] = MakeString();
    }
    return 0;
}