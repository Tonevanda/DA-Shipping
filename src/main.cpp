//
// Created by João Lourenço on 28/04/2023.
//

#include <iostream>
#include "Graph.h"
#include "parse.h"
#include <string>

using namespace std;

int main(){
    Graph graph;
    string filePath = "../Project2Graphs/";

    string toy = "../Project2Graphs/Toy-Graphs/shipping.csv";
    string extra_fc = "../Project2Graphs/Extra_Fully_Connected_Graphs/edges_25.csv";

    //read2CommaNodes(&graph,toy);
    read2CommaNodesNoHeader(&graph, extra_fc);
    double min;
    std::vector<Node *> path;
    min = graph.tspBT(path);
    for(int i = 0; i < path.size();i++) {
        if(i == path.size()-1) cout << path[i]->getId() << endl;
        else cout << path[i]->getId() << " -> ";
    }
    cout << "min: " << min << endl;
    return 0;
}