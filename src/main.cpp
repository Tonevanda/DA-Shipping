//
// Created by João Lourenço on 28/04/2023.
//

#include <iostream>
#include "Graph.h"
#include "parse.h"
#include "print.h"
#include <string>
#include <chrono>

using namespace std;


void toyGraph(Graph* graph,string file){
    readToyGraph(graph,file);
    bool choosingToyEuristic = true;
    int chooseToyEuristic;
    while (choosingToyEuristic){
        cout << "Choose an algorithm:\n"
                "1: Backtracking and bounding\n"
                "2: Triangular Approximation\n"
                "0: Go Back\n";
        while (!(cin >> chooseToyEuristic)) {
            cout << "Invalid input!\n";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Choose an algorithm:\n"
                    "1: Backtracking and bounding\n"
                    "2: Triangular Approximation\n"
                    "0: Go Back\n";
        }
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        double min = 0;
        switch (chooseToyEuristic) {
            case 1: {
                std::vector<Node *> path;
                min = graph->tspBT(path);
                printPath(path, min);
                break;
            }
            case 2: {
                std::vector<Node*> mst;
                min = graph->TriangularApproximationHeuristic(graph->getNodeSet(),mst,"toy","2");
                printPath(mst,min);
                break;
            }
            case 0:
                choosingToyEuristic= false;
                break;
        }
    }
}
/*
 * toy can only do 1 and 2
 *
 */
