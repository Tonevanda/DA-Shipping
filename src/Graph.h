// By: Gonçalo Leão

#ifndef DA_TP_CLASSES_GRAPH
#define DA_TP_CLASSES_GRAPH

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include "calculations.h"
#include <string>


#include "NodeEdge.h"

using namespace std;

class Graph {
public:
    ~Graph();
    /*
    * Auxiliary function to find a Node with a given ID.
    */
    Node* findNode(const int &id) const;
    /*
     *  Adds a Node with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a Node with that content already exists.
     */
    bool addNode(const int &id, double longitude = 0, double latitude=0);

    /**
     * Sorts nodes by their id from lower to bigger
     * @note Time-complexity -> O(nlog(n))
     */
    void sortNodes();

    /*
     * Adds an edge to a graph (this), given the contents of the source and
     * destination nodes and the edge weight (w).
     * Returns true if successful, and false if the source or destination Node does not exist.
     */
    bool addEdge(const int &sourc, const int &dest, double w);
    bool addBidirectionalEdge(const int &sourc, const int &dest, double w);

    /**
    * Calculates and adds the missing edges to turn a toy graph into a fully connected graph. Bases the calculations on the triangular inequality property, the sum of the lengths of any two sides must be greater than or equal to the length of the remaining side.
    * @param graph
    * @note Time-complexity -> O(V^2 * U) where U is the number of nodes not fully connected
    */
    void calculateMissingToyDistances();
    /**
     * Checks if node zero has any adjacent edge that is yet to be visited. Returns false if it finds any unvisited node, true if all are already visited.
     * @return
     * @note Time-complexity -> O(V)
     */
    bool zeroHasNoEdgesLeft();
    double tspBTRec(std::vector<Node *>& path, double min, double curCost, unsigned int i, unsigned int curPathSize, bool ended);
    double tspBT(std::vector<Node *>& path);

    void preOrder(Node* node,std::vector<Node*>& mst, bool firstIt);
    double TriangularApproximationHeuristic(vector<Node*> nodeSet, std::vector<Node*>& mst,std::string type, std::string ex);
    double kruskal();
    void dfsKruskalPath(Node *v);

    double kruskalEx3(vector<Node*>& nodeSet);

    vector<Node*> joinSolvedTSP(std::vector<Node*> solved, std::vector<Node*> add);
    Node* findCentroid(std::vector<Node*> cluster);
    void makeClusters(std::vector<Node*>centroids);
    vector<Node*> getCentroidCluster(Node* centroid);

    int getNumNode() const;
    std::vector<Node *> getNodeSet() const;
    vector<Node*> kMeansDivideAndConquer(int k, std::vector<Node*> clusters);
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
