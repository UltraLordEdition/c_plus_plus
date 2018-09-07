#include <iostream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <set>

using namespace std;

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
    vector<string> langs = { "Python", "C++", "C", "Java", "C#" };
    auto it = find(begin(langs), end(langs), "C++");
    //Удалим С++
    langs.erase(it, end(langs));
    //Вернем С++
    langs.insert(begin(langs), "C++");
    PrintRange(begin(langs), end(langs));

    return 0;
}

