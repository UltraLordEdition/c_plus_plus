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
	ofstream output("output.txt");
	string line;
	if (input.is_open())
	{
		while(getline(input, line))
		{
			output << line << endl;
		}
	}
	else
	{
		cout << "Error" << endl;
	}
	return 0;
}