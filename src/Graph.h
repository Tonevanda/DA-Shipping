// By: Gonçalo Leão

#ifndef DA_TP_CLASSES_GRAPH
#define DA_TP_CLASSES_GRAPH

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include "calculations.h"


#include "NodeEdge.h"

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
    */
    void calculateMissingToyDistances();

    bool zeroHasNoEdgesLeft();
    double tspBTRec(std::vector<Node *>& path, double min, double curCost, unsigned int i, unsigned int curPathSize, bool ended);
    double tspBT(std::vector<Node *>& path);
    void preOrder(Node* node,std::vector<Node*>& mst);
    double TriangularApproximationHeuristic(std::vector<Node*>& mst);
    double kruskal();
    void dfsKruskalPath(Node *v);

    vector<Node*> joinSolvedTSP(vector<Node*> solved, vector<Node*> add);
    Node* findCentroid(vector<Node*> cluster);
    void makeClusters(vector<Node*>centroids);
    vector<Node*> getCentroidCluster(Node* centroid);

    int getNumNode() const;
    std::vector<Node *> getNodeSet() const;
    vector<Node*> kMeansDivideAndConquer(int k, vector<Node*> clusters);
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
