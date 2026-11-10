
#ifndef SOILKDTREE_H
#define SOILKDTREE_H

#include "../models/Soil.h"
#include <vector>

class SoilKDTree {

private:

    struct Node {
        Soil data;
        Node* left;
        Node* right;

        Node(Soil s) {
            data = s;
            left = nullptr;
            right = nullptr;
        }
    };

    Node* root;

    Node* insertRecursive(Node* node, Soil s, int depth);

    void nearestRecursive(
        Node* node,
        double lat,
        double lon,
        int depth,
        Soil& best,
        double& bestDist,
        bool& found,
        int& visited
    );

    void rangeRecursive(
        Node* node,
        double minLat,
        double maxLat,
        double minLon,
        double maxLon,
        int depth,
        vector<Soil>& result,
        int& visited
    );

    void deleteTree(Node* node);

public:

    SoilKDTree();

    ~SoilKDTree();

    void insert(Soil s);

    bool nearestNeighbor(
        double lat,
        double lon,
        Soil& result,
        int& visited
    );

    vector<Soil> rangeSearch(
        double minLat,
        double maxLat,
        double minLon,
        double maxLon,
        int& visited
    );
};

#endif
