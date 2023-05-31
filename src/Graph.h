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
    /**
     * Default destructor of the Graph class.
     */
    ~Graph();
    /**
     * Loops through the NodeSet to check if a node with the id given as parameter exists.
     * @param id Represents the id of the node
     * @return Node* if it exists in the NodeSet, nullptr otherwise.
     * @note Time-complexity -> O(V) with V being the size of the NodeSet
     */
    [[nodiscard]] Node* findNode(const int &id) const;
    /**
     * Adds a node with id, longitude and latitude passed as parameter to the NodeSet.
     * @param id Represents the id of the node to be added
     * @param longitude Represents the longitude of the node to be added. Default is 0
     * @param latitude Represents the latitude of the node to be added. Default is 0
     * @return True if the node with those values does not exist in the NodeSet, false otherwise.
     * @note Time-complexity -> O(V) with V being the size of the NodeSet
     */
    bool addNode(const int &id, double longitude = 0, double latitude=0);
    /**
     * Returns the number of nodes in the (this) graph.
     * @return The size of the NodeSet
     */
    [[nodiscard]] int getNumNode() const;
    /**
     * Returns the vector NodeSet of the (this) graph.
     * @return vector with the nodes belonging to the (this) graph
     */
    [[nodiscard]] vector<Node *> getNodeSet() const;
    /**
     * Sorts the nodes of the (this) graph from lowest to highest
     * @note Time-complexity -> O(n*log(n))
     */
    void sortNodes();
    /**
     * Sorts the edges of the (this) graph from lowest to highest
     * @note Time-complexity -> O(n*log(n))
     */
    void sortEdges();
    /**
     * Adds an edge to the (this) graph, with origin, destination and weight passed as parameters.
     * @param sourc Represents the origin of the edge
     * @param dest Represents the destination of the edge
     * @param w Represents the weight of the edge
     * @return True if an edge with that information doesn't exist in the NodeSet, false otherwise.
     * @note Time-complexity -> O(V) with V being the size of the NodeSet
     *
     */
    bool addEdge(const int &sourc, const int &dest, double w);
    /**
     * Adds a bidirectional edge to the (this) graph, with origin, destination and weight passed as parameters.
     * @param sourc Represents one of the nodes of the edge
     * @param dest Represents one of the nodes of the edge
     * @param w Represents the weight of the edge
     * @return True if an edge with that information doesn't exist in the NodeSet, false otherwise.
     * @note Time-complexity -> O(V) with V being the size of the NodeSet
     */
    bool addBidirectionalEdge(const int &sourc, const int &dest, double w);

    /**
    * Calculates and adds the missing edges to turn a toy graph into a fully connected graph. Bases the calculations on the triangular inequality property, the sum of the lengths of any two sides must be greater than or equal to the length of the remaining side.
    * @note Time-complexity -> O(V^2 * U) where U is the number of nodes not fully connected
    */
    void calculateMissingToyDistances();
    /**
     * Checks if node 0 has any adjacent edge that is yet to be visited.
     * @return False if it finds any unvisited node, true otherwise.
     * @note Time-complexity -> O(E) with E being the number of outgoing edges from node 0
     */
    bool zeroHasNoEdgesLeft();
    double tspBTRec(std::vector<Node *>& path, double min, double curCost, unsigned int i, unsigned int curPathSize, bool ended);
    double tspBT(std::vector<Node *>& path);

    void preOrder(Node* node,std::vector<Node*>& mst, bool firstIt, double& weight);
    double TriangularApproximationHeuristic(vector<Node*> nodeSet, std::vector<Node*>& mst,const std::string& type, const std::string& ex);
    double kruskal();
    void dfsKruskalPath(Node *v);

    double kruskalEx3(vector<Node*>& nodeSet);

    static vector<Node*> joinSolvedTSP(std::vector<Node*> solved, std::vector<Node*> add);
    static void makeClusters(const std::vector<Node*>&centroids, vector<Node*>& cluster);
    static vector<Node*> getCentroidCluster(Node* centroid, vector<Node*> const& cluster);
    static bool haveSimilarDistance(const vector<Node*>& cluster);


    vector<Node*> kMeansDivideAndConquer(int k, std::vector<Node*> clusters, double& totalMin);
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
