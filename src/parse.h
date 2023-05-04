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
