#ifndef KDTREE_H
#define KDTREE_H

#include "../models/Weather.h"
#include <vector>

class KDTree {

private:

    struct Node {
        Weather data;
        Node* left;
        Node* right;

        Node(Weather w) {
            data = w;
            left = nullptr;
            right = nullptr;
        }
    };

    Node* root;

    Node* insertRecursive(Node* node, Weather w, int depth);

    void nearestRecursive(
        Node* node,
        double lat,
        double lon,
        int depth,
        Weather& best,
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
        std::vector<Weather>& result,
        int& visited
    );

    void deleteTree(Node* node);

public:

    KDTree();

    ~KDTree();

    void insert(Weather w);

    bool nearestNeighbor(
        double lat,
        double lon,
        Weather& result,
        int& visited
    );

    std::vector<Weather> rangeSearch(
        double minLat,
        double maxLat,
        double minLon,
        double maxLon,
        int& visited
    );

};

#endif