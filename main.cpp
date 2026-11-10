#include <bits/stdc++.h>
using namespace std;

#include "structures/KDTree.h"
#include "structures/SoilKDTree.h"
#include "structures/HashMap.h"
#include "services/Advisory.h"

// Global data structures
KDTree weatherTree;
SoilKDTree soilTree;
HashMap cropMap;

Advisory advisory;


// Initialize sample data
void initializeData() {

    // Weather observations
    Weather w1 = {"W1", 28.60, 77.20, 32, 60, 5};
    Weather w2 = {"W2", 28.70, 77.30, 35, 65, 2};
    Weather w3 = {"W3", 28.50, 77.10, 29, 70, 8};

    weatherTree.insert(w1);
    weatherTree.insert(w2);
    weatherTree.insert(w3);


    // Soil observations
    Soil s1 = {"S1", 28.60, 77.20, 6.5, 40, 50, 30, 40};
    Soil s2 = {"S2", 28.70, 77.30, 7.0, 45, 60, 35, 45};
    Soil s3 = {"S3", 28.50, 77.10, 6.8, 35, 55, 25, 50};

    soilTree.insert(s1);
    soilTree.insert(s2);
    soilTree.insert(s3);


    // Disease information
    Disease d1 = {
        "Rust",
        "Yellow-orange spots on leaves",
        "Follow recommended rust management practices"
    };

    Disease d2 = {
        "Smut",
        "Dark fungal spores",
        "Use certified disease-free seeds"
    };

    Disease d3 = {
        "Blast",
        "Lesions on rice leaves",
        "Follow recommended blast management practices"
    };

    cropMap.insert("Wheat", d1);
    cropMap.insert("Wheat", d2);
    cropMap.insert("Rice", d3);
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


void adminPanel() {
    cout << "\n--- ADMIN PANEL ---\n";
}

void spatialSearch() {
    cout << "\n--- SPATIAL SEARCH ---\n";
}

void performanceAnalysis() {
    cout << "\n--- PERFORMANCE ANALYSIS ---\n";
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
        cout << "3. Spatial Search\n";
        cout << "4. Performance Analysis\n";
        cout << "5. Exit\n";

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
                spatialSearch();
                break;

            case 4:
                performanceAnalysis();
                break;

            case 5:
                cout << "\nExiting Program...\n";
                break;

            default:
                cout << "\nInvalid Choice!\n";
        }

    } while (choice != 5);

    return 0;
}

