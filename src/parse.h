//
// Created by tiago on 11/03/2023.
//
#ifndef PROJETO_DA_1_PARSE
#define PROJETO_DA_1_PARSE

#include "Graph.h"
#include <fstream>
#include <sstream>
#include <cmath>

using namespace std;

/**
 * Converts from degrees to radians.
 * @param coord
 * @return
 * @note Time-complexity -> O(1)
 */
double convertToRadians(double coord){
    return (coord*M_PI)/180;
}
/**
 * Calculates the distance between two points using the haversine formula
 * @param lon1
 * @param lat1
 * @param lon2
 * @param lat2
 * @return
 * @note Time-complexity -> O(1)
 */
double haversineDistance(double lon1, double lat1, double lon2, double lat2){
    double radLon1 = convertToRadians(lon1), radLat1 = convertToRadians(lat1), radLon2 = convertToRadians(lon2), radLat2 = convertToRadians(lat2);

    double deltaLon = radLon2 - radLon1, deltaLat = radLat2 - radLat1;

    double aux = pow(sin(deltaLat/2),2) + cos(radLat1) * cos(radLat2) * pow(sin(deltaLon/2),2);

    double c = 2 * atan2(sqrt(aux), sqrt(1-aux));

    return 6371000 * c;
}

/**
 * Parses the information read in every line to make sure each field is correctly divided.
 * @param line
 * @return vector with the information of a nodes.
 * @note Time-complexity -> O(n)
 */
vector<string> read(const string textLine){
    vector<string> info;
    string word;
    bool inQuotes = false;
    for(char c :textLine){
        if(c == '"'){
            inQuotes = !inQuotes;
        }
        else if(c == ',' && !inQuotes){
            info.push_back(word);
            word.clear();
        }
        else {
            word += c;
        }
    }
    info.push_back(word);
    return info;
}

bool isAlreadyInEdges(int id, std::vector<Edge*> adj){
    if(adj.empty()){
        return false;
    }
    for(int i = 0; i < adj.size(); i++){
        if(id == adj[i]->getDest()->getId()) return true;
    }
    return false;
}

void fillInBlanks(Graph* graph) {
    for (int i = 0; i < graph->getNumNode(); i++) {
        for (int j = i+1; j < graph->getNumNode(); j++) {
            //if (i == j) graph->addEdge(i, j, 0);
            if (isAlreadyInEdges(j, graph->getNodeSet()[i]->getAdj())) continue;
            else {
                Node* node1 = graph->findNode(i);
                Node* node2 = graph->findNode(j);

                double distance = haversineDistance(node1->getLon(), node1->getLat(), node2->getLon(),node2->getLat());
                graph->addBidirectionalEdge(i, j, distance);
            }
        }
        graph->getNodeSet()[i]->sortEdges();
    }
}

void fillInBlanksWithOne(Graph* graph) {
    int numNodes = graph->getNumNode();
    std::vector<Node*> nodeSet = graph->getNodeSet();

    for (int i = 0; i < numNodes; i++) {
        Node* currentNode = nodeSet[i];

        for (int j = 0; j < numNodes; j++) {
            if (i == j) continue;  // Skip self-loop

            Node* destinationNode = nodeSet[j];

            if (!isAlreadyInEdges(destinationNode->getId(), currentNode->getAdj())) {
                graph->addBidirectionalEdge(currentNode->getId(), destinationNode->getId(), 1);
            }
        }
    }
}

/**
 * Opens the file given, parses the nodes from the provided file, assuming it's in the Real World graphs' format and closes the file
 * @param graph
 * @param file
 * @note Time-complexity -> O(n)
 */
void readRealWorldNodes(Graph* graph, string file){
    ifstream fout;
    fout.open(file);
    if(!fout.is_open()) {
        cout << "Error when opening file " << file << endl;
        return;
    }
    string tempstream,id, longitude, latitude;
    getline(fout, tempstream);
    while (getline (fout, tempstream)) {
        vector<string> info = read(tempstream);
        id = info[0];
        longitude = info[1];
        latitude = info[2];
        graph->addNode(stoi(id), stod(longitude), stod(latitude));
    }
    fout.close();
}
/**
 * Opens the file given, parses the edges from the provided file, assuming it's in the Real World graphs' format and closes the file
 * @param graph
 * @param file
 * @note Time-complexity -> O(n)
 */
void readRealWorldEdges(Graph* graph, string file){
    ifstream fout;
    fout.open(file);
    if(!fout.is_open()) {
        cout << "Error when opening file " << file << endl;
        return;
    }
    string tempstream,node1,node2, dist;
    getline(fout, tempstream);
    while (getline (fout, tempstream)) {
        vector<string> info = read(tempstream);
        node1 = info[0];
        node2 = info[1];
        dist = info[2];
        graph->addBidirectionalEdge(stoi(node1), stoi(node2), stod(dist));
    }
    fillInBlanks(graph);
    fout.close();
}

/**
 * Opens the file given, parses the nodes and edges from the provided file, assuming it's in the Toy graphs' format, orders the nodes through their id's and closes the file
 * @param graph
 * @param file
 * @note Time-complexity -> O( n log(n) )
 */
void readToyGraph(Graph* graph, string file){
    ifstream fout;
    fout.open(file);
    if(!fout.is_open()) {
        cout << "Error when opening file " << file << endl;
        return;
    }
    string tempstream,origem, destino, distancia;
    getline(fout, tempstream);
    while (getline (fout, tempstream)) {
        vector<string> info = read(tempstream);
        origem = info[0];
        destino = info[1];
        distancia = info[2];
        graph->addNode(stoi(origem));
        graph->addNode(stoi(destino));
        //graph->addBidirectionalEdge(stoi(origem),stoi(destino), stod(distancia));
        graph->addBidirectionalEdge(stoi(origem),stoi(destino), 1);
    }
    fillInBlanksWithOne(graph);
    graph->sortNodes();
    fout.close();
}
/**
 * Opens the file given, parses the nodes and edges from the provided file, assuming it's in the Extra Fully Connected graphs' format, orders the nodes through their id's and closes the file
 * @param graph
 * @param file
 * @note Time-complexity -> O(n log(n))
 */
void readExtraFullyConnectedGraph(Graph* graph, string file){
    ifstream fout;
    fout.open(file);
    if(!fout.is_open()) {
        cout << "Error when opening file " << file << endl;
        return;
    }
    string tempstream,origem, destino, distancia;
    while (getline (fout, tempstream)) {
        vector<string> info = read(tempstream);
        origem = info[0];
        destino = info[1];
        distancia = info[2];
        graph->addNode(stoi(origem));
        graph->addNode(stoi(destino));
        graph->addBidirectionalEdge(stoi(origem),stoi(destino), stod(distancia));
    }

    graph->sortNodes();
    fout.close();
}

#endif //PROJETO_DA_1_PARSE
