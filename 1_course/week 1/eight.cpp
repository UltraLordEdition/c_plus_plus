#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
	int A, B, k = 1, x;
		cin >> A >> B;
		if ( A == 0 ){
			cout << B;
		} else if ( B == 0 ){
			cout << A;
		} else if ( A == B){
			cout << A;
		} else if ( A == 1){
			cout << "1";
		} else if ( B == 1){
			cout << "1";
		} else{
				while (A % 2 == 0 && B % 2 == 0 ){
					A /= 2;
					B /= 2;
					k *= 2;
				}
				while (A != 0){
					while ( A % 2 == 0 ){
						A /= 2;
					}
					while ( B % 2 == 0){
						B /= 2;
					}
					if ( A >= B ){
						A -=B;
					} else{
						B -=A;
					}
				}
				cout << B*k;
		}
		return 0;
}
