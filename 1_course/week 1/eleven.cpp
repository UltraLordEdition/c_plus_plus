#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

bool IsPalindrom(string word){
string right;
for (int i  = word.size()-1; i >= 0; --i){
	right.push_back(word[i]);
}
if ( right == word){
	return 1;
} else {
	return 0;
}

}