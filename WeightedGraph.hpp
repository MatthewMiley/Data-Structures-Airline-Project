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
    std::string origin_city;
    std::string destination;
    int destination_idx;
    std::string dest_city;
    int distance;
    int cost;

    Edge(std::string o, int o_idx, std::string oc, std::string d, int d_idx, std::string dc, int dist, int c) : origin(o), origin_idx(o_idx), origin_city(oc), destination(d), destination_idx(d_idx), dest_city(dc), distance(dist), cost(c) {}
};

template <typename T>
class WeightedGraph {
public:

    //  insertVertex will add the origin flights into the 'vertices' vector
    void insertVertex(const T& v);
    //  [update to include weights to the edge] insertEdge will add'v2'(destination) and the given 'distance' and 'cost' into the 'edges' vector
    void insertEdge(const T& v1, const T& v2, int weight, int price, std::string origin_city, std::string dest_city);
    //  (remove / alter) no need to simply print. Special prints will likely be handled by each of the search functions
    void print() const;

    //  ================================================
    //  Will not need the simple searches, will be replaced with the specialized searches
    void DFS() const;
    void BFS(int start = 0) const;
    void shortestPath(const T& src, const T& dest) const;
    //  ================================================

    //  [Matthew Done] 3) shortest path from an origin airport to a state destination
    void shortestPathToState(const T& source, std::string target_state) const;

    //  [Evan Done] 5) count and display the direct flight connections for each airport
    void countDirectFlights() const;

    //  [Evan TODO] 6) Undirected Graph
    void undirectedGraph() const;
    
    //  [Matthew TODO] 7) Minimum spanning tree with Prim's
    void minimumSpanningTree() const;

    //  [Matthew Done] 8)  Minimum spanning forest with Kruskals
    void minimumSpanningForest() const;

    bool isConnected() const;


private:
    //  The main vector 'vertices' that contains the list of every unique airport
    std::vector<T> vertices; 
    //  Vector edges which contains 
    std::vector<std::vector<Edge>> edges; 

    //  Given a input vertex, it will return the index. Returns -1 if not found
    int getVertexIndex(const T& vs) const;

    //helper function to grab the state abriviation 
    std::string getStateAbbreviation(std::string city_state_string) const;

    bool hasEdge(int i1, int i2) const;
    void DFS(int i, std::vector<bool>& visited) const;
};

#include "WeightedGraph.tpp"

#endif
