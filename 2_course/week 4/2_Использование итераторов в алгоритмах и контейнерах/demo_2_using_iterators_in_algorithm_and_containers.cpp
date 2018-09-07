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
    //Part one удалим все элементы содержащие букву С в начале
    cout << "Part one" << endl;
    {
        vector<string> langs = { "Python", "C++", "C", "Java", "C#" };
        //Но remove_if реально данные не удоляет, а только помогает удолить!!!
        auto it = remove_if(begin(langs), end(langs),
            [](const string& lang)
        {
            return lang[0] == 'C';
        });
        //А вот теперь удалим данные!
        langs.erase(it, end(langs));
        PrintRange(begin(langs), end(langs));
    }

    //Part two удалим подряд идущии символы
    cout << endl << endl << "Part two" << endl;
    {
        vector<string> langs = { "Python", "C++", "C++", "Java", "C++" };
        auto it = unique(begin(langs), end(langs));
        //А вот теперь удалим данные!
        langs.erase(it, end(langs));
        PrintRange(begin(langs), end(langs));
    }

    //Part three найдем минимум в масиве и максимум
    // одновременно когда нужно и минимум и максимум
    cout << endl << endl << "Part three" << endl;
    {
        vector<string> langs = { "Python", "C++", "C", "Java", "C#" };

        auto it = min_element(begin(langs), end(langs));
        cout << *it << endl;

        auto it2 = max_element(begin(langs), end(langs));
        cout << *it2 << endl;

        auto p = minmax_element(begin(langs), end(langs));  //возвращает пару
        cout << *p.first << ' ' << *p.second << endl;
    }

    //Part four работа с set проверим что все слова начинаются с заглавной буквы
    cout << endl << endl << "Part four" << endl;
    {
        set<string> langs = { "Python", "C++", "C", "Java", "C#" };

        cout << all_of(begin(langs), end(langs),
            [](const string& lang)
            {
                return lang[0] >= 'A' && lang[0] <= 'Z';
            });       
    }

    return 0;
}