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

void toyGraph(Graph* graph,const string& file){
    readToyGraph(graph,file);
    bool choosingToyEuristic = true;
    int chooseToyEuristic;
    while (choosingToyEuristic){
        cout << "Choose an algorithm:\n"
                "1: Backtracking and Bounding\n"
                "2: Triangular Approximation Heuristic\n"
                "0: Go Back\n";
        while (!(cin >> chooseToyEuristic)) {
            cout << "Invalid input!\n";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Choose an algorithm:\n"
                    "1: Backtracking and Bounding\n"
                    "2: Triangular Approximation Heuristic\n"
                    "0: Go Back\n";
        }
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        double min = 0;
        switch (chooseToyEuristic) {
            case 0:{
                choosingToyEuristic= false;
                break;
            }
            case 1: {
                std::vector<Node *> path;
                auto start = chrono::steady_clock::now();
                min = graph->tspBT(path);
                printPath(path, min);
                auto end = chrono::steady_clock::now();
                cout << "Finished in: " <<  chrono::duration_cast<chrono::milliseconds > (end - start).count() << " ms\n";
                break;
            }
            case 2: {
                std::vector<Node*> mst;
                auto start = chrono::steady_clock::now();

                min = graph->TriangularApproximationHeuristic(graph->getNodeSet(),mst,"toy","2");
                printPath(mst,min);
                graph->cleanGraph();
                readToyGraph(graph,file);

                auto end = chrono::steady_clock::now();
                cout << "Finished in: " <<  chrono::duration_cast<chrono::milliseconds > (end - start).count() << " ms\n";
                break;
            }
            default:{
                cout << "Invalid input!\n";
                break;
            }
        }
    }
}

void efcGraph(Graph* graph,const string& file){
    readExtraFullyConnectedGraph(graph,file);
    bool choosingAlg = true;
    int chooseAlg;
    while (choosingAlg){
        cout << "Choose an algorithm:\n"
                "1: Backtracking and Bounding\n"
                "2: Triangular Approximation Heuristic\n"
                "0: Go Back\n";
        while (!(cin >> chooseAlg)) {
            cout << "Invalid input!\n";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Choose an algorithm:\n"
                    "1: Backtracking and Bounding\n"
                    "2: Triangular Approximation Heuristic\n"
                    "0: Go Back\n";
        }
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        double min = 0;
        switch (chooseAlg) {
            case 0:{
                choosingAlg= false;
                break;
            }
            case 1: {
                std::vector<Node *> path;
                min = graph->tspBT(path);
                printPath(path, min);
                break;
            }
            case 2: {
                std::vector<Node*> mst;
                min = graph->TriangularApproximationHeuristic(graph->getNodeSet(),mst,"extra","2");
                printPath(mst,min);
                break;
            }
            default:{
                cout << "Invalid input!\n";
                break;
            }
        }
    }
}

void realGraph1(Graph* graph){
    bool choosingAlg = true;
    int chooseAlg;
    while (choosingAlg){
        cout << "Choose an algorithm:\n"
                "1: Backtracking and Bounding\n"
                "2: Triangular Approximation Heuristic\n"
                "3: Our Heuristic\n"
                "0: Go Back\n";
        while (!(cin >> chooseAlg)) {
            cout << "Invalid input!\n";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Choose an algorithm:\n"
                    "1: Backtracking and Bounding\n"
                    "2: Triangular Approximation Heuristic\n"
                    "3: Our Heuristic\n"
                    "0: Go Back\n";
        }
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        double min = 0;
        switch (chooseAlg) {
            case 0:{
                choosingAlg= false;
                break;
            }
            case 1: {
                std::vector<Node *> path;
                min = graph->tspBT(path);
                printPath(path, min);
                break;
            }
            case 2: {
                std::vector<Node*> mst;
                min = graph->TriangularApproximationHeuristic(graph->getNodeSet(),mst,"real","2");
                printPath(mst,min);
                break;
            }
            case 3: {
                std::vector<Node *> path;
                vector<Node*> emptyCluster;
                path = graph->kMeansDivideAndConquer(sqrt(graph->getNumNode()), emptyCluster, min, true);
                printPath(path, min);
                break;
            }
            default:{
                cout << "Invalid input!\n";
                break;
            }
        }
    }
}

