// By: Gonçalo Leão

#include "NodeEdge.h"

/************************* Node  **************************/

Node::Node(int id, double longitude, double latitude): id(id), longitude(longitude), latitude(latitude) {}

/*
 * Auxiliary function to add an outgoing edge to a Node (this),
 * with a given destination Node (d) and edge weight (w).
 */
Edge * Node::addEdge(Node *d, double w) {
    auto newEdge = new Edge(this, d, w);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a Node (this).
 * Returns true if successful, and false if such edge does not exist.
 */
bool Node::removeEdge(int destID) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        Node *dest = edge->getDest();
        if (dest->getId() == destID) {
            it = adj.erase(it);
            // Also remove the corresponding edge from the incoming list
            auto it2 = dest->incoming.begin();
            while (it2 != dest->incoming.end()) {
                if ((*it2)->getOrig()->getId() == id) {
                    it2 = dest->incoming.erase(it2);
                }
                else {
                    it2++;
                }
            }
            delete edge;
            removedEdge = true; // allows for multiple edges to connect the same pair of vertices (multigraph)
        }
        else {
            it++;
        }
    }
    return removedEdge;
}

bool Node::operator<(Node & Node) const {
    return this->dist < Node.dist;
}

int Node::getId() const {
    return this->id;
}

std::vector<Edge*> Node::getAdj() const {
    return this->adj;
}

bool Node::isVisited() const {
    return this->visited;
}

bool Node::isProcessing() const {
    return this->processing;
}

unsigned int Node::getIndegree() const {
    return this->indegree;
}

double Node::getDist() const {
    return this->dist;
}

Edge *Node::getPath() const {
    return this->path;
}

std::vector<Edge *> Node::getIncoming() const {
    return this->incoming;
}

double Node::getLon() const{
    return this->longitude;
}
double Node::getLat() const{
    return this->latitude;
}

void Node::setId(int id) {
    this->id = id;
}

void Node::setVisited(bool visited) {
    this->visited = visited;
}

void Node::setProcesssing(bool processing) {
    this->processing = processing;
}

void Node::setIndegree(unsigned int indegree) {
    this->indegree = indegree;
}

void Node::setDist(double dist) {
    this->dist = dist;
}

void Node::setPath(Edge *path) {
    this->path = path;
}

void Node::setLon(double lon){
    this->longitude=lon;
}
void Node::setLat(double lat){
    this->latitude=lat;
}

void Node::sortEdges(){
    std::sort(adj.begin(),adj.end(),[](Edge* a, Edge* b){
        return a->getWeight() < b->getWeight();
    });
}

void Node::sortEdgesByID(){
    std::sort(adj.begin(),adj.end(),[](Edge* a, Edge* b){
        return a->getOrig()->getId() < b->getOrig()->getId();
    });
}

/********************** Edge  ****************************/

Edge::Edge(Node *orig, Node *dest, double w): orig(orig), dest(dest), weight(w) {}

Node * Edge::getDest() const {
    return this->dest;
}

double Edge::getWeight() const {
    return this->weight;
}

Node * Edge::getOrig() const {
    return this->orig;
}

Edge *Edge::getReverse() const {
    return this->reverse;
}

bool Edge::isSelected() const {
    return this->selected;
}

double Edge::getFlow() const {
    return flow;
}

void Edge::setSelected(bool selected) {
    this->selected = selected;
}

void Edge::setReverse(Edge *reverse) {
    this->reverse = reverse;
}

void Edge::setFlow(double flow) {
    this->flow = flow;
}