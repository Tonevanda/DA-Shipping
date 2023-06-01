// By: Gonçalo Leão

#ifndef DA_TP_CLASSES_node_EDGE
#define DA_TP_CLASSES_node_EDGE

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

class Edge;

#define INF std::numeric_limits<double>::max()

/************************* node  **************************/

class Node {
public:
    /**
     * Default constructor of the Node class.
     * @param id Represents the ID of the node to be created
     * @param longitude Represents the longitude of the node to be created
     * @param latitude Represents the latitude of the node to be created
     * @note Time-complexity -> O(1)
     */
    Node(int id, double longitude, double latitude);
    /**
     * Operator< overrider. Used to compare nodes by distance.
     * @param node Represents the node to be compared
     * @return True if the distance of (this) is lower than the distance of the node given as parameter, false otherwise.
     * @note Time-complexity -> O(1)
     */
    bool operator<(Node & node) const; // // required by MutablePriorityQueue
    /**
     * Returns the node's (this) ID.
     * @return Node's ID
     * @note Time-complexity -> O(1)
     */
    [[nodiscard]] int getId() const;
    /**
     * Returns the node's (this) outgoing edges.
     * @return vector&lt Edge*> with the node's outgoing edges
     * @note Time-complexity -> O(1)
     */
    [[nodiscard]] std::vector<Edge *> getAdj() const;
    /**
     * Checks if the node (this) was already visited.
     * @return True if it was already visited, false otherwise
     * @note Time-complexity -> O(1)
     */
    [[nodiscard]] bool isVisited() const;
    /**
     * Checks if the node (this) is processing.
     * @return True if it is processing, false otherwise
     * @note Time-complexity -> O(1)
     */
    [[nodiscard]] bool isProcessing() const;
    /**
     * Returns the node's (this) indegree.
     * @return The node's indegree
     * @note Time-complexity -> O(1)
     */
    [[nodiscard]] unsigned int getIndegree() const;
    /**
     * Returns the node's (this) distance.
     * @return The node's distance
     * @note Time-complexity -> O(1)
     */
    [[nodiscard]] double getDist() const;
    /**
     * Returns the node's (this) path.
     * @return the node's path
     * @note Time-complexity -> O(1)
     */
    [[nodiscard]] Edge* getPath() const;
    /**
     * Returns the node's (this) incoming edges.
     * @return vector&lt Edge*> with the node's incoming edges
     * @note Time-complexity -> O(1)
     */
    [[nodiscard]] std::vector<Edge *> getIncoming() const;
    /**
     * Returns the node's (this) longitude
     * @return The node's longitude
     * @note Time-complexity -> O(1)
     */
    [[nodiscard]] double getLon() const;
    /**
     * Returns the node's (this) latitude
     * @return The node's latitude
     * @note Time-complexity -> O(1)
     */
    [[nodiscard]] double getLat() const;
    /**
     * Returns the node's (this) cluster id.
     * @return The node's cluster id
     * @note Time-complexity -> O(1)
     */
    [[nodiscard]] int getClusterID() const;
    /**
     * Sets the node's ID
     * @param info Represents the node's new ID
     * @note Time-complexity -> O(1)
     */
    void setId(int info);
    /**
     * Sets the node's visited field with the value given in the parameter.
     * @param visited Represents the node's visited status(true or false)
     * @note Time-complexity -> O(1)
     */
    void setVisited(bool visited);
    /**
     * Sets the node's processing field with the
     * @param processing Represents the node's processing status(true or false)
     * @note Time-complexity -> O(1)
     */
    void setProcessing(bool processing);
    /**
     * Sets the node's indegree field with the value given in the parameter.
     * @param indegree Represents the node's new indegree
     * @note Time-complexity -> O(1)
     */
    void setIndegree(unsigned int indegree);
    /**
     * Sets the node's dist field with the value given in the parameter.
     * @param dist Represents the node's new dist
     * @note Time-complexity -> O(1)
     */
    void setDist(double dist);
    /**
     * Sets the node's path field with the value given in the parameter.
     * @param path Represents the node's new path
     * @note Time-complexity -> O(1)
     */
    void setPath(Edge *path);
    /**
     * Adds edge from (this) node to node* dest given as parameter with weight w.
     * @param dest Represents the destination of the added edge
     * @param w Represents the weight of the added edge
     * @return The added edge*
     * @note Time-complexity -> O(1)
     */
    Edge * addEdge(Node *dest, double w);
    /**
     * Removes the edge from (this) node to the node with destID.
     * @param destID Represents the id of the destination node of the edge to be removed
     * @return True if successful, false if such Edge does not exist
     * @note Time-complexity -> O(n^2)
     */
    bool removeEdge(int destID);
    /**
     * Sets the node's (this) longitude with the value given as parameter.
     * @param lon Represents the node's new longitude
     * @note Time-complexity -> O(1)
     */
    void setLon(double lon);
    /**
     * Sets the node's (this) latitude with the value given as parameter.
     * @param lat Represents the node's new latitude
     * @note Time-complexity -> O(1)
     */
    void setLat(double lat);
    /**
     * Sets the node's (this) cluster ID
     * @param clusterID Represents the ID of the cluster the node belongs to
     * @note Time-complexity -> O(1)
     */
    void setCluster(int clusterID);

