//
// Created by tiago on 27/05/2023.
//

#ifndef PROJETO_DA_2_CALCULATIONS_H
#define PROJETO_DA_2_CALCULATIONS_H

#include <cmath>
#include "Graph.h"
#include "NodeEdge.h"

using namespace std;

/**
 * Converts the value passed as parameter from degrees to radians.
 * @param value Represents the value to be converted to radians
 * @return Value converted to radians
 * @note Time-complexity -> O(1)
 */
double convertToRadians(double value);
/**
 * Calculates the distance between two locations using the haversine formula.
 * @param lon1 Represents the longitude of the first location
 * @param lat1 Represents the latitude of the first location
 * @param lon2 Represents the longitude of the second location
 * @param lat2 Represents the latitude of the second location
 * @return Distance between the 2 locations
 * @note Time-complexity -> O(1)
 */
double haversineDistance(double lon1, double lat1, double lon2, double lat2);
/**
 * Calculates the mean distance of a vector of nodes
 * @param cluster
 * @return
 * @note Time-complexity -> O(n) with n being the size of the cluster vector
 */
double calculateMean(const vector<Node*>& cluster);
/**
 * Calculates the standard deviation of a vector of nodes.
 * @param cluster
 * @return
 * @note Time-complexity -> O(n) with n being the size of the cluster vector
 */
double calculateStandardDeviation(const vector<Node*>& cluster);



#endif //PROJETO_DA_2_CALCULATIONS_H

