#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <cmath>
#include <cctype>


using namespace std;

void print(const vector<string>& v)
{
	for (const auto& i : v)
	{
		cout << i << " ";
	}
}

int main()
{
	int n;
	cin >> n;
	vector<string> stroks(n);
	for (auto& item : stroks)
	{
		cin >> item;
	}
	sort(begin(stroks), end(stroks),
		[](string a, string b) {
		for (char& i : a) { i = tolower(i);}
		for (char& j : b) { j = tolower(j);}
		return a < b;
		});

	print(stroks);
	return 0;
}