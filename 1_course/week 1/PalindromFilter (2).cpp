#include "stdafx.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool IsPalindrom(string word) {
	string right;
	for (int i = word.size() - 1; i >= 0; --i) {
		right.push_back(word[i]);
	}
	return (right == word);
}

vector<string> PalindromFilter(vector<string> words, int minLength){
	vector<string> new_words;
	for (auto str : words) {
		if (str.size() >= minLength && IsPalindrom(str)) {
			new_words.push_back(str);
		}
	}
	return new_words;
}