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
     * @note Time-complexity -> O(1)
     */
    [[nodiscard]] int getNumNode() const;
    /**
     * Returns the vector NodeSet of the (this) graph.
     * @return vector with the nodes belonging to the (this) graph
     * @note Time-complexity -> O(1)
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
     * Deletes the nodes and edges of the (this) graph.
     * @note Time-complexity -> O(V+E) with V being the size of the NodeSet and E being the number of edges of each node
     */
    void cleanGraph();
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
    /**
     * Implementation of the backtracking algorithm. Calculates the optimal path for the (this) graph and returns the weight of said path.
     * @param path Represents the path taken
     * @param min Represents the minimum cost of the paths travelled so far
     * @param curCost Represents the current cost of the path taken
     * @param i Represents the id of the node
     * @param curPathSize Represents the current path size
     * @param ended Checks if the end of the path has been reached
     * @return The minimum cost of the paths travelled
     * @note Time-complexity -> O((n-1)!*E) with n being the number of nodes in the graph
     */
    double tspBTRec(std::vector<Node *>& path, double min, double curCost, unsigned int i, unsigned int curPathSize, bool ended);
    /**
     * Fills the vector path with the size of the NodeSet and initialises it with 0's, also iterates over the
     * NodeSet and sets every node's visited field as false. Returns the result of the tspBTRec, a.k.a the recursive function
     * that implements the backtracking algorithm.
     * @param path Is initially sent as an empty vector. At the end of the function call, represents the optimal path.
     * @return The weight of the optimal path
     * @note Time-complexity -> O((n-1)!*E) with n being the number of nodes in the graph
     */
    double tspBT(std::vector<Node *>& path);
    /**
     * Creates an MST by visiting the (this) graph in preOrder, starting with the node provided as parameter. Stores the sum of
     * the edges of the MST in the weight variable passed as parameter.
     * @param node Represents the first node to be visited
     * @param mst Represents the nodes belonging to the MST
     * @param firstIt Checks if the function is in its first iteration. True if it is, false otherwise
     * @param weight Represents the sum of the edges of the MST
     * @param ex Represents which exercise this function is being used for
     * @note Time-complexity -> O(E+N) with E being the outgoing edges of the node parameter and N the number of nodes in the graph
     */
    void preOrder(Node* node,std::vector<Node*>& mst, bool firstIt, double& weight, const string& ex);
    /**
     * Implementation of the triangular approximation heuristic. Utilizes the triangular inequality law to approximate a value
     * close to the optimal one, in return for more efficiency.
     * @param nodeSet Represents the NodeSet of the (this) graph
     * @param mst Represents the nodes belonging to the MST
     * @param type Represents the type of graph
     * @param ex Represents which exercise this function is being used for
     * @return The weight of the path taken
     * @note Time-complexity -> O(N*E + E*log(E)), where N is the size of the nodeSet vector and E is the number of edges in the graph.
     */
    double TriangularApproximationHeuristic(vector<Node*> nodeSet, std::vector<Node*>& mst,const std::string& type, const std::string& ex);
    /**
     * Implementation of the kruskal algorithm. Creates an MST and returns the sum of the weight of the selected edges.
     * @return The sum of the weight of the edges of the MST
     * @note Time-complexity -> O(N*E + E*log(E)), where N is the number of nodes and E is the number of edges
     */
    double kruskal();
    /**
     * Depth-first Search used in the implementation of the kruskal algorithm.
     * @param v Represents a node which edges will be used in the DFS
     * @note Time-complexity -> O(E) where E is the number of edges of the v node
     */
    void dfsKruskalPath(Node *v);
    /**
     * Implementation of the kruskal algorithm, specific to the 3rd exercise.
     * @param nodeSet Represents a cluster of nodes
     * @return The sum of the weight of the edges of the MST
     * @note Time-complexity -> O(N*E + E*log(E)), where N is the number of nodes and E is the number of edges
     */
    double kruskalEx3(vector<Node*>& nodeSet);
    /**
     * Returns the weight of the edge between the two nodes passed as parameters.
     * @param first Represents one of the nodes of the edge
     * @param second Represents one of the nodes of the edge
     * @return The weight of the edge if it exists, INF otherwise
     * @note Time-complexity -> O(E) with E being the number of outgoing edges of the first node
     */
    static double getEdgeWeight(Node* first, Node* second);
    /**
     * Calculates the best nodes to link two clusters with solved hamiltonian cycles and merges the two clusters. Stores the
     * weight of the hamiltonian cycle in the variable weight passed as parameter.
     * @param solved Represents one of the clusters to be merged
     * @param add Represents one of the clusters to be merged
     * @param weight Represents the weight of the hamiltonian cycle of the merged clusters
     * @return Merged cluster of the solved and add clusters
     * @note Time-complexity -> O(S * A + S + A) with S being the size of solved vector and A the size of the add vector
     */
    static vector<Node*> joinSolvedTSP(std::vector<Node*> solved, std::vector<Node*> add, double& weight);
    /**
     * Creates clusters with a centroid in the center of each cluster.
     * @param centroids Represents the centroids created randomly
     * @param cluster Represents the cluster in which the clusters will be created
     * @note Time-complexity -> O(C + K * C) with C being the size of the cluster vector and K the size of the centroids vector
     */
    static void makeClusters(const std::vector<Node*>&centroids, vector<Node*>& cluster);
    /**
     * Returns the cluster of a centroid
     * @param centroid Represents the centroid of a cluster
     * @param cluster Represents a cluster of nodes
     * @return vector&lt Node*> with every node pertaining to the cluster of a centroid
     * @note Time-complexity -> O(n) with n being the size of the cluster vector
     */
    static vector<Node*> getCentroidCluster(Node* centroid, vector<Node*> const& cluster);
    /**
     * Checks if the nodes of a cluster have similar distance by analysing the mean and standard deviation of their distances.
     * @param cluster Represents a cluster of nodes
     * @return True if the standard deviation is less or equal than 10% of the mean of the nodes' distances
     * @note Time-complexity -> O(1)
     */
    static bool haveSimilarDistance(const vector<Node*>& cluster);
    bool isFullyConnected(vector<Node*> cluster);
    /**
     * Implementation of the k-means algorithm using a divide and conquer approach.
     * @param k Represents the number of clusters created in each iteration of this algorithm
     * @param clusters Represents the current cluster of nodes
     * @param totalMin Represents the total weight of the path of the clusters variable
     * @param firstIt Checks if the function is in its first iteration. True if it is, false otherwise
     * @return The path solved by the approximation heuristic
     * @note Time-complexity -> O((C + K * C) * log(K)) with C being the size of the clusters vector and K the size of the centroids vector
     */
    vector<Node*> kMeansDivideAndConquer(int k, std::vector<Node*> clusters, double& totalMin, bool firstIt);
protected:
    std::vector<Node *> NodeSet;    // Node set

    double ** distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall

    /**
     * Finds the index of the node with a given content.
     * @param id Represents the id of the node
     * @return The index of the node with the given id
     */
    [[nodiscard]] int findNodeIdx(const int &id) const;
};

void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);

#endif /* DA_TP_CLASSES_GRAPH */
