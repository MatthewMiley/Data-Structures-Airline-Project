#ifndef WEIGHTEDGRAPH_HPP
#define WEIGHTEDGRAPH_HPP
#include <vector>
#include <string>

//  Class Edge represents the one directional path between two nodes.
//  It contains the destination, the distance, and the cost
class Edge {
    public:
    std::string destination
    int distance;
    int cost;

    Edge(int d, int c, std::string e) : distance(d), cost(c), destination(e) {}
};

template <typename T>
class WeightedGraph {
public:

    //  insertVertex will add the origin flights into the 'vertices' vector
    void insertVertex(const T& v);
    //  [update to include weights to the edge] insertEdge will add'v2'(destination) and the given 'distance' and 'cost' into the 'edges' vector
    void insertEdge(const T& v1, const T& v2);
    //  (remove / alter) no need to simply print. Special prints will likely be handled by each of the search functions
    void print() const;

    //  ================================================
    //  Will not need the simple searches, will be replaced with the specialized searches
    void DFS() const;
    void BFS(int start = 0) const;
    int shortestPath(const T& src, const T& dest) const;
    //  ================================================

    bool isConnected() const;


private:
    //  The main vector 'vertices' that contains the list of every origin airport
    std::vector<T> vertices; 
    std::vector<std::vector<int>> edges; 

    //  Given a input vertex, it will return the index. Returns -1 if not found
    int getVertexIndex(const T& vs) const;

    bool hasEdge(int i1, int i2) const;
    void DFS(int i, std::vector<bool>& visited) const;
};

#include "WeightedGraph.tpp"

#endif
