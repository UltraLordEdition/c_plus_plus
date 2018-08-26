#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
    string operation_code;
    is >> operation_code;
    if (operation_code == "NEW_BUS")
    {
        q.type = QueryType::NewBus;
        cin >> q.bus;
        int stop_count;
        cin >> stop_count;
        q.stops.resize(stop_count);
        for (auto& stop : q.stops)
        {
            cin >> stop;
         
        }

    }
    else if (operation_code == "BUSES_FOR_STOP")
    {
        q.type = QueryType::BusesForStop;
        cin >> q.stop;
    }
    else if (operation_code == "STOPS_FOR_BUS")
    {
        q.type = QueryType::StopsForBus;
        cin >> q.bus;
    }
    else if (operation_code == "ALL_BUSES")
    {
        q.type = QueryType::AllBuses;
    }

    return is;
}


struct BusesForStopResponse 
{
    string status;
    string stop;
    vector<string> vector_s_t_b;
    map<string, vector<string>> map_b_t_s;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r)
{
    if (r.status == "No stop") 
    {
        os << "No stop" << endl;
    }
    else
    {
       for (const string& bus : r.vector_s_t_b)
        {
            os << bus << " ";
        }
        os << endl;
    }
return os;
}

struct StopsForBusResponse
{
    string stutus;
    string bus;
    vector<string> vector_b_t_s;
    map<string, vector<string>> map_b_t_s;
    vector<string> vector_s_t_b;
    vector<string> stops;
    map<string, vector<string>> map_s_t_b;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r)
{
    if (r.stutus == "No bus")
    {
        os << "No bus" << endl;
    }
    else
    {
        for (const string& stop : r.vector_b_t_s)
        {
            os << "Stop " << stop << ": ";
            if (r.map_s_t_b.at(stop).size() == 1)
            {
                os << "no interchange";
            }
            else
            {
                for (const string& other_bus : r.map_s_t_b.at(stop))
                {
                    if (r.bus != other_bus)
                    {
                        os << other_bus << " ";
                    }
                }
            }
            os << endl;
        }
    }
    return os;
}


struct AllBusesResponse
{
    string status;
    map<string, vector<string>> b_t_s;
};

ostream& operator << (ostream& os, const AllBusesResponse& r)
{
    if (r.status == "No buses")
    {
        os << "No buses" << endl;
    }
    else
    {
        for (const auto& bus_item : r.b_t_s)
        {
            os << "Bus " << bus_item.first << ": ";
            for (const string& stop : bus_item.second)
            {
                os << stop << " ";
            }
            os << endl;
        }
    }

    return os;
}

class BusManager {
public:

    void AddBus(const string& bus, const vector<string>& stops)
    {
        buses_to_stops[bus] = stops;
        for (const string& stop : buses_to_stops[bus]) 
        {
            stops_to_buses[stop].push_back(bus);
        }

    }
    
    BusesForStopResponse GetBusesForStop(const string& stop) const 
    {
        BusesForStopResponse q;
        q.stop = stop;
        q.map_b_t_s = stops_to_buses;
        q.vector_s_t_b = q.map_b_t_s[stop];
        if (stops_to_buses.count(stop) == 0)
        {
            q.status = "No stop";
        }
        
        return q;
    }
    
    StopsForBusResponse GetStopsForBus(const string& bus) const
    {
        StopsForBusResponse q;
        q.bus = bus;
        q.map_b_t_s = buses_to_stops;
        q.vector_b_t_s = q.map_b_t_s[bus];
        q.map_s_t_b = stops_to_buses;
        if (buses_to_stops.count(bus) == 0)
        {
            q.stutus = "No bus";
        }
        return q;
    }
    

    AllBusesResponse GetAllBuses() const
    {
        AllBusesResponse q;
        q.b_t_s = buses_to_stops;
        if (q.b_t_s.empty())
        {
            q.status = "No buses";
        }
        return q;
    }

private:

    map<string, vector<string>> buses_to_stops, stops_to_buses;
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
     
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
        case QueryType::NewBus:
            bm.AddBus(q.bus, q.stops);
            break;
        case QueryType::BusesForStop:
            cout << bm.GetBusesForStop(q.stop) << endl;
            break;
        case QueryType::StopsForBus:
            cout << bm.GetStopsForBus(q.bus) << endl;
            break;
        case QueryType::AllBuses:
            cout << bm.GetAllBuses() << endl;
            break;
        }
    }

    return 0;
}

