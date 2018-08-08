#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int average(vector<int>& a) 
{
	int sum = 0;
	for(auto x : a) 
	{
		sum += x;
	}
	sum = sum / a.size();
	int tmp = 0;
	for (int i = 0; i <= a.size()-1; i++)
	{
		if (a[i] > sum)
		{
			a[tmp] = i;
			tmp++;
		}
	}
	a.resize(tmp);
	return tmp;
}

int main() 
{
	int d;
	int n;
	cin >> n;
	vector<int> quantity(n);
	for(int i=0; i<n; i++) 
	{
		cin >> quantity[i];
	}
	d = average(quantity);
	cout << d << endl;
	for (auto x : quantity)
	{
		cout << x << " ";
	}
	return 0;
}

