//
// Created by tiago on 11/03/2023.
//
#ifndef PROJETO_DA_1_PARSE
#define PROJETO_DA_1_PARSE

#include "Graph.h"
#include <fstream>
#include <sstream>

using namespace std;

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
    for(int i = 0; i < adj.size()-1; i++){
        if(id == adj[i]->getDest()->getId()) return true;
    }
    return false;
}

/**
 * Opens the file, parse the nodes from the provided file and closes the file.
 * @param graph
 * @param file
 * @note Time-complexity -> O(n)
 */
void readNodes(Graph* graph, string file){
    ifstream fout;
    file= "../" +file;
    fout.open(file);
    if(!fout.is_open()){
        cout << "Error when opening file " << file << endl;
        return;
    }


    fout.close();
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
        graph->addBidirectionalEdge(stoi(origem),stoi(destino), stod(distancia));
    }
    graph->sortNodes();
    fout.close();
}
/**
 * Opens the file given, parses the nodes and edges from the provided file, assuming it's in the Extra Fully Connected graphs' format, orders the nodes through their id's and closes the file
 * @param graph
 * @param file
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

/**
 * Opens the network file, parse the Network from the provided file and closes the file.
 * @param graph
 * @param file
 * @note Time-complexity -> O(n)
 */
void readNetwork(Graph* graph, string file){
    ifstream fout;
    file="../"+file;
    fout.open(file);
    if(!fout.is_open()){
        cout << "Error when opening file " << file << endl;
        return;
    }

    fout.close();
}

#endif //PROJETO_DA_1_PARSE
