#include "stdafx.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <cmath>
#include <cctype>

using namespace std;

int ComputeDistance(const string& source, const string& destination)
{
	return source.length() - destination.length();
}

class Route {
public:
	Route()									//Конструктор по умолчанию
	{
		source = "Moscow";
		destination = "Saint Petersburg";
		UpdateLength();
		cout << "Default constructed\n";
	}
	Route(const string& new_source,			//Конструктор параметризованный
		const string& new_destination)
	{
		source = new_source;
		destination = new_destination;
		UpdateLength();
		cout << "Counstructed\n";
	}
	~Route()								//Деструктор
	{
		//for (const string& entry : compute_distance_log)
		//cout << entry << endl;
		cout << "Destructed\n";
	}
	string GetSource() const
	{
		return source;
	}
	string GetDestination() const
	{
		return destination;
	}
	int GetLength() const
	{
		return length;
	}

	void SetSource(const string& new_source)
	{
		source = new_source;
		UpdateLength();
	}
	void SetDestination(const string& new_destination)
	{
		destination = new_destination;
		UpdateLength();
	}
private:
	string source;
	string destination;
	int length;
	vector<string> compute_distance_log;

	void UpdateLength()
	{
		length = ComputeDistance(source, destination);
		compute_distance_log.push_back(source + " - " + destination);
	}
};

void PrintRoute(const Route& route)
{
	cout << route.GetSource() << " - " << route.GetDestination() << endl;
}

void ReverseRoute(Route& route)
{
	string old_source = route.GetSource();
	string old_destination = route.GetDestination();
	route.SetSource(old_destination);
	route.SetDestination(old_source);
}

void Worthless(Route route)
{
	cout << 2 << "\n";
}
Route GetRoute()
{
	cout << 1 << "\n";
	return {};
}

int main()
{
	/*
	Route route("Moscow", "Saint Petersburg");
	route.SetSource("Vyborg");
	route.SetDestination("Vologda");
	*/
	/*
	cout << 1 << endl;
	Route route;
	cout << 2 << endl;
	return 0;
	*/
	/*
	for (int i : {0, 1})
	{
		cout << "Step " << i << ": " << 1 << "\n";
		Route route;
		cout << "Step " << i << ": " << 2 << "\n";
	}
	cout << "End\n";
	return 0;
	*/
	/*
	cout << 1 << "\n";
	Route first_route;
	if (false)
	{
		cout << 2 << "\n";
		return 0;
	}
	cout << 3 << "\n";
	Route second_route;
	cout << 4 << "\n";
	return 0;
	*/
	/*
	cout << 1 << "\n";
	Worthless({});
	cout << 3 << "\n";
	return 0;
	*/
	GetRoute();
	cout << 2 << "\n";
	return 0;
}
/*
int main()
{
	Route route;
	PrintRoute(route);
	route.SetSource("Moscow");
	route.SetDestination("Vologda");
	ReverseRoute(route);
	PrintRoute(route);

	Route route1;
	PrintRoute(route1);

	Route route2("Zvenigorod", "Istra");
	PrintRoute(route2);

	PrintRoute(Route());	//По умолчанию
	PrintRoute({});

	PrintRoute(Route("Seversk", "Tomsk"));	//Параметризованный
	PrintRoute({ "Seversk", "Tomsk" });

	vector<Route>	routes;
	routes.push_back({ "Seversk", "Tomsk" });

	return 0;
}
*/
//Пример использования конструктора
Route Getoute(bool is_empty)
{
	if (is_empty)
	{
		return {};
	}
	else
	{
		return { "Seversk", "Tomsk" };
	}
}

vector<int> GetNumbers(bool is_empty)
{
	if (is_empty)
	{
		return {};
	}
	else
	{
		return { 8,6,9,6 };
	}
}