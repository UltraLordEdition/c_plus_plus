#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

bool already_exists_for(const map<vector<string>, int>& bus, const vector<string>& stops)
{
	for (auto& m : bus)
	{
		if (m.first == stops)
		{
			return true;
		}
	}
	return false;
}


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
		if (already_exists_for(bus, stops))
		{
			cout << "Already exists for " << bus[stops] << endl;
		}
		else
		{
			int new_value = bus.size()+1;
			bus[stops] = new_value;
			cout << "New bus " << new_value << endl;
		}
	}
	return 0;
}
