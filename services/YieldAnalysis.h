#ifndef YIELDANALYSIS_H
#define YIELDANALYSIS_H

#include "../models/Yield.h"
#include <vector>
#include <string>

class YieldAnalysis {
public:
    void searchByCrop(const std::vector<Yield>& records, std::string cropName);

    void displayYieldStatistics(
        const std::vector<Yield>& records,
        std::string cropName
    );

    void compareCropYields(
        const std::vector<Yield>& records,
        const std::vector<std::string>& cropNames
    );
};

#endif