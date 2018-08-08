#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <cmath>
#include <cctype>

using namespace std;

string sort(const string& first_name, const string& last_name)
{
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
	else
	{
		return (first_name + " " + last_name);
	}
}

string FindAllNameByYear(const map<int, string>& names, int year)
{
	vector<string> name;
	string help;
	for (const auto& item : names)
	{
		if (item.first <= year)
		{
			if (item.second.empty() == false)
			{
				name.push_back(item.second);
			}
		}
		else
		{
			break;
		}
	}
	reverse(begin(name), end(name));
	if (name.size() > 2)
	{
		for (size_t i = 1; i <= name.size() - 1; ++i)
		{
			if (name[i] != name[i-1])
			{
				help += name[i];
				if (i != name.size() - 1)
				{
					help += ", ";
				}
			}
		}
		if (help.empty())
		{
			return name[0];
		}
		else
		{
			return name[0] + " (" + help + ")";
		}
	}
	else if(name.size() == 2)
	{
		if (name[0] != name[1])
		{
			help = name[0] + " (" + name[1] + ")";
		}
		else
		{
			return name[0];
		}
	}
	else if(name.size() == 1)
	{
		help = name[0];
	}
	return help;
}

string FindNameByYear(const map<int, string>& names, int year)
{
	string name;
	for (const auto& item : names)
	{
		if (item.first <= year)
		{
			if (item.first <= year)
			{
				name = item.second;
			}
			else
			{
				break;
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

		return sort(first_name, last_name);
	}

	string GetFullNameWithHistory(int year)
	{
		string first_name = FindAllNameByYear(FirstName, year);
		string last_name = FindAllNameByYear(LastName, year);

		return sort(first_name, last_name);
	}

private:
	map<int, string> FirstName;
	map<int, string> LastName;
};
