#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

struct BusesForStopResponse
{
    string status;
    string stop;
    vector<string> vector_s_t_b;
    map<string, vector<string>> map_b_t_s;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r);

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

ostream& operator << (ostream& os, const StopsForBusResponse& r);

struct AllBusesResponse
{
    string status;
    map<string, vector<string>> b_t_s;
};

ostream& operator << (ostream& os, const AllBusesResponse& r);