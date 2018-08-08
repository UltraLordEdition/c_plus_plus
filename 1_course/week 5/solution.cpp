#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;
#define MONTHs	12
#define DAYs	31

// –еализуйте функции и методы классов и при необходимости добавьте свои
class Date {
public:
	Date()
	{
		year = 0;
		month = 1;
		day = 1;
	}
	Date(int one, int two, int three)
	{
		year = one;
		month = two;
		day = three;
		if (month>MONTHs || month<1)
		{
			string error = "Month value is invalid: " + to_string(month);
			throw out_of_range(error);
		}
		else if (day>DAYs || day<1)
		{
			string error = "Day value is invalid: " + to_string(day);
			throw out_of_range(error);
		}
	}

	int GetYear() const
	{
		return year;
	}

	int GetMonth() const
	{
		return month;
	}

	int GetDay() const
	{
		return day;
	}

private:
	int year, month, day;
};

bool operator<(const Date& lhs, const Date& rhs)
{
	return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} <
		vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

class Database {
public:
	void AddEvent(const Date& date, const string& event)
	{
		DB[date].insert(event);
	}

	bool DeleteEvent(const Date& date, const string& event)
	{
		return DB[date].erase(event);
	}


	int  DeleteDate(const Date& date)
	{
		int n = DB[date].size();
		DB.erase(date);
		return n;
	}

	void Find(const Date& date) const
	{
		if (DB.count(date) != 0)
		{
			for (const auto& item : DB.at(date))
			{
				cout << item << endl;
			}
		}
	}

	void Print() const
	{
		cout << setfill('0');
		for (const auto& x : DB)
		{
			for (const auto& y : x.second)
			{
				cout << setw(4) << x.first.GetYear() << "-"
					 << setw(2) << x.first.GetMonth() << "-"
					 << setw(2) << x.first.GetDay() << " ";
				cout << y << endl;
			}
		}
	}
private:
	map<Date, set<string>> DB;
};

istream& operator>>(istream& stream, Date& d)
{
	int year, month, day;
	char ch;
	vector<bool> error(4);

	string ss;
	stringstream str;
	stream >> ss;

	str << ss;
	str >> year;
	if (year >= 10000)
	{
		error[0] = true;
	}
	str.get(ch);
	if (ch != '-')
	{
		error[1] = true;
	}
	str >> month;
	str.get(ch);
	if (ch != '-')
	{
		error[2] = true;
	}
	str >> day;
	if (str.eof() != true)
	{
		error[3] = true;
	}
	if (error[0] || error[1] || error[2] || error[3] == true)
	{
		throw invalid_argument("Wrong date format: " + ss);
	}
	d = {year, month, day};
	return stream;
}

int main() {
	Database db;

	string command;
	stringstream str;
	string date;
	Date d;
	try {
		while (getline(cin, command)) {
			// —читайте команды с потока ввода и обработайте каждую
			stringstream str;
			str << command;
			str >> command;
			if (command == "Add")
			{
				string event;
				str >> d >> event;
				db.AddEvent(d, event);
			}
			else if (command == "Del")
			{
				string event;
				str >> d >> event;
				if (!event.empty())
				{
					if (db.DeleteEvent(d, event))
					{
						cout << "Deleted successfully" << endl;
					}
					else
					{
						cout << "Event not found" << endl;
					}
				}
				else
				{
					cout << "Deleted " << db.DeleteDate(d) << " events" << endl;
				}
			}
			else if (command == "Find")
			{
				str >> d;
				db.Find(d);
			}
			else if (command == "Print")
			{
				db.Print();
			}
			else
			{
				if (command.empty() != true)
				{
					cout << "Unknown command: " << command << endl;
					return 0;
				}
			}
		}
	}
	catch (const exception& ex)
	{
		cout << ex.what() << endl;
	}
	return 0;
}