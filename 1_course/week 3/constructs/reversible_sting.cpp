#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <cmath>
#include <cctype>

using namespace std;

class ReversibleString
{
public:
	ReversibleString()	{}
	ReversibleString(const string& new_str)
	{
		str = new_str;
	}
	void Reverse()
	{
		reverse(begin(str), end(str));

	}
	string ToString() const
	{
		return str;
	}
private:
	string str;
};