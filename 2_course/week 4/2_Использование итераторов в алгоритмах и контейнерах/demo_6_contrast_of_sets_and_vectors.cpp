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
    // Найдем язык начинающийся с буквы С и его позицию для vector
    {
        vector<string> langs = { "Python", "C++", "C", "Java", "C#" };
        vector<string> c_langs;
        auto  it = find_if(begin(langs), end(langs),
            [](const string& lang)
            {
                return lang[0] == 'C';
            });
        cout << it-begin(langs) << endl;
        //PrintRange(begin(c_langs), end(c_langs));
    }

    // Для set 
    cout << endl << "Stagе two" << endl;
    {
        set<int> s = { 1,6,8,9 };
        auto it = s.find(6);
        ++it;
        PrintRange(it, end(s));
    }

    // Для set улучшенный вариант с использованием next
    cout << endl << "Stagе three" << endl;
    {
        set<int> s = { 1,6,8,9 };
        auto it = s.find(6);
        PrintRange(next(it), end(s));
    }

    // Для set улучшенный вариант с использованием prev
    cout << endl << "Stagе three" << endl;
    {
        set<int> s = { 1,6,8,9 };
        auto it = s.find(6);
        PrintRange(prev(it), end(s));
    }

    return 0;
}

