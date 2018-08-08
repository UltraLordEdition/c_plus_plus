#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
double N,A,B,X,Y;
	cin >> N >> A >> B >> X >> Y;
	if (A < B){
		if (N > A && N <= B){
			cout << (N-N*(X/100));
		} else if (N > B){
			cout << (N-N*(Y/100));
		} else if (N <= A){
			cout << N;
		}
	} else if (A == B){
		cout << "Error - A equal B";
	} else{
		cout << "Error - A bolshe B";
	}

	return 0;
}