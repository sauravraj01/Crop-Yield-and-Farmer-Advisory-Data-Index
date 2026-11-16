
#include "DataLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int loadWeatherData(const string& filename, KDTree& weatherTree) {

    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error: Could not open " << filename << endl;
        return -1;
    }

    string line;
    int count = 0;

    while (getline(file, line)) {

        stringstream ss(line);
        string field;
        vector<string> fields;

        while (getline(ss, field, ',')) {
            fields.push_back(field);
        }

        if (fields.size() != 6) {
            cout << "Skipping invalid weather record.\n";
            continue;
        }

        try {
            Weather w;

            w.id = fields[0];
            w.latitude = stod(fields[1]);
            w.longitude = stod(fields[2]);
            w.temperature = stod(fields[3]);
            w.humidity = stod(fields[4]);
            w.rainfall = stod(fields[5]);

            weatherTree.insert(w);
            count++;
        }
        catch (...) {
            cout << "Skipping invalid weather record.\n";
        }
    }

    file.close();

    cout << count << " weather records loaded successfully.\n";

    return count;
}



int loadSoilData(const string& filename, SoilKDTree& soilTree) {

    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error: Could not open " << filename << endl;
        return -1;
    }

    string line;
    int count = 0;

    while (getline(file, line)) {

        stringstream ss(line);
        string field;
        vector<string> fields;

        while (getline(ss, field, ',')) {
            fields.push_back(field);
        }

        if (fields.size() != 8) {
            cout << "Skipping invalid soil record.\n";
            continue;
        }

        try {
            Soil s;

            s.id = fields[0];
            s.latitude = stod(fields[1]);
            s.longitude = stod(fields[2]);
            s.pH = stod(fields[3]);
            s.moisture = stod(fields[4]);
            s.nitrogen = stod(fields[5]);
            s.phosphorus = stod(fields[6]);
            s.potassium = stod(fields[7]);

            soilTree.insert(s);
            count++;
        }
        catch (...) {
            cout << "Skipping invalid soil record.\n";
        }
    }

    file.close();

    cout << count << " soil records loaded successfully.\n";

    return count;
}



int loadDiseaseData(const string& filename, HashMap& cropMap) {

    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error: Could not open " << filename << endl;
        return -1;
    }

    string line;
    int count = 0;

    while (getline(file, line)) {

        stringstream ss(line);
        string field;
        vector<string> fields;

        while (getline(ss, field, ',')) {
            fields.push_back(field);
        }

        if (fields.size() != 4) {
            cout << "Skipping invalid disease record.\n";
            continue;
        }

        try {
            string cropName = fields[0];

            Disease d;
            d.diseaseName = fields[1];
            d.symptoms = fields[2];
            d.advisory = fields[3];

            cropMap.insert(cropName, d);
            count++;
        }
        catch (...) {
            cout << "Skipping invalid disease record.\n";
        }
    }

    file.close();

    cout << count << " disease records loaded successfully.\n";

    return count;
}



int loadYieldData(
    const string& filename,
    vector<Yield>& yieldRecords
) {

    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error: Could not open " << filename << endl;
        return -1;
    }

    string line;
    int count = 0;

    while (getline(file, line)) {

        stringstream ss(line);
        string field;
        vector<string> fields;

        while (getline(ss, field, ',')) {
            fields.push_back(field);
        }

        if (fields.size() != 9) {
            cout << "Skipping invalid yield record.\n";
            continue;
        }

        try {
            Yield y;

            y.id = fields[0];
            y.cropName = fields[1];
            y.year = stoi(fields[2]);
            y.season = fields[3];

            y.latitude = stod(fields[4]);
            y.longitude = stod(fields[5]);

            y.area = stod(fields[6]);
            y.production = stod(fields[7]);
            y.yieldValue = stod(fields[8]);

            if (y.area <= 0 || y.production < 0 ||
                y.yieldValue < 0) {
                cout << "Skipping invalid yield record.\n";
                continue;
            }

            yieldRecords.push_back(y);
            count++;
        }
        catch (...) {
            cout << "Skipping invalid yield record.\n";
        }
    }

    file.close();

    cout << count << " yield records loaded successfully.\n";

    return count;
}



