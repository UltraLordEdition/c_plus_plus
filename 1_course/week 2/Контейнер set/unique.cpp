#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>


using namespace std;

int main()
{
	int n;
	cin >> n;

	set<string> stroka;

	for (int i = 0; i < n; ++i)
	{
		string operation_code;
		cin >> operation_code;
		stroka.insert(operation_code);
	}
	cout << stroka.size() << endl;
	return 0;
}
