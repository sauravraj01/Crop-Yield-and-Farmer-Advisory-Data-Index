
#ifndef ADVISORY_H
#define ADVISORY_H

#include "../models/Farm.h"
#include "../structures/KDTree.h"
#include "../structures/SoilKDTree.h"
#include "../structures/HashMap.h"

class Advisory {

public:

    void generateAdvisory(
        Farm farm,
        KDTree& weatherTree,
        SoilKDTree& soilTree,
        HashMap& cropMap
    );

};

#endif
