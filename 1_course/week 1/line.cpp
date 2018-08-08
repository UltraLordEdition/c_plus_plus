#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void  do_operation(const string& operation, const int& persons, vector<bool>& tail)
{
	if (operation == "WORRY")
	{
		tail[persons] = true;
		return;
	}
	if (operation == "QUIET")
	{
		tail[persons] = false;
		return;
	}
	if (operation == "COME")
	{
		tail.resize(tail.size() + (persons));
		return;
	}
}
int main()
{
	int quantity;
	int persons = 0;
	int a = 0;
	string operation;
	vector<bool> tail(0, false);
	cin >> quantity;
	for (int i = 0; i < quantity; i++)
	{
		cin >> operation;
		if (operation == "WORRY_COUNT")
		{
			a = 0;
			for (auto s : tail)
			{
				if (s == true)
				{
					++a;
				}
			}
			cout << a << endl;
			}
		else
		{
			cin >> persons;
			do_operation(operation, persons, tail);
		}
	}

	return 0;
}

