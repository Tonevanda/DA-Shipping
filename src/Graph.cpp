// By: Gonçalo Leão

#include "Graph.h"
#include "UFDS.h"
#include "calculations.h"
#include "parse.h"

using namespace std;

void Graph::calculateMissingToyDistances(){
    vector<Node*> unconnectedNodes = this->getNodeSet();
    int isEverythingConnected = 0;
    int i = 0;
    while(isEverythingConnected != unconnectedNodes.size()){
        Node* curNode = unconnectedNodes[i];

        if(curNode->getAdj().size()==this->getNumNode()-1 && !curNode->isVisited()){
            isEverythingConnected++;
            if(isEverythingConnected == unconnectedNodes.size()) return;
            curNode->setVisited(true);
            continue;
        }

        for(auto adj : unconnectedNodes[i]->getAdj()){
            Node* nextNode = adj->getDest();

            for(auto nextAdj : nextNode->getAdj()){
                Node* finalNode = nextAdj->getDest();

                if(curNode == finalNode) continue;

                if(!isAlreadyInEdges(finalNode->getId(), unconnectedNodes[i]->getAdj())){
                    double weight = adj->getWeight() + nextAdj->getWeight();
                    //cout << "Adding edge from " << curNode->getId() << " to " << finalNode->getId() << " with weight: " << weight << endl;
                    this->addBidirectionalEdge(curNode->getId(),finalNode->getId(), weight);
                }
            }
        }

        if(i==unconnectedNodes.size()-1) i = 0; // se chegar ao i = 13 volta ao inicio
        else i++;

    }
}

int Graph::getNumNode() const {
    return NodeSet.size();
}

std::vector<Node *> Graph::getNodeSet() const {
    return NodeSet;
}


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

