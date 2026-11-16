#include "YieldAnalysis.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <limits>

using namespace std;

// Convert crop names to lowercase for case-insensitive comparison
string toLower(string s) {
    transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c) {
            return tolower(c);
        });

    return s;
}

// Feature 1: Search records by crop
void YieldAnalysis::searchByCrop(
    const vector<Yield>& records,
    string cropName
) {
    bool found = false;

    cout << "\n--- YIELD RECORDS FOR " << cropName << " ---\n";

    for (const Yield& y : records) {
        if (toLower(y.cropName) == toLower(cropName)) {
            cout << "\nRecord ID: " << y.id;
            cout << "\nYear: " << y.year;
            cout << "\nSeason: " << y.season;
            cout << "\nArea: " << y.area << " hectares";
            cout << "\nProduction: " << y.production << " tonnes";
            cout << "\nYield: " << y.yieldValue << " tonnes/hectare\n";

            found = true;
        }
    }

    if (!found) {
        cout << "No yield records found for this crop.\n";
    }
}

// Feature 2 and 3: Average, maximum and minimum yield
void YieldAnalysis::displayYieldStatistics(
    const vector<Yield>& records,
    string cropName
) {
    double total = 0;
    double maxYield = numeric_limits<double>::lowest();
    double minYield = numeric_limits<double>::max();

    int count = 0;
    string maxRecord, minRecord;

    for (const Yield& y : records) {
        if (toLower(y.cropName) == toLower(cropName)) {
            total += y.yieldValue;
            count++;

            if (y.yieldValue > maxYield) {
                maxYield = y.yieldValue;
                maxRecord = y.id;
            }

            if (y.yieldValue < minYield) {
                minYield = y.yieldValue;
                minRecord = y.id;
            }
        }
    }

    if (count == 0) {
        cout << "\nNo yield records found for " << cropName << ".\n";
        return;
    }

    cout << fixed << setprecision(2);

    cout << "\n--- YIELD STATISTICS: " << cropName << " ---\n";
    cout << "Total records: " << count << "\n";
    cout << "Average yield: " << total / count << " tonnes/hectare\n";
    cout << "Maximum yield: " << maxYield << " tonnes/hectare";
    cout << " (Record: " << maxRecord << ")\n";
    cout << "Minimum yield: " << minYield << " tonnes/hectare";
    cout << " (Record: " << minRecord << ")\n";
}

// Feature 4: Compare average yield across crops
void YieldAnalysis::compareCropYields(
    const vector<Yield>& records,
    const vector<string>& cropNames
) {
    cout << "\n--- CROP YIELD COMPARISON ---\n";
    cout << fixed << setprecision(2);

    for (const string& crop : cropNames) {
        double total = 0;
        int count = 0;

        for (const Yield& y : records) {
            if (toLower(y.cropName) == toLower(crop)) {
                total += y.yieldValue;
                count++;
            }
        }

        cout << "\nCrop: " << crop;

        if (count == 0) {
            cout << "\nNo records available.\n";
        } else {
            cout << "\nAverage yield: "
                 << total / count << " tonnes/hectare\n";
        }
    }
}