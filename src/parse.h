//
// Created by tiago on 11/03/2023.
//
#ifndef PROJETO_DA_1_PARSE
#define PROJETO_DA_1_PARSE

#include "Graph.h"
#include <fstream>
#include <sstream>
#include "calculations.h"

using namespace std;

/**
 * Parses the information read in every line to make sure each field is correctly divided.
 * @param line
 * @return vector with the information of a nodes.
 * @note Time-complexity -> O(n)
 */
vector<string> read(std::string filename);
/**
 * Checks if a node with a given id is already inside the vector of adjacent edges of another node
 * @param id
 * @param adj
 * @return bool on weather it is already inside or not
 * @note Time-complexity -> O(V)
 */
bool isAlreadyInEdges(int id, std::vector<Edge*> edges);
void fillInBlanks(Graph* graph);
void fillInBlanksWithOne(Graph* graph);
/**
 * Opens the file given, parses the nodes from the provided file, assuming it's in the Real World graphs' format and closes the file
 * @param graph
 * @param file
 * @note Time-complexity -> O(n)
 */
void readRealWorldNodes(Graph* graph, std::string filename);
/**
 * Opens the file given, parses the edges from the provided file, assuming it's in the Real World graphs' format and closes the file
 * @param graph
 * @param file
 * @note Time-complexity -> O(n)
 */
void readRealWorldEdges(Graph* graph, std::string filename);
/**
 * Opens the file given, parses the nodes and edges from the provided file, assuming it's in the Toy graphs' format, orders the nodes through their id's and closes the file
 * @param graph
 * @param file
 * @note Time-complexity -> O( n log(n) )
 */
void readToyGraph(Graph* graph, std::string filename);
/**
 * Opens the file given, parses the nodes and edges from the provided file, assuming it's in the Toy graphs' format, but instead of adding it's real distance, sets it as 1 instead, then it fully connects the rest of the nodes with assigned distance of 1, orders the nodes through their id's and closes the file
 * @param graph
 * @param file
 * @note Time-complexity -> O( n log(n) )
 */
void readToyGraphWith1Distance(Graph* graph, string file);
/**
 * Opens the file given, parses the nodes and edges from the provided file, assuming it's in the Extra Fully Connected graphs' format, orders the nodes through their id's and closes the file
 * @param graph
 * @param file
 * @note Time-complexity -> O(n log(n))
 */
void readExtraFullyConnectedGraph(Graph* graph, std::string filename);


#endif //PROJETO_DA_1_PARSE
