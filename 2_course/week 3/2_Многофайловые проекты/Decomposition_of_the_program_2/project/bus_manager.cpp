#include "bus_manager.h"

void BusManager::AddBus(const string& bus, const vector<string>& stops)
{
    buses_to_stops[bus] = stops;
    for (const string& stop : buses_to_stops[bus])
    {
        stops_to_buses[stop].push_back(bus);
    }
}

BusesForStopResponse BusManager::GetBusesForStop(const string& stop) const
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

StopsForBusResponse BusManager::GetStopsForBus(const string& bus) const
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


AllBusesResponse BusManager::GetAllBuses() const
{
    AllBusesResponse q;
    q.b_t_s = buses_to_stops;
    if (q.b_t_s.empty())
    {
        q.status = "No buses";
    }
return q;
}