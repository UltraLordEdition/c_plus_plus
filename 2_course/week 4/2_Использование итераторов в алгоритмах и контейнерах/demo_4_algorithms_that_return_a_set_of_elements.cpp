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
        cout << *it << ", ";
    }
}

int main()
{
    vector<string> langs = { "Python", "C++", "C", "Java", "C#" };
    
   // Разобьем вектор на две части по критериям
    {
        auto it = partition(begin(langs), end(langs),
            [](const string& lang)
            {
                return lang[0] == 'C';
            });
        PrintRange(begin(langs), it);
    }

    // Скопируем одну часть вектора в другой вектор
    vector<string> langs1 = { "Python", "C++", "C", "Java", "C#" };
    cout << endl << "Stage two" << endl;
    {
        vector<string> c_langs(langs1.size());
        auto it = copy_if(begin(langs1), end(langs1), begin(c_langs),
            [](const string& lang)
            {
                return lang[0] == 'C';
            });
        PrintRange(begin(c_langs), it);
    }

    // Алгоритм пересечения множества
    cout << endl << "Stage three" << endl;
    {
        set<int> a = { 1, 8, 3 };
        set<int> b = { 3, 6, 8 };
        vector<int> v(a.size());
        auto it = set_intersection(begin(a), end(a), begin(b), end(b), begin(v));
        PrintRange(begin(v), it);
    }

    return 0;
}