void chooseGraph(Graph* graph){
    bool canRun = true;
    while(canRun){
        int typeOfFile;
        cout << "Choose a type of file:\n"
                "1: Toy\n"
                "2: Extra Fully Connected\n"
                "3: Real World\n"
                "4: Enter my own\n"
                "0: Quit\n";
        while (!(cin >> typeOfFile)) {
            cout << "Invalid input!\n";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Choose a type of file:\n"
                    "1: Toy\n"
                    "2: Extra Fully Connected\n"
                    "3: Real World\n"
                    "4: Enter my own\n"
                    "0: Quit\n";
        }
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        switch (typeOfFile) {
            case 0:{
                canRun=false;
                break;
            }
            case 1:{  // Toy
                int chooseToy;
                bool choosingToy = true;
                while(choosingToy){
                    cout << "Choose a toy graph:\n"
                            "1: Shipping\n"
                            "2: Stadiums\n"
                            "3: Tourism\n"
                            "0: Go Back\n";
                    while (!(cin >> chooseToy)) {
                        cout << "Invalid input!\n";
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        cout << "Choose a toy graph:\n"
                                "1: Shipping\n"
                                "2: Stadiums\n"
                                "3: Tourism\n"
                                "0: Go Back\n";
                    }
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    switch (chooseToy) {
                        case 0:{
                            choosingToy=false;
                            break;
                        }
                        case 1:{ //shipping
                            toyGraph(graph,"../Project2Graphs/Toy-Graphs/shipping.csv");
                            break;
                        }
                        case 2:{ //stadiums
                            toyGraph(graph,"../Project2Graphs/Toy-Graphs/stadiums.csv");
                            break;
                        }
                        case 3:{ // tourism
                            toyGraph(graph,"../Project2Graphs/Toy-Graphs/tourism.csv");
                            break;
                        }
                        default:{
                            cout << "Invalid input!\n";
                            break;
                        }
                    }
                }
                break;
            } // end of Toy
            case 2:{ // Extra Fully Connected
                int number;
                bool isChoosingExtra = true;
                while(isChoosingExtra){
                    cout << "Please enter one of these numbers: [25,50,75,100,200,300,400,500,600,700,800,900] to choose the EFC graph or 0 to go back\n";
                    while (!(cin >> number)) {
                        cout << "Invalid input!\n";
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        cout << "Please enter one of these numbers: [25,50,75,100,200,300,400,500,600,700,800,900] to choose the EFC graph or 0 to go back\n";
                    }
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    if(number==0){
                        isChoosingExtra=false;
                    } else if(number == 25 || number == 50 || number == 75 || number==100 || number==200|| number==300|| number==400|| number==500|| number==600|| number==700|| number==800|| number==900){
                        string extra_fc = "../Project2Graphs/Extra_Fully_Connected_Graphs/edges_" + to_string(number) + ".csv";
                        readExtraFullyConnectedGraph(graph, extra_fc);
                        isChoosingExtra=false;
                    }
                    else{
                        cout << "Invalid input!\n";
                    }
                    std::vector<Node*> mst;
                    int min=0;
                    min = graph->TriangularApproximationHeuristic(graph->getNodeSet(),mst,"toy","2");
                    printPath(mst,min);
                }
                break;
            } // end of EFC
            case 3:{ // real world
                int chooseReal;
                bool choosingReal = true;
                while(choosingReal){
                    cout << "Choose a real graph:\n"
                            "1: graph1\n"
                            "2: graph2\n"
                            "3: graph3\n"
                            "0: Go Back\n";
                    while (!(cin >> chooseReal)) {
                        cout << "Invalid input!\n";
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        cout << "Choose a real graph:\n"
                                "1: graph1\n"
                                "2: graph2\n"
                                "3: graph3\n"
                                "0: Go Back\n";
                    }
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    int min=0;
                    switch (chooseReal) {
                        case 0:{
                            choosingReal=false;
                            break;
                        }
                        case 1:{ //shipping
                            int ChooseRealHeuristic =0;
                            readRealWorldNodes(graph,"../Project2Graphs/Real-World-Graphs/graph1/nodes.csv");
                            readRealWorldEdges(graph,"../Project2Graphs/Real-World-Graphs/graph1/edges.csv");
                            std::vector<Node*> mst;
                            cout << "Choose an algorithm:\n"
                                    "1: Triangular Approximation\n"
                                    "2: Our Heuristic\n"
                                    "0: Go Back\n";
                            while (!(cin >> ChooseRealHeuristic)) {
                                cout << "Invalid input!\n";
                                cin.clear();
                                cin.ignore(INT_MAX, '\n');
                                cout << "Choose an algorithm:\n"
                                        "1: Triangular Approximation\n"
                                        "2: Our Heuristic\n"
                                        "0: Go Back\n";
                            }
                            cin.clear();
                            cin.ignore(INT_MAX, '\n');
                            switch (ChooseRealHeuristic) {
                                case 1:{
                                    min = graph->TriangularApproximationHeuristic(graph->getNodeSet(),mst,"real","2");
                                    printPath(mst,min);
                                    break;
                                }
                                case 2:{
                                    std::vector<Node *> path;
                                    double min=0;
                                    vector<Node*> emptyCluster;
                                    path = graph->kMeansDivideAndConquer(sqrt(graph->getNumNode()), emptyCluster, min, true);
                                    printPath(path, min);
                                    break;
                                }
                                case 0:{
                                    break;
                                }
                            }

                        }
                        case 2:{ //stadiums
                            readRealWorldNodes(graph,"../Project2Graphs/Real-World-Graphs/graph2/nodes.csv");
                            readRealWorldEdges(graph,"../Project2Graphs/Real-World-Graphs/graph2/edges.csv");
                            std::vector<Node*> mst;
                            min = graph->TriangularApproximationHeuristic(graph->getNodeSet(),mst,"toy","2");
                            printPath(mst,min);
                            break;
                        }
                        case 3:{ // tourism
                            readRealWorldNodes(graph,"../Project2Graphs/Real-World-Graphs/graph3/nodes.csv");
                            readRealWorldEdges(graph,"../Project2Graphs/Real-World-Graphs/graph3/edges.csv");
                            std::vector<Node*> mst;
                            min = graph->TriangularApproximationHeuristic(graph->getNodeSet(),mst,"toy","2");
                            printPath(mst,min);
                            break;
                        }
                        default:{
                            cout << "Invalid input!\n";
                            break;
                        }
                    }
                }
                break;
            } // end of real world
            case 4:{ // my own
                //should ask what type of graph it is first and do actions accordingly
                //ask user if they want to use the toy,bonus or real
                string path;
                cout << "input graph file path:\n";
                while (!(cin >> path)) {
                    cout << "Invalid input!\n";
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    cout << "input graph file path:\n";
                }
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                int chooseGraphType;
                bool choosingGraphType= true;
                while(choosingGraphType){
                    cout << "What type of file do you input?:\n"
                            "1: Toy\n"
                            "2: Extra fully connected\n"
                            "3: Real World\n"
                            "0: Go Back\n";
                    while (!(cin >> chooseGraphType)) {
                        cout << "Invalid input!\n";
                        cin.clear();
                        cin.ignore(INT_MAX, '\n');
                        cout << "What type of file do you wish to input?:\n"
                                "1: Toy\n"
                                "2: Extra fully connected\n"
                                "3: Real World\n"
                                "0: Go Back\n";
                    }
                    cin.clear();
                    cin.ignore(INT_MAX, '\n');
                    double min=0;
                    switch (chooseGraphType) {
                        case 1:{
                            toyGraph(graph,path);
                            break;
                        }
                        case 2:{
                            readExtraFullyConnectedGraph(graph, path);
                            std::vector<Node*> mst;
                            min = graph->TriangularApproximationHeuristic(graph->getNodeSet(),mst,"toy","2");
                            printPath(mst,min);
                            break;
                        }
                        case 3:{
                            readRealWorldNodes(graph,"../Project2Graphs/Real-World-Graphs/graph1/nodes.csv");
                            readRealWorldEdges(graph,"../Project2Graphs/Real-World-Graphs/graph1/edges.csv");
                            std::vector<Node*> mst;
                            min = graph->TriangularApproximationHeuristic(graph->getNodeSet(),mst,"toy","2");
                            printPath(mst,min);
                            break;
                        }
                        case 0:{
                            choosingGraphType=false;
                            break;
                        }
                    }
                }
                break;
            } // end of my own
            default:{
                cout << "Invalid input|\n";
                break;
            }
        }
    }
}

