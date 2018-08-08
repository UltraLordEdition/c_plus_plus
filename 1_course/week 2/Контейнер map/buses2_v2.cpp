#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

int main()
{
	int N = 0;
	int n;
	cin >> n;
	map<vector<string>, int> bus;

	for (int i = 0; i < n; ++i)
	{
		int quantity_stops;
		cin >> quantity_stops;
		vector<string> stops(quantity_stops);

		for (auto& i : stops)
		{
			cin >> i;
		}
		if (bus.count(stops) == 0)
		{
			int new_value = bus.size() + 1;
			bus[stops] = new_value;
			cout << "New bus " << new_value << endl;
		}
		else
		{
			cout << "Already exists for " << bus[stops] << endl;
		}
	}
	return 0;
}
