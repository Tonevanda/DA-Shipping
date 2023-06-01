//
// Created by tiago on 27/05/2023.
//

#include "parse.h"
#include "Graph.h"
#include <sstream>

using namespace std;

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
    int numNodes = graph->getNumNode();
    std::vector<Node*> nodeSet = graph->getNodeSet();

    for (int i = 0; i < numNodes; i++) {
        Node* currentNode = nodeSet[i];

        for (int j = 0; j < numNodes; j++) {
            if (i == j) continue;

            Node* destinationNode = nodeSet[j];

            if (!isAlreadyInEdges(destinationNode->getId(), currentNode->getAdj())) {
                cout << "Adding from " << currentNode->getId() << " to " << destinationNode->getId() << endl;
                double distance = haversineDistance(currentNode->getLon(), currentNode->getLat(), destinationNode->getLon(),destinationNode->getLat());
                graph->addBidirectionalEdge(currentNode->getId(), destinationNode->getId(), distance);
            }
        }
    }
}

void fillInBlanksWithOne(Graph* graph) {
    int numNodes = graph->getNumNode();
    std::vector<Node*> nodeSet = graph->getNodeSet();

    for (int i = 0; i < numNodes; i++) {
        Node* currentNode = nodeSet[i];

        for (int j = 0; j < numNodes; j++) {
            if (i == j) continue;

            Node* destinationNode = nodeSet[j];

            if (!isAlreadyInEdges(destinationNode->getId(), currentNode->getAdj())) {
                graph->addBidirectionalEdge(currentNode->getId(), destinationNode->getId(), 1);
            }
        }
    }
}


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
    graph->sortEdges();
    fout.close();
}


void readToyGraph(Graph* graph, string file){
    cout << "reading toy graph\n";
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
    graph->sortEdges();
    fout.close();
}

void readToyGraphWith1Distance(Graph* graph, string file){
    cout << "reading toy graph\n";
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
        graph->addBidirectionalEdge(stoi(origem),stoi(destino), 1);
    }
    fillInBlanksWithOne(graph);
    graph->sortNodes();
    fout.close();
}


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
    graph->sortEdges();
    fout.close();
}

