#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void UpdateIfGreater(int first, int& second) {
	if (first > second) {
		second = first;
	}
}