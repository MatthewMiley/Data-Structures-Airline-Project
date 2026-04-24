#ifndef WEIGHTEDGRAPH_HPP
#define WEIGHTEDGRAPH_HPP


#include "HashMap.hpp"
#include <vector>
#include <string>

//  Class Edge represents the one directional path between two nodes.
//  It contains the destination, the distance, and the cost
class Edge {
    public:
    std::string origin;
    int origin_idx;
    std::string destination;
    int destination_idx;
    int distance;
    int cost;

    Edge(std::string o, int o_idx, std::string d, int d_idx, int l, int c) : origin(o), origin_idx(o_idx), destination(d), destination_idx(d_idx), distance(l), cost(c) {}
};

template <typename T>
class WeightedGraph {
public:

    //  insertVertex will add the origin flights into the 'vertices' vector
    void insertVertex(const T& v);
    //  [update to include weights to the edge] insertEdge will add'v2'(destination) and the given 'distance' and 'cost' into the 'edges' vector
    void insertEdge(const T& v1, const T& v2, int weight, int price);
    //  (remove / alter) no need to simply print. Special prints will likely be handled by each of the search functions
    void print() const;

    //  ================================================
    //  Will not need the simple searches, will be replaced with the specialized searches
    void DFS() const;
    void BFS(int start = 0) const;
    void shortestPath(const T& src, const T& dest) const;
    //  ================================================

    //  [Evan TODO] 5) count and display the direct flight connections for each airport
    void countDirectFlights() const;
    /*
        Sample Output:
        Airport Connections
        ATL     12
        ORD     11
        MIA     11
    */

    bool isConnected() const;


private:
    //  The main vector 'vertices' that contains the list of every unique airport
    std::vector<T> vertices; 
    //  Vector edges which contains 
    std::vector<std::vector<Edge>> edges; 

    //  Given a input vertex, it will return the index. Returns -1 if not found
    int getVertexIndex(const T& vs) const;

    bool hasEdge(int i1, int i2) const;
    void DFS(int i, std::vector<bool>& visited) const;
};

#include "WeightedGraph.tpp"

#endif
