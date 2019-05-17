#include "profile.h"
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <utility>

using namespace std;

vector<string> ReadStrings(istream& stream, bool use_move) {
    vector<string> strings;
    string s;
    while (stream >> s) {
        if (use_move) {
            strings.push_back(move(s));
        }
        else {
            strings.push_back(s);
        }
    }
    return strings;
}

string GenerateText() {
    const int SIZE = 100'000'000;
    const int WORD_LENGHT = 1'000'000;
    string text(SIZE, 'a');
    for (int i = WORD_LENGHT; i < SIZE; i += WORD_LENGHT) {
        text[i] = ' ';
    }
    return text;
}

int main() {
    const string text = GenerateText();
    //with move 9627ms
    {  LOG_DURATION("without move");
    istringstream stream(text);
    ReadStrings(stream, false);
    }
    //without move 9324ms
    {  LOG_DURATION("with move");
        istringstream stream(text);
        ReadStrings(stream, true);
    }

    return 0;
}