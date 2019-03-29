#include "profile.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <string_view>
#include <vector>
#include <set>

using namespace std;

template <typename It>
string ConstructString(It range_begin, It range_end)
{
    string word(range_begin, range_end);
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

vector<string_view> SplitIntoWordsView(const string& s) {
    string_view str = s;

    vector<string_view> result;

    while (true)
    {
        //ищим пробел в еще не обработанной части
        size_t space = str.find(' ');
        result.push_back(str.substr(0, space));
        if (space == str.npos) {
            break;
        }
        else {
            str.remove_prefix(space + 1);
        }
    }
    return result;
}

//функция генерирующая текст
string GenerateText() {
    const int SIZE = 10000000;
    string text(SIZE, 'a');
    for (int i = 100; i < SIZE; i += 100) {
        text[i] = ' ';
    }
    return text;
}

int main() {
    const string text = GenerateText();
    { LOG_DURATION("string");
      const auto words = SplitIntoWords(text);
      cout << words[0] << "\n";
    }
    //спомощью string_view
    { LOG_DURATION("string_view");
    const auto words = SplitIntoWordsView(text);
    cout << words[0] << "\n";
    }

    return 0;
}