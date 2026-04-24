#include "WeightedGraph.hpp"
#include <iostream>
#include <queue>
#include <climits>

//------------------------------------------------------------------------------------------------------------------------------------------

template <typename T>
void WeightedGraph<T>::insertVertex(const T& v) {
    if (getVertexIndex(v) != -1) {
        std::cout << "insertVertex: vertex already exist\n";
        return;
    }

    vertices.push_back(v);
    std::vector<Edge> tmp;
    edges.push_back(tmp); //insert empty vector to the edges
}

//------------------------------------------------------------------------------------------------------------------------------------------

//Weight=distance
template <typename T>
void WeightedGraph<T>::insertEdge(const T& v1, const T& v2, int weight, int price) {
    //i1 is index of source airport
    int i1 = getVertexIndex(v1);

    //i2 is index of destination airport
    int i2 = getVertexIndex(v2);
    if (i1 == -1 || i2 == -1) {
        std::cout << "insertEdge: incorrect vertices\n";
        return;
    }

    if (!hasEdge(i1, i2)) {
        //create edge object with origin, origin index, destination, destination index, distance, and price.
        edges[i1].push_back(Edge(v1, i1, v2, i2, weight, price));
    }
}  

//------------------------------------------------------------------------------------------------------------------------------------------

template <typename T>
int WeightedGraph<T>::getVertexIndex(const T& ver) const {
    for(int i = 0; i < vertices.size(); i++) {
        if (vertices[i] == ver) {
            return i;
        }
    }

    return -1;
}

//------------------------------------------------------------------------------------------------------------------------------------------

// template <typename T>
// void WeightedGraph<T>::print() const {
    //     for (int i = 0; i < vertices.size(); i++) {
        //         std::cout << "{ " << vertices[i] << ": ";
        //         for(int j = 0; j < edges[i].size(); j++) {
            //             std::cout << vertices[edges[i][j]] << ' ';
            //         }
            //         std::cout << " }\n";
            //     }
            // }
            
            
