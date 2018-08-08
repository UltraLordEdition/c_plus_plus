#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void MoveStrings(vector<string>& source, vector<string>& destination) {
	for (size_t i = 0; i < source.size(); ++i) {
		destination.push_back(source[i]);
	}
	source.clear();
}