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

int main() 
{
    vector<Lang> langs = {
        {"Python",26},
        {"C++",34},
        {"C", 45},
        {"Java", 22},
        {"C#", 17 }};
    auto result = find_if(begin(langs), end(langs),
        [](const Lang& lang)
        {
            return lang.name[0] == 'С';
        });
    //Если элемент не нашелся (сравниваем результат с концом диапазона)
    if (result == end(langs))
    {
        cout << "Not found";
    }
    else
    {
        //Выведем возраст age используя операцию разыменования итератора
        cout << (*result).age << endl;
        //Или выведем вот так, более удобно
        cout << result->age << endl;
    }
    
    cout << begin(langs)->name << " " << langs.begin()->age << endl;

    return 0;
}

