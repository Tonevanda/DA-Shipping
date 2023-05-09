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

void fillInBlanks(Graph* graph){
    for(int i = 0; i < graph->getNumNode(); i++){
        for(int j = 0; j < graph->getNumNode(); j++){
            if(i==j) graph->addEdge(i,j,0);
            else if (isAlreadyInEdges(j,graph->getNodeSet()[i]->getAdj())) continue;
            else{
                graph->addEdge(i,j,std::numeric_limits<double>::infinity());
            }
        }
        graph->getNodeSet()[i]->sortEdges();
    }
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


void read2CommaNodes(Graph* graph, string file){
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
        graph->addEdge(stoi(origem),stoi(destino), stod(distancia));
    }
    graph->sortNodes();
    fillInBlanks(graph);
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
