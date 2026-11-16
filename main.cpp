#include <bits/stdc++.h>
using namespace std;

#include "services/DataLoader.h"
#include "services/YieldAnalysis.h"
#include "structures/KDTree.h"
#include "structures/SoilKDTree.h"
#include "structures/HashMap.h"
#include "services/Advisory.h"

// Global data structures
KDTree weatherTree;
SoilKDTree soilTree;
HashMap cropMap;
YieldAnalysis yieldAnalysis;

Advisory advisory;
vector<Yield> yieldRecords;

// Initialize sample data
void initializeData() {
    loadWeatherData("data/weather.txt", weatherTree);
    loadSoilData("data/soil.txt", soilTree);
    loadDiseaseData("data/diseases.txt", cropMap);
    loadYieldData("data/yield.txt", yieldRecords);

}


// Farmer panel
void farmerPanel() {

    Farm farm;

    cout << "\n========== FARMER PANEL ==========\n";

    cout << "Enter farmer name: ";
    getline(cin, farm.farmerName);

    cout << "Enter crop name: ";
    getline(cin, farm.cropName);

    cout << "Enter latitude: ";
    cin >> farm.latitude;

    cout << "Enter longitude: ";
    cin >> farm.longitude;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    advisory.generateAdvisory(
        farm,
        weatherTree,
        soilTree,
        cropMap
    );
}

void viewAllYieldRecords() {
    cout << "\n========== ALL YIELD RECORDS ==========\n";

    if (yieldRecords.empty()) {
        cout << "No yield records available.\n";
        return;
    }

    for (const Yield& y : yieldRecords) {
        cout << "\nRecord ID: " << y.id;
        cout << "\nCrop: " << y.cropName;
        cout << "\nYear: " << y.year;
        cout << "\nSeason: " << y.season;
        cout << "\nArea: " << y.area << " hectares";
        cout << "\nProduction: " << y.production << " tonnes";
        cout << "\nYield: " << y.yieldValue << " tonnes/hectare\n";
    }

    cout << "\nTotal records: " << yieldRecords.size() << "\n";
}


void adminPanel() {
    int choice;

    do {
        cout << "\n========== ADMIN PANEL ==========\n";
        cout << "1. View All Records\n";
        cout << "2. View Dataset Summary\n";
        cout << "3. Exit to Main Menu\n";

        cout << "\nEnter choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "\n--- DISEASE RECORDS ---\n";
            cropMap.displayAll();

            cout << "\n--- YIELD RECORDS ---\n";
            viewAllYieldRecords();
        }
        else if (choice == 2) {
            cout << "\n========== DATASET SUMMARY ==========\n";
            cout << "Weather Records: 500\n";
            cout << "Soil Records: 500\n";
            cout << "Disease Records: 50\n";
            cout << "Yield Records: " << yieldRecords.size() << "\n";
        }
        else if (choice != 3) {
            cout << "Invalid choice!\n";
        }

    } while (choice != 3);
}


void yieldAnalysisPanel() {
    int choice;

    do {
        cout << "\n========== YIELD ANALYSIS ==========\n";
        cout << "1. Search yield records by crop\n";
        cout << "2. Display yield statistics\n";
        cout << "3. Compare yields across crops\n";
        cout << "4. Back to Main Menu\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        if (choice == 1 || choice == 2) {
            string crop;
            cout << "Enter crop name: ";
            cin >> crop;

            if (choice == 1) {
                yieldAnalysis.searchByCrop(yieldRecords, crop);
            } else {
                yieldAnalysis.displayYieldStatistics(yieldRecords, crop);
            }
        }
        else if (choice == 3) {
            int n;
            cout << "How many crops do you want to compare? ";
            cin >> n;

            if (n <= 0) {
                cout << "Enter a valid number of crops.\n";
                continue;
            }

            vector<string> crops(n);

            for (int i = 0; i < n; i++) {
                cout << "Enter crop " << i + 1 << ": ";
                cin >> crops[i];
            }

            yieldAnalysis.compareCropYields(yieldRecords, crops);
        }
        else if (choice != 4) {
            cout << "Invalid choice.\n";
        }

    } while (choice != 4);
}

int main() {

    initializeData();

    int choice;

    do {

        cout << "\n====================================\n";
        cout << " CROP YIELD & FARMER ADVISORY SYSTEM\n";
        cout << "====================================\n";

        cout << "1. Farmer Panel\n";
        cout << "2. Admin Panel\n";
        cout << "3. Yield Analysis\n";
        cout << "4. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {

            case 1:
                farmerPanel();
                break;

            case 2:
                adminPanel();
                break;
            case 3:
                yieldAnalysisPanel();
                break;
            case 4:
                cout << "\nExiting Program...\n";
                break;

            default:
                cout << "\nInvalid Choice!\n";
        }

    } while (choice != 4);

    return 0;
}

