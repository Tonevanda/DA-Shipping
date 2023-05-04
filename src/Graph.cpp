// By: Gonçalo Leão

#include "Graph.h"

int Graph::getNumNode() const {
    return NodeSet.size();
}

std::vector<Node *> Graph::getNodeSet() const {
    return NodeSet;
}

/*
 * Auxiliary function to find a Node with a given content.
 */
Node * Graph::findNode(const int &id) const {
    for (auto v : NodeSet)
        if (v->getId() == id)
            return v;
    return nullptr;
}

/*
 * Finds the index of the Node with a given content.
 */
int Graph::findNodeIdx(const int &id) const {
    for (unsigned i = 0; i < NodeSet.size(); i++)
        if (NodeSet[i]->getId() == id)
            return i;
    return -1;
}
/*
 *  Adds a Node with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a Node with that content already exists.
 */
bool Graph::addNode(const int &id) {
    if (findNode(id) != nullptr)
        return false;
    NodeSet.push_back(new Node(id));
    return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination Node does not exist.
 */
bool Graph::addEdge(const int &sourc, const int &dest, double w) {
    auto v1 = findNode(sourc);
    auto v2 = findNode(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w);
    return true;
}

bool Graph::addBidirectionalEdge(const int &sourc, const int &dest, double w) {
    auto v1 = findNode(sourc);
    auto v2 = findNode(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, w);
    auto e2 = v2->addEdge(v1, w);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}


unsigned int tspBTRec(const unsigned int **dists, unsigned int n, unsigned int path[], unsigned int min, unsigned int curCost,unsigned int curPath[], unsigned int i, unsigned int curPathSize, unsigned int visited[], bool ended) {

    if(visited[i] == 0){
        visited[i] = 1;
        if(curPathSize == (n-1)){
            visited[i] = 0;
            int sum = tspBTRec(dists,n,path,min,curCost+dists[i][0],curPath,0,curPathSize,visited, true);
            if(sum < min){
                min = sum;
                path[curPathSize] = i;
            }
            return min;
        }
    }
    else if(i==0 && ended){
        min = (curCost < min) ? curCost : min;
        return min;
    }
    else return min;

    unsigned int localCost;

    for(int j = 0; j < n; j++){
        if(i==j) continue;
        localCost=tspBTRec(dists,n,path,min,curCost+dists[i][j],curPath,j,curPathSize+1, visited, false);
        if(localCost < min){
            min = localCost;
            path[curPathSize] = i;
        }
    }
    visited[i] = 0;
    return min;
}

unsigned int tspBT(const unsigned int **dists, unsigned int n, unsigned int path[]) {
    unsigned int visited[n];
    unsigned int curPath[n];
    for(int i = 0; i < n; i++){
        visited[i]=0;
        curPath[i] = 0;
        path[i] = 0;
    }

    return tspBTRec(dists,n,path,INT_MAX,0, curPath, 0, 0, visited, false);
}


void deleteMatrix(int **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

void deleteMatrix(double **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

Graph::~Graph() {
    deleteMatrix(distMatrix, NodeSet.size());
    deleteMatrix(pathMatrix, NodeSet.size());
}