int main(){
    Graph graph;
    auto start = chrono::steady_clock::now();
    //chooseGraph(&graph);
    //chooseGraph(&graph);
    string filePath = "../Project2Graphs/";

    string toy_shipping = "../Project2Graphs/Toy-Graphs/shipping.csv";
    string toy_stadiums = "../Project2Graphs/Toy-Graphs/stadiums.csv";
    string toy_tourism = "../Project2Graphs/Toy-Graphs/tourism.csv";

    string extra_fc = "../Project2Graphs/Extra_Fully_Connected_Graphs/edges_25.csv";

    string real_graph1_nodes = "../Project2Graphs/Real-World-Graphs/graph1/nodes.csv";
    string real_graph1_edges = "../Project2Graphs/Real-World-Graphs/graph1/edges.csv";

    string real_graph2_nodes = "../Project2Graphs/Real-World-Graphs/graph2/nodes.csv";
    string real_graph2_edges = "../Project2Graphs/Real-World-Graphs/graph2/edges.csv";

    string real_graph3_nodes = "../Project2Graphs/Real-World-Graphs/graph3/nodes.csv";
    string real_graph3_edges = "../Project2Graphs/Real-World-Graphs/graph3/edges.csv";

    readToyGraph(&graph,toy_shipping); // min: 86.7 | 0 -> 1 -> 11 -> 10 -> 12 -> 13 -> 3 -> 2 -> 4 -> 6 -> 9 -> 7 -> 8 -> 5
    //readToyGraph(&graph,toy_stadiums); // min: 341 | 0 -> 1 -> 9 -> 6 -> 8 -> 4 -> 7 -> 5 -> 10 -> 2 -> 3
    //readToyGraph(&graph,toy_tourism); // min: 2600 | 0 -> 3 -> 2 -> 1 -> 4

    //readExtraFullyConnectedGraph(&graph, extra_fc); // min: 364937 | 0, 22, 12, 23, 9, 15, 18, 10, 19, 3, 21, 13, 1, 2, 16, 14, 5, 4, 24, 8, 17, 7, 11, 6, 20, 0

    //readx(parse.cpp)->tspBT(ex1)toy graphs/TriangularAproximationEuristic(ex2)todos/kmeansDivideAndConquer(ex3)realWorldGraph1

    //readRealWorldNodes(&graph,real_graph1_nodes);
    //readRealWorldEdges(&graph,real_graph1_edges); // min: 1.12096e+06


    //readRealWorldNodes(&graph,real_graph2_nodes);
    //readRealWorldEdges(&graph,real_graph2_edges); // min: 1.58349e+06 | 5.29505e+06

    //readRealWorldNodes(&graph,real_graph3_nodes);
    //readRealWorldEdges(&graph,real_graph3_edges);


    double min = 0.0;
    std::vector<Node *> path;
    min = graph.tspBT(path);
    printPath(path,min);


    std::vector<Node*> mst;
    double min2 = graph.TriangularApproximationHeuristic(graph.getNodeSet(),mst,"real","2");
    printPath(mst,min2);


    vector<Node*> emptyCluster;
    //path = graph.kMeansDivideAndConquer(sqrt(graph.getNumNode()), emptyCluster, min);
    //printPath(path, min);

    auto end = chrono::steady_clock::now();
    cout << "Finished in: " <<  chrono::duration_cast<chrono::milliseconds > (end - start).count() << " ms";

    return 0;
}
