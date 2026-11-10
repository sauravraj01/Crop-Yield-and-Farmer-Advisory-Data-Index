#include "HashMap.h"

HashMap::HashMap() {

    for (int i = 0; i < TABLE_SIZE; i++) {
        table[i] = nullptr;
    }

}

int HashMap::hashFunction(string cropName) {

    int sum = 0;

    for (char ch : cropName) {
        sum += ch;
    }

    return sum % TABLE_SIZE;
}

void HashMap::insert(string cropName, Disease disease) {

    int index = hashFunction(cropName);

    Node* newNode = new Node(cropName, disease);

    newNode->next = table[index];

    table[index] = newNode;

}

vector<Disease> HashMap::search(string cropName) {

    vector<Disease> result;

    int index = hashFunction(cropName);

    Node* current = table[index];

    while (current != nullptr) {

        if (current->cropName == cropName) {
            result.push_back(current->disease);
        }

        current = current->next;
    }

    return result;
}

void HashMap::displayAll() {

    for (int i = 0; i < TABLE_SIZE; i++) {

        Node* current = table[i];

        while (current != nullptr) {

            cout << "\nCrop: " << current->cropName;
            cout << "\nDisease: " << current->disease.diseaseName;
            cout << "\nSymptoms: " << current->disease.symptoms;
            cout << "\nAdvisory: " << current->disease.advisory;
            cout << "\n--------------------------\n";

            current = current->next;
        }
    }
}

HashMap::~HashMap() {

    for (int i = 0; i < TABLE_SIZE; i++) {

        Node* current = table[i];

        while (current != nullptr) {

            Node* temp = current;
            current = current->next;

            delete temp;
        }
    }
}

