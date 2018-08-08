#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
string word;
	cin >> word;
	int x = 0;
	for (int i = 0; i <= word.size(); ++i){
		if ( word[i] == 'f'){
			x++;
			if ( x == 2){
				cout << i;
				break;
			}
		}
	}
	if ( x == 1){
		cout << "-1";
	} else if ( x == 0){
		cout << "-2";
	}
	return 0;
}