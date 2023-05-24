// By: Gonçalo Leão

#ifndef DA_TP_CLASSES_GRAPH
#define DA_TP_CLASSES_GRAPH

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

#include "NodeEdge.h"

class Graph {
public:
    ~Graph();
    /*
    * Auxiliary function to find a Node with a given ID.
    */
    Node *findNode(const int &id) const;
    /*
     *  Adds a Node with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a Node with that content already exists.
     */
    bool addNode(const int &id, double longitude = 0, double latitude=0);

    void sortNodes();

    /*
     * Adds an edge to a graph (this), given the contents of the source and
     * destination nodes and the edge weight (w).
     * Returns true if successful, and false if the source or destination Node does not exist.
     */
    bool addEdge(const int &sourc, const int &dest, double w);
    bool addBidirectionalEdge(const int &sourc, const int &dest, double w);

    bool zeroHasNoEdgesLeft();
    double tspBTRec(std::vector<Node *>& path, double min, double curCost, unsigned int i, unsigned int curPathSize, bool ended);
    double tspBT(std::vector<Node *>& path);
    std::vector<Node*> kruskal();

    int getNumNode() const;
    std::vector<Node *> getNodeSet() const;
protected:
    std::vector<Node *> NodeSet;    // Node set

    double ** distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall

    /*
     * Finds the index of the Node with a given content.
     */
    int findNodeIdx(const int &id) const;
};

void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);

#endif /* DA_TP_CLASSES_GRAPH */
