#include "stdafx.h"
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

void Print(const vector<string>& names, const vector<double>& values, int width)
{
	ofstream output("list.txt");
	output << setfill('-');					//��������� ����� ����������� �������� '-'
	output << left;							//������� ����� � ���� �� �����
	for (const auto& n : names)
	{
		output << setw(width) << n << ' ';
		cout << setw(width) << n << ' ';
	}
	output << endl;
	cout << endl;
	cout << fixed << setprecision(5);		//����� ����� � ������������� ������, ���������� ������ ����� ������� 5
											//cout << setw(10);						//����������� ������������ ����� ��� ����������
	output << fixed << setprecision(5);
	for (const auto& v : values)
	{
		output << setw(width) << v << ' ';
		cout << setw(width) << v << ' ';
	}
}

int main()
{
	vector<string> names = { "a","b","c" };
	vector<double> values = { 5, 0.01, 0.00001 };
	Print(names, values, 10);

	return 0;
}