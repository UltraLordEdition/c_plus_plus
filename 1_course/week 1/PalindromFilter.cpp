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
	for (size_t i = 0; i < words.size(); ++i){
		if (words[i].size() >= minLength){
			if (IsPalindrom(words[i]) == true) {
				new_words.push_back(words[i]);
			}
		}
	}
	
	return new_words;
}