#ifndef WEATHER_H
#define WEATHER_H

#include <bits/stdc++.h>
using namespace std;

struct Weather {
    string id;
    double latitude;
    double longitude;

    double temperature;
    double humidity;
    double rainfall;
};

#endif