    /**
     * Sorts the node's (this) outgoing edges by their weight, in increasing order.
     * @note Time-complexity -> O(n*log(n)) with n being the size of the NodeSet
     */
    void sortEdges();
    /**
     * Sorts the node's (this) outgoing edges by their ID, in increasing order.
     * @note Time-complexity -> O(n*log(n)) with n being the size of the NodeSet
     */
    void sortEdgesByID();

    /**
     * Checks if node (this) is inside the vector passed as parameter.
     * @param vector Represents the vector which we wish to check the presence of the (this) node.
     * @return True if the (this) node is inside the vector, false otherwise.
     * @note Time-complexity -> O(n) with n being the size of the vector
     */
    bool isInsideVector(const std::vector<Node*>& vector) const;
    void deleteAdj();

protected:
    int id;                // identifier
    std::vector<Edge *> adj;  // outgoing edges

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    bool processing = false; // used by isDAG (in addition to the visited attribute)
    unsigned int indegree; // used by topsort
    double dist = std::numeric_limits<double>::max();
    Edge *path = nullptr;
    double latitude = 0;
    double longitude = 0;
    int clusterID;

    std::vector<Edge *> incoming; // incoming edges

    int queueIndex = 0; 		// required by MutablePriorityQueue and UFDS
};

/********************** Edge  ****************************/

class Edge {
public:
    /**
     * Default constructor of Edge class.
     * @param orig Represents the origin node of the edge
     * @param dest Represents the destination node of the edge
     * @param w Represents the weight of the edge
     * @note Time-complexity -> O(1)
     */
    Edge(Node *orig, Node *dest, double w);

    /**
     * Returns the destination node of the (this) edge.
     * @return The destination node of (this) edge
     * @note Time-complexity -> O(1)
     */
    [[nodiscard]] Node * getDest() const;
    /**
     * Returns the weight of the (this) edge.
     * @return The weight of (this) edge
     * @note Time-complexity -> O(1)
     */
    [[nodiscard]] double getWeight() const;
    /**
     * Checks if the (this) edge is selected.
     * @return True if the edge is selected, false otherwise
     * @note Time-complexity -> O(1)
     */
    [[nodiscard]] bool isSelected() const;
    /**
     * Returns the origin node of the (this) edge.
     * @return The origin node of the edge
     * @note Time-complexity -> O(1)
     */
    [[nodiscard]] Node * getOrig() const;
    /**
     * Returns the reverse of the (this) edge.
     * @return The reverse of the edge
     * @note Time-complexity -> O(1)
     */
    [[nodiscard]] Edge *getReverse() const;
    /**
     * Returns the flow of the (this) edge.
     * @return The flow of the edge
     * @note Time-complexity -> O(1)
     */
    [[nodiscard]] double getFlow() const;
    /**
     * Sets the selected field of (this) edge to the value given in the parameter.
     * @param selected The new value of the select field
     * @note Time-complexity -> O(1)
     */
    void setSelected(bool selected);
    /**
     * Sets the reverse field of (this) edge to the value given in the parameter.
     * @param reverse The new value of the reverse field
     * @note Time-complexity -> O(1)
     */
    void setReverse(Edge *reverse);
    /**
     * Sets the flow field of (this) edge to the value given in the parameter.
     * @param flow The new value of the flow field
     * @note Time-complexity -> O(1)
     */
    void setFlow(double flow);
protected:
    Node * dest; // destination node
    double weight; // edge weight, can also be used for capacity

    // auxiliary fields
    bool selected = false;

    // used for bidirectional edges
    Node *orig;
    Edge *reverse = nullptr;

    double flow; // for flow-related problems
};

#endif /* DA_TP_CLASSES_node_EDGE */