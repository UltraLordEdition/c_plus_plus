#include "stdafx.h"
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <fstream>
#include <limits>
#include <tuple>
#include <utility>

using namespace std;

class Cities
{
public:
    tuple<bool, string> FindCountry(const string& city) const
    {
        if (city_to_country.count(city) == 1)
        {
            return {true, city_to_country.at(city)};
        }
        else if(amgiguous_cities.count(city) == 1)
        {
            return {false, "Ambiguose"};
        }
        else
        {
            return { false, "Not exist" };
        }

    }
private:
    map<string, string> city_to_country;
    set<string> amgiguous_cities;
};

int main()
{
    Cities cities;
    bool success;
    string message;
    
    //Плохой вариант
    auto t = cities.FindCountry("Volgograd");
    cout << get<1>(t) << endl;
        
    //Уже по лучше
    tie(success,message) = cities.FindCountry("Volgograd");     
    cout << success << " " << message << endl;
    
    //Самый лучший вариант (стандарт С++ 17)
    auto[suc,mes] = cities.FindCountry("Volgograd");
    cout << suc << " " << mes << endl;

    return 0;
}