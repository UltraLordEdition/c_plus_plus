#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <cmath>
#include <cctype>

using namespace std;

class SortedStrings
{
public:
	void AddString(const string& s)
	{
		str.push_back(s);
	}

	vector<string> GetSortedStrings()
	{
		sort(begin(str), end(str));
		return str;
	}
private:
	vector<string> str;
};