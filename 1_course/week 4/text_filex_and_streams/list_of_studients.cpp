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

struct Student
{
	string Name;
	string LastName;
	int Day;
	int Month;
	int BirthDay;
};

int main()
{
	int n;
	cin >> n;
	vector<Student> Students(n);
	for(int i=0; i<n; ++i)
	{
		cin >> Students[i].Name 
			>> Students[i].LastName 
			>> Students[i].Day 
			>> Students[i].Month
			>> Students[i].BirthDay;
	}
	int m;
	int K;
	string request;
	cin >> m;
	for(int i=0; i<m; ++i)
	{
		cin >> request >> K;
		K = K - 1;
		if (request == "name" && K<=Students.size())
		{
			cout << Students[K].Name << " " << Students[K].LastName << endl;
		}
		else if (request == "date" && K <= Students.size())
		{
			cout << Students[K].Day << "." << Students[K].Month << "." << Students[K].BirthDay << endl;
		}
		else
		{
			cout << "bad request" << endl;
		}
	}

	return 0;
}