#include "responses.h"

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