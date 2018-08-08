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
	map<set<string>, int> bus_stop;
	
	for (int i = 0; i<n; ++i)
	{
		int n;
		cin >> n;
		vector<string> stops(n);
		for (string& i : stops)
		{
			cin >> i;
		}
		set<string> stops_set(begin(stops), end(stops));

		if (bus_stop.count(stops_set) == false)
		{
			const int new_number = bus_stop.size() + 1;
			bus_stop[stops_set] = new_number;
			cout << "New bus " << new_number << endl;
		}
		else
		{
			cout << "Already exists for " << bus_stop[stops_set] << endl;
		}
	}
	return 0;
}
