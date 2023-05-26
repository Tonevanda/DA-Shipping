//
// Created by João Lourenço on 28/04/2023.
//

#include <iostream>
#include "Graph.h"
#include "parse.h"
#include "print.h"
#include <string>

using namespace std;

int main(){
    Graph graph;
    string filePath = "../Project2Graphs/";

    string toy_shipping = "../Project2Graphs/Toy-Graphs/shipping.csv";
    string toy_stadiums = "../Project2Graphs/Toy-Graphs/stadiums.csv";
    string toy_tourism = "../Project2Graphs/Toy-Graphs/tourism.csv";

    string extra_fc = "../Project2Graphs/Extra_Fully_Connected_Graphs/edges_25.csv";

    string real_graph1_nodes = "../Project2Graphs/Real-World-Graphs/graph1/nodes.csv";
    string real_graph1_edges = "../Project2Graphs/Real-World-Graphs/graph1/edges.csv";

    //readToyGraph(&graph,toy_shipping); // min: 86.7 | 0 -> 1 -> 11 -> 10 -> 12 -> 13 -> 3 -> 2 -> 4 -> 6 -> 9 -> 7 -> 8 -> 5
    //readToyGraph(&graph,toy_stadiums); // min: 341 | 0 -> 1 -> 9 -> 6 -> 8 -> 4 -> 7 -> 5 -> 10 -> 2 -> 3
    //readToyGraph(&graph,toy_tourism); // min: 2600 | 0 -> 3 -> 2 -> 1 -> 4

    readExtraFullyConnectedGraph(&graph, extra_fc);

    //readRealWorldNodes(&graph,real_graph1_nodes);
    //readRealWorldEdges(&graph,real_graph1_edges);
    /*
    double min;
    std::vector<Node *> path;
    min = graph.tspBT(path);
    printPath(path,min);
    */

    std::vector<Node*> mst;
    double min = graph.TriangularApproximationHeuristic(mst);
    printPath(mst,min);

    return 0;
}
