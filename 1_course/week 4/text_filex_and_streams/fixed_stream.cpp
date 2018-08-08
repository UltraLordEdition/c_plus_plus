#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <cmath>
#include <cctype>
#include <fstream>
#include <iomanip>

using namespace std;

int main()
{
	ifstream input("input.txt");
	double value;
	if (input.is_open())
	{
		cout << fixed << setprecision(3);
		while (input >> value)
		{
			cout << value << endl;
		}

	}
	else
	{
		cout << "Error" << endl;
	}
	return 0;
}