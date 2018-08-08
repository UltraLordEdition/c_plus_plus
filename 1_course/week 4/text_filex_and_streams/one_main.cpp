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
	string line;
	if (input.is_open())
	{
		while(getline(input, line))
		{
			cout << line << endl;
		}
	}
	else
	{
		cout << "Error" << endl;
	}
	return 0;
}