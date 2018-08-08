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
	int N = 0;
	int M = 0;
	int value;
	if (input.is_open())
	{
		input >> N;
		input.ignore(1);
		input >> M;
		for (int a = 0; a < N; ++a)
		{
			for (int i = 0; i < M; ++i)
			{
				input >> value;
				input.ignore(1);
				cout << setw(10) << value;
				if (i < (M - 1))
				{
					cout << " ";
				}
			}
			cout << endl;
		}
	}
	else
	{
		cout << "Error" << endl;
	}

	return 0;
}