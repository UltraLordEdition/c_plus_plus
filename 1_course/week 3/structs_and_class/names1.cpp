#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <cmath>
#include <cctype>

using namespace std;

string FindNameByYear(const map<int, string>& names, int year)
{
	string name;
	for (const auto& item : names)
	{
		if (item.first <= year)
		{
			if (item.second.empty())
			{
				name = name;
			}
			else
			{
				name = item.second;
			}
		}
	}
	return name;
}

class Person
{
public:
	void ChangeFirstName(int year, const string& first_name)
	{
		FirstName[year] = first_name;
	}

	void ChangeLastName(int year, const string& last_name)
	{
		LastName[year] = last_name;
	}

	string GetFullName(int year)
	{
		const string first_name = FindNameByYear(FirstName, year);
		const string last_name = FindNameByYear(LastName, year);

		if (first_name.empty() && last_name.empty())
		{
			return "Incognito";
		}
		else if (first_name.empty())
		{
			return last_name + " with unknown first name";
		}
		else if (last_name.empty())
		{
			return first_name + " with unknown last name";
		}
		return (first_name + " " + last_name);
	}
private:
	map<int, string> FirstName;
	map<int, string> LastName;
};