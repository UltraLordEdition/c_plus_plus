#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <cmath>


using namespace std;

void print(const vector<int>& v)
{
	for (auto i : v)
	{
		cout << i << " ";
	}
}

int main()
{
	int n;
	cin >> n;
	vector<int> numbers(n);
	for (auto& item : numbers)
	{
		cin >> item;
	}
	sort(begin(numbers), end(numbers),
		[](int i, int j) {
		return abs(i) < abs(j);
		});
	print(numbers);
	return 0;
}
