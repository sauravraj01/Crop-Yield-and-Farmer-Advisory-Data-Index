
#ifndef DATALOADER_H
#define DATALOADER_H

#include "../models/Yield.h"
#include "../structures/HashMap.h" // disease
#include "../structures/KDTree.h" // weather
#include "../structures/SoilKDTree.h" // soil
#include <string>

int loadWeatherData(const std::string& filename, KDTree& weatherTree);

int loadSoilData(const std::string& filename, SoilKDTree& soilTree);

int loadDiseaseData(const std::string& filename, HashMap& cropMap);

int loadYieldData(
    const string& filename,
    vector<Yield>& yieldRecords
);

#endif
