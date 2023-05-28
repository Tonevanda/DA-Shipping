//
// Created by tiago on 27/05/2023.
//

#ifndef PROJETO_DA_2_CALCULATIONS_H
#define PROJETO_DA_2_CALCULATIONS_H

#include <cmath>
#include "Graph.h"

using namespace std;

/**
 * Converts from degrees to radians.
 * @param coord
 * @return
 * @note Time-complexity -> O(1)
 */
double convertToRadians(double value);
/**
 * Calculates the distance between two points using the haversine formula
 * @param lon1
 * @param lat1
 * @param lon2
 * @param lat2
 * @return
 * @note Time-complexity -> O(1)
 */
double haversineDistance(double lon1, double lat1, double lon2, double lat2);



#endif //PROJETO_DA_2_CALCULATIONS_H

