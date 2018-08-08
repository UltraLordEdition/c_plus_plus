#include <iostream>
#include <string>
using namespace std;

int main() {
	string x;
	string a,b,c;
	cin >> a >> b >>c;
	x = a;
	if (x > b){
		x = b;
	}
	if (x > c){
		x = c;
	}
	cout << x;
return 0;
}