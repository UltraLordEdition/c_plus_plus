#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

struct Lang
{
    string name;
    int age;
};

//сделаем синоним для типа итератора
using LangIt = vector<string>::iterator;
//сделаем функию шаблонной
template <typename It>
void PrintRange(It range_begin, It range_end)
{
    for (auto it = range_begin; it != range_end; ++it)
    {
        cout << *it << " ";
    }
}

template <typename It>
void PrintMapRange(It range_begin, It range_end)
{
    for (auto it = range_begin; it != range_end; ++it)
    {
        cout << it->first << "/" << it->second << " ";
    }
}


int main() 
{
    //Iterator for vector
    cout << "Iterator for vector:" << endl;
    {
        vector<string> langs = {
            "Python",
            "C++",
            "C",
            "Java",
            "C#",
        };
        PrintRange(begin(langs), end(langs));
    }
    //Iterator for set
    cout << endl << "Iterator for set:" << endl;
    {
        set<string> langs = {
            "Python",
            "C++",
            "C",
            "Java",
            "C#",
        };
        PrintRange(begin(langs), end(langs));

        cout << endl;
        auto it = langs.find("C++");
        PrintRange(begin(langs), it);
        
        cout << endl;
        PrintRange(it, langs.end());
    }
    //Iterator for map
    cout << endl << "Iterator for map:" << endl;
    {
        map<string, int> langs = {
            {"Python", 26},
            {"C++", 34},
            {"C", 45},
            {"Java", 22},
            {"C#", 17}
        };
        auto it = langs.find("C++");
        PrintMapRange(begin(langs), it);
        cout << endl;
        PrintMapRange(it, langs.end());
    }
           
    return 0;
}

