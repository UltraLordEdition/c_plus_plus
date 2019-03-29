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
//передаем string_view по значению для безопасного использования
//если хотим работать в функции с string_view удобно принимать string_view
//можно передать как string так и string_view
vector<string_view> SplitIntoWordsView(string_view str) {
    vector<string_view> result;

    //начинаем с нулевой позицией
    size_t pos = 0;
    //позиция за концом
    const size_t pos_end = str.npos;

    while (true)
    {
        size_t space = str.find(' ', pos);
        result.push_back(
            space == pos_end
            ? str.substr(pos)
            : str.substr(pos, space - pos));
        if (space == pos_end) {
            break;
        }
        else {
            pos = space + 1;
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