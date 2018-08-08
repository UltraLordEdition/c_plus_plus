#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
	vector<int> bin;
	int N;
	cin >> N;
	while ( N != 0){
		bin.push_back(N % 2);
		N = N/2;
	}
	for (int i = bin.size()-1; i >= 0; --i ){
		cout << bin[i];
		}
	return 0;
}