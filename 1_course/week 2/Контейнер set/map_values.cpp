#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>


using namespace std;

set<string> BuildMapValuesSet(const map<int, string>& m)
{
	set<string> stroka;
	for(const auto& x : m)
	{
		stroka.insert(x.second);
	}
	return stroka;
}