#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>

using namespace std;

template <typename It>
string ConstructString(It range_begin, It range_end)
{
    string word(range_begin,range_end);
    return word;
}

vector<string> SplitIntoWords(const string& s)
{
    vector<string> words;
    auto start_it = begin(s);
    while (true)
    {
        auto end_it = find((start_it), end(s), ' ');
        words.push_back(ConstructString(start_it, end_it));
        if (end_it != end(s))
        {
            start_it = end_it;
            ++start_it;
        }
        else
        {
            return words;
        }
    }
}

int main() {
    string s = "C Cpp Java Python";

    vector<string> words = SplitIntoWords(s);
    cout << words.size() << " ";
    for (auto it = begin(words); it != end(words); ++it) {
        if (it != begin(words)) {
            cout << "/";
        }
        cout << *it;
    }
    cout << endl;

    return 0;
}