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

    void insertVertex(const T& v);
    void insertEdge(const T& v1, const T& v2);
    void print() const;

    void DFS() const;
    void BFS(int start = 0) const;
    int shortestPath(const T& src, const T& dest) const;
    bool isConnected() const;


private:
    std::vector<T> vertices; 
    std::vector<std::vector<int>> edges; 

    
    int getVertexIndex(const T& vs) const;

    bool hasEdge(int i1, int i2) const;
    void DFS(int i, std::vector<bool>& visited) const;
};

#include "WeightedGraph.tpp"

#endif