void realGraph23(Graph* graph){
    bool choosingAlg = true;
    int chooseAlg;
    while (choosingAlg){
        cout << "Choose an algorithm:\n"
                "1: Backtracking and Bounding\n"
                "2: Triangular Approximation Heuristic\n"
                "0: Go Back\n";
        while (!(cin >> chooseAlg)) {
            cout << "Invalid input!\n";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Choose an algorithm:\n"
                    "1: Backtracking and Bounding\n"
                    "2: Triangular Approximation Heuristic\n"
                    "0: Go Back\n";
        }
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        double min = 0;
        switch (chooseAlg) {
            case 0:{
                choosingAlg= false;
                break;
            }
            case 1: {
                std::vector<Node *> path;
                min = graph->tspBT(path);
                printPath(path, min);
                break;
            }
            case 2: {
                std::vector<Node*> mst;
                min = graph->TriangularApproximationHeuristic(graph->getNodeSet(),mst,"real","2");
                printPath(mst,min);
                break;
            }
            default:{
                cout << "Invalid input!\n";
                break;
            }
        }
    }
}


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
                    string file;
                    switch (chooseToy) {
                        case 0:{
                            choosingToy=false;
                            break;
                        }
                        case 1:{ //shipping
                            file = "../Project2Graphs/Toy-Graphs/shipping.csv";
                            toyGraph(graph,file);
                            graph->cleanGraph();
                            break;
                        }
                        case 2:{ //stadiums
                            file = "../Project2Graphs/Toy-Graphs/stadiums.csv";
                            toyGraph(graph,file);
                            graph->cleanGraph();
                            break;
                        }
                        case 3:{ // tourism
                            file = "../Project2Graphs/Toy-Graphs/tourism.csv";
                            toyGraph(graph,file);
                            graph->cleanGraph();
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
                        efcGraph(graph, extra_fc);
                        graph->cleanGraph();
                    }
                    else{
                        cout << "Invalid input!\n";
                    }
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
                    switch (chooseReal) {
                        case 0:{
                            choosingReal=false;
                            break;
                        }
                        case 1:{
                            readRealWorldNodes(graph,"../Project2Graphs/Real-World-Graphs/graph1/nodes.csv");
                            readRealWorldEdges(graph,"../Project2Graphs/Real-World-Graphs/graph1/edges.csv");
                            realGraph1(graph);
                            graph->cleanGraph();
                            break;
                        }
                        case 2:{
                            readRealWorldNodes(graph,"../Project2Graphs/Real-World-Graphs/graph2/nodes.csv");
                            readRealWorldEdges(graph,"../Project2Graphs/Real-World-Graphs/graph2/edges.csv");
                            realGraph23(graph);
                            graph->cleanGraph();
                            break;
                        }
                        case 3:{
                            readRealWorldNodes(graph,"../Project2Graphs/Real-World-Graphs/graph3/nodes.csv");
                            readRealWorldEdges(graph,"../Project2Graphs/Real-World-Graphs/graph3/edges.csv");
                            realGraph23(graph);
                            graph->cleanGraph();
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
                string path;
                int chooseGraphType;
                bool choosingGraphType= true;
                while(choosingGraphType){
                    cout << "What type of graph did you input?\n"
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
                        case 0:{
                            choosingGraphType=false;
                            break;
                        }
                        case 1:{
                            cout << "Please input your graph's file path:\n";
                            while (!(cin >> path)) {
                                cout << "Invalid input!\n";
                                cin.clear();
                                cin.ignore(INT_MAX, '\n');
                                cout << "Please input your graph's file path:\n";
                            }
                            cin.clear();
                            cin.ignore(INT_MAX, '\n');
                            toyGraph(graph,path);
                            graph->cleanGraph();
                            break;
                        }
                        case 2:{
                            cout << "Please input your graph's file path:\n";
                            while (!(cin >> path)) {
                                cout << "Invalid input!\n";
                                cin.clear();
                                cin.ignore(INT_MAX, '\n');
                                cout << "Please input your graph's file path:\n";
                            }
                            cin.clear();
                            cin.ignore(INT_MAX, '\n');
                            efcGraph(graph, path);
                            graph->cleanGraph();
                            break;
                        }
                        case 3:{
                            string node, edge;
                            cout << "Please input your graph's nodes file path (Note: Our heuristic will not work as intended for graphs without coordinates and not fully connected):\n";
                            while (!(cin >> node)) {
                                cout << "Invalid input!\n";
                                cin.clear();
                                cin.ignore(INT_MAX, '\n');
                                cout << "Please input your graph's nodes file path:\n";
                            }
                            cin.clear();
                            cin.ignore(INT_MAX, '\n');
                            cout << node << endl;
                            readRealWorldNodes(graph,node);
                            cout << "Please input your graph's edge file path:\n";
                            while (!(cin >> edge)) {
                                cout << "Invalid input!\n";
                                cin.clear();
                                cin.ignore(INT_MAX, '\n');
                                cout << "Please input your graph's edge file path:\n";
                            }
                            cin.clear();
                            cin.ignore(INT_MAX, '\n');
                            cout << edge << endl;
                            readRealWorldEdges(graph,edge);
                            realGraph1(graph);
                            graph->cleanGraph();
                            break;
                        }
                        default:{
                            cout << "Invalid input!\n";
                            break;
                        }

                    }
                }
                break;
            } // end of my own
            default:{
                cout << "Invalid input!\n";
                break;
            }
        }
    }
}

int main(){
    Graph graph;

    chooseGraph(&graph);


    return 0;
}
