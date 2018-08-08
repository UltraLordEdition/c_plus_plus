#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void Reverse(vector<int>& v) {
	vector<int> f;

	for (int i = v.size()-1; i >= 0; i--) {
		f.push_back(v[i]);
	}
	v = f;
}
