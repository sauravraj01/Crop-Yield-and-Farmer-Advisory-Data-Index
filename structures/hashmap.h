
#ifndef HASHMAP_H
#define HASHMAP_H

#include "../models/Disease.h"
#include <vector>

class HashMap {

private:

    static const int TABLE_SIZE = 101;

    struct Node {
        string cropName;
        Disease disease;
        Node* next;

        Node(string crop, Disease d) {
            cropName = crop;
            disease = d;
            next = nullptr;
        }
    };

    Node* table[TABLE_SIZE];

    int hashFunction(string cropName);

public:

    HashMap();

    ~HashMap();

    void insert(string cropName, Disease disease);

    vector<Disease> search(string cropName);

    void displayAll();

};

#endif
