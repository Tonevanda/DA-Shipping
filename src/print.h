//
// Created by tiago on 26/05/2023.
//

#ifndef PROJETO_DA_2_PRINT_H
#define PROJETO_DA_2_PRINT_H

#include "Graph.h"
#include "NodeEdge.h"

using namespace std;
/**
 * Iterates through path and prints it. In the end it shows the minimum value.
 * @param path
 * @param min
 * @note Time-complexity -> O(n) with n being the size of the path vector
 */
void printPath(std::vector<Node*> path, double min){
    for(int i = 0; i < path.size();i++) {
        if(i == path.size()-1) cout << path[i]->getId() << endl;
        else cout << path[i]->getId() << ", ";
    }
    cout << "Minimum total distance value: " << min << endl;
}

#endif //PROJETO_DA_2_PRINT_H
