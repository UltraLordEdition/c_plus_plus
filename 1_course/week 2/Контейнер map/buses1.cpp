#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

bool buses_for_stop(const map<int, map<string, vector<string>>>& bus_cell, string stop)
{
	bool no_stop = false;
	for (const auto& item : bus_cell)					//сканируем €чейку маршрута
	{
		for (const auto& item1 : item.second)			//сканируем маршруты
		{
			for (const string& item2 : item1.second)	//провер€ем остановки  в маршруте
			{
				if (item2 == stop)
				{
					cout << item1.first << " ";
					no_stop = true;
					break;
				}
			}
		}
	}
	return no_stop;
}

bool stops_for_bus(const map<int, map<string, vector<string>>>& bus_cell, string stop)
{
	bool no_interchang = false;
	int id_marshut;
	vector<string> new_stops;
	map<int, map<string, vector<string>>> new_bus_cell;

	for (const auto& item : bus_cell)					//сканируем €чейку маршрута
	{
		for (const auto& item1 : item.second)			//сканируем маршруты
		{
			if (item1.first == stop)
			{
				id_marshut = item.first;
				for (const string& item2 : item1.second)
				{
					new_stops.push_back(item2);
				}
			}
		}
	}
	new_bus_cell = bus_cell;
	new_bus_cell.erase(id_marshut);
	for (const auto& zaeblo : new_stops)
	{
		cout << "Stop " << zaeblo << ": ";
		if (buses_for_stop(new_bus_cell, zaeblo) == true)
		{
			no_interchang = true;
			cout << endl;
		}
		else
		{
			cout << "no interchange" << endl;
		}
	}

	return no_interchang;
}

map<string, vector<string>> marshruts(const map<int, map<string, vector<string>>>& bus_cell)	//массив маршрутов
{
	map<string, vector<string>> marshruts;
	for (const auto& item2 : bus_cell)					//сканируем €чейку маршрута
	{
		for (const auto& item3 : item2.second)			//сканируем маршруты
		{
			marshruts[item3.first] = item3.second;
		}
	}
	return marshruts;
}

void all_buses(const map<int, map<string, vector<string>>>& bus_cell)
{
	if (marshruts(bus_cell).empty() == true)
	{
		cout << "No buses" << endl;
	}
	else
	{
		for (const auto& item : marshruts(bus_cell))
		{
			cout << "Bus " << item.first << ": ";
			for (const auto& item1 : item.second)
			{
				cout << item1 << " ";
			}
			cout << endl;
		}
	}
}

int main() {
	int n;
	cin >> n;
	int id = 0; //счетчик маршрутов автобусов
	map<int, map<string, vector<string>>> bus_cell;

	for (int i = 0; i<n; ++i)
	{
		string operation_code;
		cin >> operation_code;

		if (operation_code == "NEW_BUS")
		{
			int stop_count;
			string bus;
			cin >> bus >> stop_count;
			vector<string> stop(stop_count);
			map<string, vector<string>> marsruts;

			for (string& s : stop)
			{
				cin >> s;
			}
			marsruts[bus] = stop;
			bus_cell[id] = marsruts;
			++id;
		}
		else if (operation_code == "BUSES_FOR_STOP")
		{
			string stop;
			cin >> stop;

			if (buses_for_stop(bus_cell, stop) == true)
			{
				cout << endl;
			}
			else
			{
				cout << "No stop" << endl;
			}

		}
		else if (operation_code == "STOPS_FOR_BUS")
		{
			string bus;
			cin >> bus;
			if (marshruts(bus_cell).count(bus) == true)
			{
				stops_for_bus(bus_cell, bus);
			}
			else
			{
				cout << "No bus" << endl;
			}

		}
		else if (operation_code == "ALL_BUSES")
		{
			all_buses(bus_cell);
		}
	}
	return 0;
}