void Graph::sortEdges(){
    for(Node* node : NodeSet){
        node->sortEdges();
    }
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
        if(curCost+edge->getWeight() >= min) break;
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

void Graph::preOrder(Node* node,std::vector<Node*>& mst, bool firstIt, double& weight){
    if(node== nullptr)return;
    if(firstIt) mst.push_back(node);

    for (Edge* edge : node->getAdj()) {
        Node* nextNode = edge->getDest();

        if(nextNode->getPath() != nullptr){
            if(nextNode->getPath()->getOrig()->getId() == node->getId()){
                Node* last = mst.back();
                mst.push_back(nextNode);
                for(auto adj : last->getAdj()){
                    if(nextNode->getId() == adj->getDest()->getId()){
                        weight+=adj->getWeight();
                    }
                }
                preOrder(nextNode, mst, false, weight);
            }
        }

    }

}

double Graph::TriangularApproximationHeuristic(vector<Node*> nodeSet,std::vector<Node*>& L, const string& type, const string& ex){
    if(nodeSet.size()==1&&type=="real"){
        L.push_back(nodeSet[0]);
        return 0;
    } else if(nodeSet.size()==2 && type=="real"){
        L.push_back(nodeSet[0]);
        L.push_back(nodeSet[1]);
        L.push_back(nodeSet[0]);
        return 2*haversineDistance(nodeSet[0]->getLon(),nodeSet[0]->getLat(),nodeSet[1]->getLon(),nodeSet[1]->getLat());
    } else if(nodeSet.size()==3 && type=="real"){
        L.push_back(nodeSet[0]);
        L.push_back(nodeSet[1]);
        L.push_back(nodeSet[2]);
        L.push_back(nodeSet[0]);
        return haversineDistance(nodeSet[0]->getLon(),nodeSet[0]->getLat(),nodeSet[1]->getLon(),nodeSet[1]->getLat()) + haversineDistance(nodeSet[0]->getLon(),nodeSet[0]->getLat(),nodeSet[2]->getLon(),nodeSet[2]->getLat()) + haversineDistance(nodeSet[2]->getLon(),nodeSet[2]->getLat(),nodeSet[1]->getLon(),nodeSet[1]->getLat()) + haversineDistance(nodeSet[0]->getLon(),nodeSet[0]->getLat(),nodeSet[2]->getLon(),nodeSet[2]->getLat());
    }

    for(Node* node : NodeSet){
        node->setPath(nullptr);
        node->setVisited(false);
    }

    if(type == "toy" && ex=="2"){
        calculateMissingToyDistances();
        for(Node* node : NodeSet){
            node->setVisited(false);
        }
    }

    double weight = 0;

    if (ex=="2") kruskal();
    else{
        kruskalEx3(nodeSet);
    }

    if(ex=="2")preOrder(NodeSet[0],L,true, weight);
    else if(ex=="3"){
        preOrder(nodeSet[0],L,true, weight);
    }

    Node* last = L.back();
    Node* zero = L.front();
    if(type!="real"){
        for(auto e : last->getAdj()){
            if(e->getDest()==zero){
                weight+=e->getWeight();
                cout << "added " << e->getWeight() << endl;
            }
        }
    }
    else weight+=haversineDistance(last->getLon(),last->getLat(),zero->getLon(),zero->getLat());
    if(ex != "3") L.push_back(zero);

    return weight;
}

void Graph::dfsKruskalPath(Node *v) {
    v->setVisited(true);
    for (auto e : v->getAdj()) {
        if (e->isSelected() && !e->getDest()->isVisited()) {
            e->getDest()->setPath(e);
            dfsKruskalPath(e->getDest());
        }
    }
}

double Graph::kruskal() {
    UFDS ufds(NodeSet.size());
    std::vector<Edge*> sortedEdges;

    for (auto v: NodeSet) {
        for (auto e: v->getAdj()) {
            e->setSelected(false);
            if (e->getOrig()->getId() < e->getDest()->getId()) {
                sortedEdges.push_back(e);
            }
        }
    }

    std::sort(sortedEdges.begin(), sortedEdges.end(), [](const Edge* e1, const Edge* e2) {
        return e1->getWeight() < e2->getWeight();
    });

    unsigned selectedEdges = 0;
    double totalWeight = 0.0;
    for (Edge* e: sortedEdges) {
        Node* orig = e->getOrig();
        Node* dest = e->getDest();

        if (!ufds.isSameSet(orig->getId(), dest->getId())) {

            ufds.linkSets(orig->getId(), dest->getId());

            e->setSelected(true);
            e->getReverse()->setSelected(true);
            totalWeight += e->getWeight();

            if (++selectedEdges == NodeSet.size() - 1) {
                break;
            }
        }
    }

    for (auto v: NodeSet) {
        v->setVisited(false);
    }
    NodeSet[0]->setPath(nullptr);

    dfsKruskalPath(NodeSet[0]);

    return totalWeight;
}

double Graph::kruskalEx3(vector<Node*>& nodeSet){
    UFDS ufds(NodeSet.size());
    std::vector<Edge*> sortedEdges;

    for (auto v: nodeSet) {
        for (auto e: v->getAdj()) {
            e->setSelected(false);
            if (e->getOrig()->getId() < e->getDest()->getId() && e->getDest()->isInsideVector(nodeSet)) {
                sortedEdges.push_back(e);
            }
        }
    }

    std::sort(sortedEdges.begin(), sortedEdges.end(), [](const Edge* e1, const Edge* e2) {
        return e1->getWeight() < e2->getWeight();
    });

    unsigned selectedEdges = 0;
    double totalWeight = 0.0;
    for (Edge* e: sortedEdges) {
        Node* orig = e->getOrig();
        Node* dest = e->getDest();

        int origId = orig->getId();
        int destId = dest->getId();

        if (!ufds.isSameSet(origId, destId)) {

            ufds.linkSets(orig->getId(), dest->getId());

            e->setSelected(true);
            e->getReverse()->setSelected(true);
            totalWeight += e->getWeight();

            if (++selectedEdges == nodeSet.size() - 1) {
                break;
            }
        }
    }

    for (auto v: nodeSet) {
        v->setVisited(false);
    }
    nodeSet[0]->setPath(nullptr);

    dfsKruskalPath(nodeSet[0]);

    return totalWeight;
}

double getEdgeWeight(Node* first, Node* second){
    for(Edge* edge : first->getAdj()){
        if(edge->getDest()==second){
            return edge->getWeight();
        }
    }
    return INF;
}

//só funciona para o real world graph 1 por causa daquele loop que calcula a distância
vector<Node*> Graph::joinSolvedTSP(vector<Node*> solved, vector<Node*> add, double& weight){
    if(solved.empty()) return add;
    if(add.empty()) return solved;

    //cout << "Solved front: " << solved.front()->getId() << " solved back: " << solved.back()->getId() << endl;
    //cout << "Add front: " << add.front()->getId() << " add back: " << add.back()->getId() << endl;

    if(solved.size()!=1 && (solved.front()->getId()==solved.back()->getId()))solved.pop_back();
    if(add.size()!=1 && (add.front()->getId()==add.back()->getId()))add.pop_back();


    double min = std::numeric_limits<double>::max();
    int minNode;
    vector<Node*> joined;
    int i = 0, k = 0, j=0, l = 0;

    double curWeight = 0;
    double dist;
    //maybe there's a better way
    for(Node* first : solved){
        for(Node* second : add){
            dist = getEdgeWeight(first, second);
            //double dist = haversineDistance(first->getLon(), first->getLat(), second->getLon(), second->getLat());
            if(dist < min){
                min = dist;
                k=i;
                minNode = first->getId();
                l = j;
            }
            j++;
        }
        i++;
        j=0;
    }

    i = k;
    j = l;
    int prevI, prevJ = j;
    bool firstIt= true;
    i++; //passo um à frente para nn estar no node que faz a connecção
    while(true){
        i %= solved.size();

        if(!firstIt){
            curWeight+= getEdgeWeight(solved[prevI], solved[i]);
        } else firstIt=false;

        if(solved[i]->getId()==minNode){
            joined.push_back(solved[i]); //node que liga do solved
            joined.push_back(add[j]); //node que liga do add
            curWeight += getEdgeWeight(solved[i],add[j]);
            j++;
            while(true){
                j %= add.size();
                curWeight += getEdgeWeight(add[prevJ],add[j]);
                if(j==l) break;
                joined.push_back(add[j]);
                prevJ=j;
                j++;
            }
            break;
        }
        else{
            joined.push_back(solved[i]);
            prevI = i;
            i++;
        }
    }

    curWeight+= getEdgeWeight(solved.back(), solved.front());
    Node* newFront = solved[0];
    solved.push_back(newFront);


    weight = curWeight;

    return joined;
}

void Graph::makeClusters(const vector<Node*>& centroids, vector<Node*>& cluster){
    for(Node* node : cluster){
        node->setDist(std::numeric_limits<double>::max());  // reset distance
    }
    for(Node* centroid : centroids){
        for(Node* node : cluster){
            double dist = haversineDistance(centroid->getLon(), centroid->getLat(), node->getLon(), node->getLat());
            if(dist < node->getDist()){
                node->setDist(dist);
                node->setCluster(centroid->getClusterID());
            }
        }
    }
}

vector<Node*> Graph::getCentroidCluster(Node* centroid, vector<Node*> const& cluster){
    vector<Node*> result;
    for(auto node : cluster){
        if(node->getClusterID()==centroid->getClusterID()) result.push_back(node);
    }
    return result;
}

bool Graph::haveSimilarDistance(vector<Node*> const& cluster){
    if(cluster.empty()) return false;
    double long se = calculateStandardDeviation(cluster);
    double long mean = calculateMean(cluster) * 0.1;

    return se <= mean;
}

void printPath2(std::vector<Node*> path, double min){
    for(int i = 0; i < path.size();i++) {
        if(i == path.size()-1) cout << path[i]->getId() << endl;
        else cout << path[i]->getId() << " -> ";
    }
    if(path.empty()){
        cout << "Empty vector!\n";
    }
}

//ver exemplo: https://github.com/aditya1601/kmeans-clustering-cpp/blob/master/kmeans.cpp
//este algoritmo é baseado neste: https://reasonabledeviations.com/2019/10/02/k-means-in-cpp/
vector<Node*> Graph::kMeansDivideAndConquer(int k, vector<Node*> clusters, double& totalMin){
    if(k <= 0) return clusters;

    if(!clusters.empty() && ((clusters.size()<=3 || haveSimilarDistance(clusters) || k <= 1))){
        vector<Node*> result;
        TriangularApproximationHeuristic(clusters, result,"real", "3");
        //clusters.clear();
        return result;
    }

    if(clusters.empty()) clusters=NodeSet;

    //Declaro aqui os centroids e escolho k pontos aleatorios
    vector<Node*> centroids;
    srand(time(0));  // need to set the random seed
    for (int i = 0; i < k; i++) {
        Node* random;
        if(clusters.empty()) random = NodeSet[rand() % NodeSet.size()];
        else random = clusters[rand() % clusters.size()];
        Node* centroid = new Node(i, random->getLon(), random->getLat());
        centroid->setCluster(i);
        centroid->setIndegree(random->getId());
        centroids.push_back(centroid);
    }
    makeClusters(centroids,clusters);


    vector<int> nNodes;
    vector<double> sumLon, sumLat;
    bool doing = true;


    //este loop seria até deixar de encontrar mudanças. No site onde estava a ver nn falam disto, mas no exemplo e no chat gpt fazem uma cena q eu presumo q seja basicamente isto
    while(doing){
        makeClusters(centroids,clusters);
        nNodes.clear();
        sumLat.clear();
        sumLon.clear();
        // Initialise with zeroes
        for (int j = 0; j < k; ++j) {
            nNodes.push_back(0);
            sumLon.push_back(0.0);
            sumLat.push_back(0.0);
        }

        // Iterate over points to append data to centroids
        for (Node* node : clusters) {
            int clusterId = node->getClusterID();
            nNodes[clusterId] += 1;
            sumLon[clusterId] += node->getLon();
            sumLat[clusterId] += node->getLat();
        }

        // Compute the new centroids
        doing = false;
        for(Node* c : centroids){
            int clusterId = c->getClusterID();

            double oldLon = c->getLon();
            double oldLat = c->getLat();

            if(nNodes[clusterId]==0){
                Node* random;
                if(clusters.empty())random = NodeSet[rand() % NodeSet.size()];
                else random = clusters[rand() % clusters.size()];
                c->setLon(random->getLon());
                c->setLat(random->getLat());
            } else{
                c->setLon(sumLon[clusterId]/nNodes[clusterId]);
                c->setLat(sumLat[clusterId]/nNodes[clusterId]);
            }


            //cout << "Updating centroids -> " << clusterId << " (started at " << c->getIndegree() << ") | it: " << it << " | oldLon: " << oldLon << " newLon: " << c->getLon() << " | oldLat: " << oldLat << " newLat: " << c->getLat() << endl;
            if(oldLat!=c->getLat() || oldLon!=c->getLon())doing=true;

        }
    }


    vector<Node*> solved, centroidCluster, recursion;
    //double curWeight;
    for(Node* c : centroids){
        //curWeight=0;
        int clusterId = c->getClusterID();
        centroidCluster = getCentroidCluster(c, clusters);
        recursion = kMeansDivideAndConquer(sqrt(centroidCluster.size()),centroidCluster, totalMin);
        for(Node* node : centroidCluster){
            node->setCluster(clusterId);
        }
        //cout << "Joining two TSP | Solved size: " << solved.size() << " recursion sized: " << recursion.size() << endl;
        solved = joinSolvedTSP(solved,recursion,totalMin);
        //printPath2(solved, 1);
        //cout << "Joined two TSP | Solved size: " << solved.size() << endl;
    }
    for(auto c : centroids){
        delete c;
    }
    centroids.clear();
    return solved;
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