#include "kdtree.h"
#include <cmath>

KDTree::KDTree() {
    root = nullptr;
}

KDTree::Node* KDTree::insertRecursive(Node* node, Weather w, int depth) {

    if (node == nullptr) {
        return new Node(w);
    }

    int axis = depth % 2;

    if (axis == 0) {

        if (w.latitude < node->data.latitude) {
            node->left = insertRecursive(node->left, w, depth + 1);
        }
        else {
            node->right = insertRecursive(node->right, w, depth + 1);
        }

    }
    else {

        if (w.longitude < node->data.longitude) {
            node->left = insertRecursive(node->left, w, depth + 1);
        }
        else {
            node->right = insertRecursive(node->right, w, depth + 1);
        }

    }

    return node;
}

void KDTree::insert(Weather w) {
    root = insertRecursive(root, w, 0);
}

bool KDTree::nearestNeighbor(
    double lat,
    double lon,
    Weather& result,
    int& visited
) {

    Weather best;
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

void KDTree::rangeRecursive(
    Node* node,
    double minLat,
    double maxLat,
    double minLon,
    double maxLon,
    int depth,
    vector<Weather>& result,
    int& visited
) {

    if (node == nullptr) {
        return;
    }

    visited++;

    double lat = node->data.latitude;
    double lon = node->data.longitude;

    // Check whether current point lies inside the rectangle
    if (lat >= minLat && lat <= maxLat &&
        lon >= minLon && lon <= maxLon) {

        result.push_back(node->data);
    }

    int axis = depth % 2;

    if (axis == 0) {

        // Current node divides space using latitude
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

        // Current node divides space using longitude
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


vector<Weather> KDTree::rangeSearch(
    double minLat,
    double maxLat,
    double minLon,
    double maxLon,
    int& visited
) {

    vector<Weather> result;

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


void KDTree::deleteTree(Node* node) {

    if (node == nullptr) {
        return;
    }

    deleteTree(node->left);
    deleteTree(node->right);

    delete node;
}

KDTree::~KDTree() {
    deleteTree(root);
}

void KDTree::nearestRecursive(
    Node* node,
    double lat,
    double lon,
    int depth,
    Weather& best,
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