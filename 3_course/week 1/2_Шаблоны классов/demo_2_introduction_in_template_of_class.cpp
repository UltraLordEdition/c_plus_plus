#include <iostream>
#include <vector>

using namespace std;
  
struct PairOfStringAndInt {
	string first;
	int second;
};

template <typename T, typename U>	//Шаблон класса
struct Pair {
	T first;
	U second;
};

int main() {
	Pair<string, int> si; //  класс самостостельный тип (инстанцирование)
	si.first = "Hello";
	si.second = 5;

	Pair<bool, char> bc;
	bc.first = true;
	bc.second = 'z';
}