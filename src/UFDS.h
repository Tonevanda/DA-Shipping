/*
 * UFDS.h
 * A simple implementation of Union-Find Disjoint Set (UFDS), required by Kruskal's algorithm.
 *
 * Created on: 25/01/2022
 *      Author: Gonçalo Leão
 */

#ifndef DA_TP_CLASSES_UFDS
#define DA_TP_CLASSES_UFDS

#include <vector>

class UFDS {
public:
    /**
     * Constructor for the UFDS class. Creates a UFDS object with path and rank with N size.
     * @param N Represents the size of the path and rank field
     */
    UFDS(unsigned int N);
    /**
     * Finds the set which the node i is contained in.
     * @param i Represents a node
     * @return The path of node i
     */
    unsigned long findSet(unsigned int i);
    /**
     * Checks if i and j, passed as parameters, are in the same set.
     * @param i Represents one of the nodes
     * @param j Represents one of the nodes
     * @return True if the nodes are in the same set, false otherwise.
     */
    bool isSameSet(unsigned int i, unsigned int j);
    /**
     * Checks if the node i and j belong to the same set, if they don't then links them together.
     * @param i Represents one of the nodes
     * @param j Represents one of the nodes
     */
    void linkSets(unsigned int i, unsigned int j);
private:
    std::vector<unsigned int> path; // Ancestor of node i (which can be itself). It is used to determine if two nodes are part of the same set.
    std::vector<unsigned int> rank; // Upper bound for the height of a tree whose root is node i.
};


#endif //DA_TP_CLASSES_UFDS
