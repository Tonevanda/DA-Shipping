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
bool Graph::addNode(const int &id, double longitude, double latitude) {
    if (findNode(id) != nullptr)
        return false;
    NodeSet.push_back(new Node(id, longitude, latitude));
    return true;
}

void Graph::sortNodes(){
    std::sort(NodeSet.begin(),NodeSet.end(),[](Node* a, Node* b){
        return a->getId() < b->getId();
    });
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

bool Graph::zeroHasNoEdgesLeft(){
    for(Edge* edge : NodeSet[0]->getAdj()){
        if(!edge->getDest()->isVisited()) return false;
    }
    return true;
}

double Graph::tspBTRec(std::vector<Node *>& path, double min, double curCost, unsigned int i, unsigned int curPathSize, bool ended){
    if(zeroHasNoEdgesLeft()) return min;
    if(!NodeSet[i]->isVisited()){
        if(curPathSize == NodeSet.size()-1){
            double sum = tspBTRec(path,min,curCost+NodeSet[i]->getAdj()[0]->getWeight(),0,curPathSize,true);
            if(sum < min && NodeSet[i]->getAdj()[0]->getDest()->getId()==0){
                min = sum;
                path[curPathSize] = NodeSet[i];
            }
            return min;
        }
        NodeSet[i]->setVisited(true);
    }
    else if(ended){
        min = (curCost < min) ? curCost : min;
        return min;
    }
    else return min;

    for(Edge* edge: NodeSet[i]->getAdj()){
        Node* node = edge->getDest();
        if(curCost+edge->getWeight() > min) continue;
        double sum = tspBTRec(path,min,curCost+edge->getWeight(),node->getId(),curPathSize+1,false);
        if (sum < min){
            min = sum;
            path[curPathSize] = NodeSet[i];
        }
    }

    NodeSet[i]->setVisited(false);
    return min;
}

double Graph::tspBT(std::vector<Node *>& path){
    path = std::vector<Node *>(NodeSet.size(), 0);
    for(int i = 0; i < NodeSet.size()-1; i++){
        NodeSet[i]->setVisited(false);
    }
    return tspBTRec(path,INT_MAX,0,0,0,false);
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