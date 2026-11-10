#include "SoilKDTree.h"
#include <cmath>

SoilKDTree::SoilKDTree() {
    root = nullptr;
}


SoilKDTree::Node* SoilKDTree::insertRecursive(
    Node* node, Soil s, int depth
) {

    if (node == nullptr) {
        return new Node(s);
    }

    int axis = depth % 2;

    if (axis == 0) {

        if (s.latitude < node->data.latitude) {
            node->left = insertRecursive(node->left, s, depth + 1);
        }
        else {
            node->right = insertRecursive(node->right, s, depth + 1);
        }

    }
    else {

        if (s.longitude < node->data.longitude) {
            node->left = insertRecursive(node->left, s, depth + 1);
        }
        else {
            node->right = insertRecursive(node->right, s, depth + 1);
        }

    }

    return node;
}

void SoilKDTree::insert(Soil s) {
    root = insertRecursive(root, s, 0);
}

void SoilKDTree::nearestRecursive(
    Node* node,
    double lat,
    double lon,
    int depth,
    Soil& best,
    double& bestDist,
    bool& found,
    int& visited
) {

    if (node == nullptr) {
        return;
    }

    visited++;

    double dLat = lat - node->data.latitude;
    double dLon = lon - node->data.longitude;

    double dist = dLat * dLat + dLon * dLon;

    if (!found || dist < bestDist) {
        bestDist = dist;
        best = node->data;
        found = true;
    }

    int axis = depth % 2;

    double diff;

    if (axis == 0) {
        diff = lat - node->data.latitude;
    }
    else {
        diff = lon - node->data.longitude;
    }

    Node* nearSide;
    Node* farSide;

    if (diff < 0) {
        nearSide = node->left;
        farSide = node->right;
    }
    else {
        nearSide = node->right;
        farSide = node->left;
    }

    nearestRecursive(
        nearSide, lat, lon, depth + 1,
        best, bestDist, found, visited
    );

    if (diff * diff <= bestDist) {

        nearestRecursive(
            farSide, lat, lon, depth + 1,
            best, bestDist, found, visited
        );

    }
}

bool SoilKDTree::nearestNeighbor(
    double lat,
    double lon,
    Soil& result,
    int& visited
) {

    Soil best;
    double bestDist = 0;
    bool found = false;

    visited = 0;

    nearestRecursive(
        root, lat, lon, 0,
        best, bestDist, found, visited
    );

    if (found) {
        result = best;
    }

    return found;
}


void SoilKDTree::rangeRecursive(
    Node* node,
    double minLat,
    double maxLat,
    double minLon,
    double maxLon,
    int depth,
    vector<Soil>& result,
    int& visited
) {

    if (node == nullptr) {
        return;
    }

    visited++;

    double lat = node->data.latitude;
    double lon = node->data.longitude;

    if (lat >= minLat && lat <= maxLat &&
        lon >= minLon && lon <= maxLon) {

        result.push_back(node->data);
    }

    int axis = depth % 2;

    if (axis == 0) {

        if (minLat <= lat) {
            rangeRecursive(
                node->left, minLat, maxLat,
                minLon, maxLon, depth + 1,
                result, visited
            );
        }

        if (maxLat >= lat) {
            rangeRecursive(
                node->right, minLat, maxLat,
                minLon, maxLon, depth + 1,
                result, visited
            );
        }

    }
    else {

        if (minLon <= lon) {
            rangeRecursive(
                node->left, minLat, maxLat,
                minLon, maxLon, depth + 1,
                result, visited
            );
        }

        if (maxLon >= lon) {
            rangeRecursive(
                node->right, minLat, maxLat,
                minLon, maxLon, depth + 1,
                result, visited
            );
        }

    }
}



vector<Soil> SoilKDTree::rangeSearch(
    double minLat,
    double maxLat,
    double minLon,
    double maxLon,
    int& visited
) {

    vector<Soil> result;

    visited = 0;

    if (minLat > maxLat || minLon > maxLon) {
        return result;
    }

    rangeRecursive(
        root,
        minLat, maxLat,
        minLon, maxLon,
        0,
        result,
        visited
    );

    return result;
}

void SoilKDTree::deleteTree(Node* node) {

    if (node == nullptr) {
        return;
    }

    deleteTree(node->left);
    deleteTree(node->right);

    delete node;
}

SoilKDTree::~SoilKDTree() {
    deleteTree(root);
}

