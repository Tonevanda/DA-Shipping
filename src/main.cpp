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
    read2CommaNodes(&graph,toy);
    double min;
    std::vector<Node *> path;
    min = graph.tspBT(path);
    for(int i = 0; i < path.size();i++){
        cout << path[i]->getId() << endl;
    }
    cout << "min: " << min << endl;
    return 0;
}