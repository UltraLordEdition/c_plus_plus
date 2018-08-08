#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

void add(size_t& day_index, string& day_work, vector<string>& month)
{
	month[day_index] += day_work + " ";
}

int quantity_task(const vector<string>& month, const size_t& f)
{
	int task=0;
	for (auto d : month[f])
	{
		if (d == ' ')
		{
			++task;
		}
	}
	return task;
}

int main()
{
	int q;
	cin >> q;

	vector<size_t> days_in_months = {28,31,30,31,30,31,31,30,31,30,31,31};
	vector<string> month(32);

	size_t s = 32, count = 0;

	for (int i=0; i<q; ++i)
	{
		string operation_code;
		cin >> operation_code;

		if(operation_code == "ADD")
			{
				size_t day_index;
				string day_work;
				cin >> day_index >> day_work;
				add(day_index,day_work,month);
			}
			else if(operation_code == "NEXT")
			{
				if (count >= days_in_months.size())
				{
					count = 0;
				}
				s  = days_in_months[count];
				if (month.size() > s)
					{
						for (size_t last_days = s+1; last_days < month.size(); ++last_days)
						{
							if (month[last_days] != "\0")
							{
								month[s] += month[last_days];
							}
						}
						month.resize(s+1);
					}
					else
					{
						month.resize(s+1);
					}
					count++;



			}
			else if (operation_code == "DUMP")
			{
				size_t f;
				int a;
				cin >> f;
				a = quantity_task(month, f);
				cout << a << " " << month[f] << endl;
			}
		}
	return 0;
}