template <typename T>
void WeightedGraph<T>::print() const {
    for (int i = 0; i < vertices.size(); i++) {
        std::cout << vertices[i] << std::endl;
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------

template <typename T>
bool WeightedGraph<T>::hasEdge(int i1, int i2) const {
    // Safety check for valid index range
    if (i1 < 0 || i1 >= edges.size()) {
        return false;
    }

    // Loop through all edges starting at the source index i1
    for (const auto& edge : edges[i1]) { 
        // Compare the stored destination index with the target index i2
        if (edge.destination_idx == i2) { 
            return true;
        }
    }

    return false;
}

//OLD HAS_EDGE
// template <typename T>
// bool WeightedGraph<T>::hasEdge(int i1, int i2) const {
//     if (i1 < 0 || i1 >= edges.size()) {
//         return false;
//     }

//     for (int i : edges[i1]) {
//         if (i == i2) {
//             return true;
//         }
//     }

//     return false;
// }

//------------------------------------------------------------------------------------------------------------------------------------------

// template <typename T>
// void WeightedGraph<T>::DFS() const {
//     if (vertices.empty()) {
//         return;
//     }
//     std::vector<bool> visited(vertices.size(), false);
//     DFS(0, visited);
// }

//------------------------------------------------------------------------------------------------------------------------------------------

// template <typename T>
// void WeightedGraph<T>::DFS(int i, std::vector<bool>& visited) const {
//     visited[i] = true;
//     std::cout << vertices[i] << " -> ";

//     // Look through all the neighbours
//     for (int j : edges[i]) {
//         if (!visited[j]) {
//             DFS(j, visited);
//         }
//     }
// }

//------------------------------------------------------------------------------------------------------------------------------------------

// template <typename T>
// void WeightedGraph<T>::BFS(int start) const {
//     if (vertices.empty() || start < 0 || start >= vertices.size()) {
//         return;
//     }

//     std::vector<bool> discovered(vertices.size(), false);
//     std::queue<int> where_to_go;

//     where_to_go.push(start);
//     discovered[start] = true;

//     while (!where_to_go.empty()) {
//         int cur = where_to_go.front();
//         std::cout << vertices[cur];
//         where_to_go.pop();

//         // Explore the neighbors
//         for (int j : edges[cur]) {
//             if (!discovered[j]) {
//                 where_to_go.push(j);
//                 discovered[j] = true;
//             }
//         }

//     }   

// }

//------------------------------------------------------------------------------------------------------------------------------------------

// [Matthew TODO] Find shortest path by distance between origin airport and destination
// Must output path and total distance
template <typename T>
void WeightedGraph<T>::shortestPath(const T& src, const T& dest) const {
    // Find vertex indices from the airport abrivations
    int i_src = getVertexIndex(src);
    int i_dest = getVertexIndex(dest);

    //-------------------------------------------------------------------------------------

    // Check edge cases

    //if either airport doesn't exist in the vector of unique airports (the vertex index is -1) print an error
    if (i_src == -1 || i_dest == -1) {
        std::cout << "Shortest route from " << src << " to " << dest << ": None" <<std::endl;
        return;
    }
    //if the origin and destination are the same just print the origin
    if (i_src == i_dest) {
        std::cout << "Shortest route from " << src << " to " << dest << ": " << src << ". The length is 0. The cost is 0." << std::endl;
        return;
    }

    //--------------------------------------------------------------------------------------

    //CREATING VECTORS TO TRACK NAMES, PRICE, AND DISTANCE

    // Create distances vector
    std::vector<int> distances(vertices.size()); // distances from source to all other nodes
    // Set initial distances
    for (int i = 0; i < distances.size(); i++) {
        // Using a large number INT_MAX to represent infinity so -1 doesn't break comparisons
        distances[i] = (i == i_src) ? 0 : INT_MAX;
    }

    //create a predecessor vector that keeps track of which airports you've visited in the attempt of finding the shortest path.
    std::vector<int> predecessor(vertices.size(), -1);

    //create a price vector to update the price with each new path update
    std::vector<int> price(vertices.size(), 0);

    //---------------------------------------------------------------------------------------
    // Perform BFS and update distances


    std::vector<int> q;
    q.push_back(i_src);

    while (!q.empty()) {
        //Find the index in 'q' that has the smallest value in distances
        int smallestIdx = 0;
        for (int i = 1; i < q.size(); i++) {
            if (distances[q[i]] < distances[q[smallestIdx]]) {
                smallestIdx = i;
            }
        }
        //Get the actual airport index and remove it from the queue
        int cur = q[smallestIdx];
        q.erase(q.begin() + smallestIdx);

        // Check the neighbors of current node
        for (const auto& edge : edges[cur]) {
            int neighborIdx = edge.destination_idx; 
            int newDist = distances[cur] + edge.distance;

            if (newDist < distances[neighborIdx]) { 
                distances[neighborIdx] = newDist;
                price[neighborIdx] = price[cur] + edge.cost;
                predecessor[neighborIdx] = cur;
                q.push_back(neighborIdx);
            }
        }
    }

    // Check if a path was actually found
    if (distances[i_dest] >= 1000000) {
        std::cout << "Shortest route from " << src << " to " << dest << ": None" << std::endl;
        return; 
    }

    // Path Reconstruction
    std::vector<T> path;
    for (int v = i_dest; v != -1; v = predecessor[v]) {
        path.push_back(vertices[v]);
    }

    // Output formatted result
    std::cout << "Shortest route from " << src << " to " << dest << ": ";
    for (int i = path.size() - 1; i >= 0; i--) {
        std::cout << path[i] << (i == 0 ? "" : " -> ");
    }
    std::cout << ". The length is " << distances[i_dest] << ". The cost is " << price[i_dest] << "." << std::endl;

    return; // No path exists
}

//------------------------------------------------------------------------------------------------------------------------------------------

//  [Evan Done?] 5) count and display the direct flight connections for each airport
//  This works exactly as expected for the Testing sample set. will check again after csv data is functioning
template <typename T>
void WeightedGraph<T>::countDirectFlights() const {

    // 'verticies' has a list of every unique airport vertex
    //  using a hashmap I can count the amount of times each origin has an outgoing
    //  flight as well as every time a flight has one incomming.

    //  hash of key (string)==[ABE, ABQ, etc] and value (int) count of direct flights
    HashMap<std::string, int> map(7);

    //  initialize the hash with all of the unique airports
    for (int i = 0; i < vertices.size(); i++) {
        map.insert(vertices[i]);
    }

    //  loop through edges, and add for each flight both ways
    for (int i = 0; i < edges.size(); i++) {
        //  origin airport <here>

        //  for each origin, increment self by quantity of edges
        map.incrementValue(vertices[i], edges[i].size());

        for (int j = 0; j < edges[i].size(); j++) {
            //  each edge or incomming connection <here>

            //  for each edge increment destination by 1
            map.incrementValue(edges[i][j].destination);

        }

    }

    //output
    map.mapOutput();
    
    //  this is only so they look good with spaces after multiple display functions are called
    //std::cout << std::endl;

    /*
        Sample Output:
        Airport Connections
        ATL     12
        ORD     11
        MIA     11
    */

}
