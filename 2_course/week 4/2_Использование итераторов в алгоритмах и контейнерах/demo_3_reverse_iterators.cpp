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
    
    // Воспользуемся обратными итераторами
    {
        PrintRange(rbegin(langs), rend(langs));
    }

    cout << endl << "Stage two" << endl;
    {
        auto it = rbegin(langs);
        cout << *it << " ";
        ++it;
        cout << *it << " ";
    }

    cout << endl << "Stage three" << endl;
    {
        auto it = find_if(rbegin(langs), rend(langs),
            [](const string& langs)
            {
                return langs[0] == 'C';
            });
        cout << *it << endl;
    }

    cout << endl << "Stage four" << endl;
    {
        sort(rbegin(langs), rend(langs));
        PrintRange(begin(langs), end(langs));        
    }

    return 0;
}

