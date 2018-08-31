#include <iostream>
#include <vector>
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

int main() 
{
    //Part one
    cout << "Part one" << endl;
    {
        vector<Lang> langs = {
            {"Python",26},
            {"C++",34},
            {"C", 45},
            {"Java", 22},
            {"C#", 17 } };
        auto result = find_if(begin(langs), end(langs),
            [](const Lang& lang)
        {
            return lang.name[0] == 'С';
        });

        string lang = langs[1].name;
        auto it = begin(lang);
        cout << *it;
        it++;
        cout << *it;
    }
    //Part two
    cout << endl << "Part two" << endl;
    {
        vector<Lang> langs = {
            { "Python",26 },
            { "C++",34 },
            { "C", 45 },
            { "Java", 22 },
            { "C#", 17 } 
        };
        for (auto it = begin(langs); it != end(langs); ++it)
        {
            cout << it->name << " ";
        }
        /* Вот так вот делать нельзя
        cout << end(langs)->name;*/             
    }
    //Part three
    cout << endl << "Part three" << endl;
    {
       vector<string> langs = {
            "Python",
            "C++",
            "C",
            "Java",
            "C#",
        };
        PrintRange(begin(langs), end(langs));
        //После того как ввели шаблон для функции PrintRange, стало возможно вызвать функцию от строки
        PrintRange(begin(langs[0]), end(langs[0]));

    }
       
    return 0;
}