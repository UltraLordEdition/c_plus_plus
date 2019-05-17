#include "profile.h"
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include <utility>

using namespace std;

vector<string> SplitIntoWords(const string& text) {
    vector<string> words;
    string current_words;
    for (const char c : text) {
        if (c == ' ') {
            words.push_back(move(current_words));   //копирование если убрать move
            current_words.clear();
        } else {
            current_words.push_back(c);
        }
    }
    words.push_back(move(current_words));             //копирование
    return words;
}

int main() {
    for (const string& word : SplitIntoWords("Red belt C++")) {
        cout << word << "\n";
    }
    return 0;
}
/*
	- функция move позволяет инициаровать перемещение там, где случилось бы копирование
	- функция move не перемещает, она лишь заставляет компилятор переместить
	- как правило после перемещения обьект остается пустым
*/
