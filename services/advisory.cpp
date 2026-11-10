#include "Advisory.h"
#include <iostream>
using namespace std;

void Advisory::generateAdvisory(
    Farm farm,
    KDTree& weatherTree,
    SoilKDTree& soilTree,
    HashMap& cropMap
) {

    cout << "\n====================================\n";
    cout << "       FARMER ADVISORY REPORT\n";
    cout << "====================================\n";

    cout << "Farmer Name: " << farm.farmerName << endl;
    cout << "Crop: " << farm.cropName << endl;
    cout << "Location: " << farm.latitude
         << ", " << farm.longitude << endl;

    // 1. Find nearest weather station

    Weather weather;
    int weatherVisited = 0;

    cout << "\n--- WEATHER INFORMATION ---\n";

    if (weatherTree.nearestNeighbor(
        farm.latitude, farm.longitude,
        weather, weatherVisited
    )) {

        cout << "Station ID: " << weather.id << endl;
        cout << "Temperature: " << weather.temperature << " C\n";
        cout << "Humidity: " << weather.humidity << "%\n";
        cout << "Rainfall: " << weather.rainfall << endl;

        cout << "\nWeather Advisory:\n";

        if (weather.temperature > 35) {
            cout << "- High temperature detected.\n";
        }
        else if (weather.temperature < 10) {
            cout << "- Low temperature detected.\n";
        }
        else {
            cout << "- Temperature is within the demo's normal range.\n";
        }

        if (weather.humidity > 80) {
            cout << "- High humidity may favor fungal diseases.\n";
        }

        if (weather.rainfall < 5) {
            cout << "- Low recorded rainfall. Check irrigation needs.\n";
        }

    }
    else {
        cout << "No weather data available.\n";
    }

    cout << "Weather nodes visited: " << weatherVisited << endl;


    // 2. Find nearest soil observation

    Soil soil;
    int soilVisited = 0;

    cout << "\n--- SOIL INFORMATION ---\n";

    if (soilTree.nearestNeighbor(
        farm.latitude, farm.longitude,
        soil, soilVisited
    )) {

        cout << "Soil Observation ID: " << soil.id << endl;
        cout << "pH: " << soil.pH << endl;
        cout << "Moisture: " << soil.moisture << endl;
        cout << "Nitrogen: " << soil.nitrogen << endl;
        cout << "Phosphorus: " << soil.phosphorus << endl;
        cout << "Potassium: " << soil.potassium << endl;

        cout << "\nSoil Advisory:\n";

        if (soil.pH < 5.5) {
            cout << "- Soil is acidic according to the demo threshold.\n";
        }
        else if (soil.pH > 7.5) {
            cout << "- Soil is alkaline according to the demo threshold.\n";
        }
        else {
            cout << "- Soil pH is within the demo's target range.\n";
        }

        if (soil.moisture < 20) {
            cout << "- Soil moisture is low. Check irrigation requirements.\n";
        }

    }
    else {
        cout << "No soil data available.\n";
    }

    cout << "Soil nodes visited: " << soilVisited << endl;


    // 3. Search crop-related diseases using Hash Map

    cout << "\n--- CROP DISEASE INFORMATION ---\n";

    vector<Disease> diseases = cropMap.search(farm.cropName);

    if (diseases.empty()) {

        cout << "No disease information available for this crop.\n";

    }
    else {

        for (auto d : diseases) {

            cout << "\nDisease: " << d.diseaseName << endl;
            cout << "Symptoms: " << d.symptoms << endl;
            cout << "Advisory: " << d.advisory << endl;

        }

    }

    cout << "\n====================================\n";
}

