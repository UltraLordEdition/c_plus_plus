#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> Reversed(const vector<int>& v) {
	vector<int> v1;

	int n = v.size();
	v1 = v;
	for (int i = 0; i < n/2; ++i) {
		int tmp = v1[i];
		v1[i] = v1[n - 1 - i];
		v1[n - 1 - i] = tmp;
	}
	return v1;
}