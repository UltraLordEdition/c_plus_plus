#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int Factorial(int x ){
	int fact=1;
	if (x >= 0){
		for (int i = fact; i <= x; ++i){
		fact = fact*i;
			}
		} else{
			return 1;
		}
	return fact;
}