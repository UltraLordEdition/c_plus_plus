#include <iostream>
#include <string>
#include <deque>

using namespace std;

string MakeString(deque<string>& formula)
{
	string str;
	for (auto it : formula)
	{
		str += it;
		formula.pop_front();
	}
	return str;
}

int main()
{
	int x;
	cin >> x;

	int n;
	cin >> n;

	deque<string> formula;
	string symbol = to_string(x);

	for (int i = 0; i < n; ++i)
	{
		formula.push_front("(");
		formula.push_back(symbol);
		formula.push_back(")");
		cin >> symbol;
		cin >> x;		
		symbol = MakeString(formula) + " " + symbol + " " + to_string(x);
	}

	cout << symbol << endl;

	return 0;
}