#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

int main() {
	vector<double> K(3);
		double D, x1, x2;
		cin >> K[0] >> K [1] >> K[2];
		if (K[0] == 0 && K[1] != 0){
			x1 = (-1*K[2]) / (K[1]);
			cout << x1;
		} else{
			D = (K[1]*K[1])-(4*K[0]*K[2]);
			if ( D == 0 && K[1] != 0){
			x1 = (-1*K[1]) / (2*K[0]);
			cout << x1;
			}
			if ( D > 0 ){
				x1 = ((-1*K[1])+(sqrt(D))) / (2*K[0]);
				x2 = ((-1*K[1])-(sqrt(D))) / (2*K[0]);
				cout << x1 << " " << x2;
			}
		}


	return 0;
}
