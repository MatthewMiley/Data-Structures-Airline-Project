#include "WeightedGraph.hpp"
#include <iostream>
#include <queue>
#include <climits>

//------------------------------------------------------------------------------------------------------------------------------------------

template <typename T>
void WeightedGraph<T>::insertVertex(const T& vertex_value) {
    // Check if the vertex already exists in the graph using getVertexIndex
    if (getVertexIndex(vertex_value) != -1) {
        // If found print an error message and exit the function
        std::cout << "insertVertex: vertex already exist\n";
        return;
    }

    // Add the new vertex value to the vertices vector
    vertices.push_back(vertex_value);
    // Create a temporary empty vector to hold edges for this new vertex
    std::vector<Edge> temporary_edge_list;
    // Add that empty edge list to the edges adjacency list
    edges.push_back(temporary_edge_list);
}

//------------------------------------------------------------------------------------------------------------------------------------------

//Weight=distance
template <typename T>
void WeightedGraph<T>::insertEdge(const T& vertex_1, const T& vertex_2, int weight, int price) {
    // Get the internal index for the source vertex
    int index_1 = getVertexIndex(vertex_1);
    // Get the internal index for the destination vertex
    int index_2 = getVertexIndex(vertex_2);

    // If either vertex wasn't found in the graph print error and return
    if (index_1 == -1 || index_2 == -1) {
        std::cout << "insertEdge: incorrect vertices\n";
        return;
    }

    // If the edge doesn't already exist between these two indices
    if (!hasEdge(index_1, index_2))  {
        // Add a new Edge object to the source vertex's adjacency list
        edges[index_1].push_back(Edge(vertex_1, index_1, vertex_2, index_2, weight, price));
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------

template <typename T>
int WeightedGraph<T>::getVertexIndex(const T& vertex_to_find) const {
    // Loop through the entire vertices vector
    for(int i = 0; i < vertices.size(); i++) {
        // If the current vertex matches the one we are looking for
        if (vertices[i] == vertex_to_find) {
            // Return the index of that vertex
            return i;
        }
    }
    // If we get through the whole loop without a match return -1
    return -1;
}

//------------------------------------------------------------------------------------------------------------------------------------------
            
template <typename T>
void WeightedGraph<T>::print() const {
    // Iterate through every vertex in the graph
    for (int i = 0; i < vertices.size(); i++) {
        // Print the vertex name followed by a newline
        std::cout << vertices[i] << std::endl;
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------

template <typename T>
bool WeightedGraph<T>::hasEdge(int index_1, int index_2) const {
    // Safety check for valid index range
    if (index_1 < 0 || index_1 >= edges.size()) {
        return false;
    }

    // Loop through all edges starting at the source index index_1
    for (const auto& edge : edges[index_1]) { 
        // Compare the stored destination index with the target index index_2
        if (edge.destination_idx == index_2) { 
            return true;
        }
    }

    return false;
}

//------------------------------------------------------------------------------------------------------------------------------------------

// [Matthew TODO][DONE] Find shortest path by distance between origin airport and destination
// Must output path and total distance
template <typename T>
void WeightedGraph<T>::shortestPath(const T& source, const T& destination) const {
    // Find vertex indices from the airport abbreviations
    int index_source = getVertexIndex(source);
    int index_destination = getVertexIndex(destination);

    //-------------------------------------------------------------------------------------

    // Check edge cases

    //if either airport doesn't exist in the vector of unique airports (the vertex index is -1) print an error
    if (index_source == -1 || index_destination == -1) {
        std::cout << "Shortest route from " << source << " to " << destination << ": None" <<std::endl;
        return;
    }
    //if the origin and destination are the same just print the origin
    if (index_source == index_destination) {
        std::cout << "Shortest route from " << source << " to " << destination << ": " << source << ". The length is 0. The cost is 0." << std::endl;
        return;
    }

    //--------------------------------------------------------------------------------------

    //CREATING VECTORS TO TRACK NAMES, PRICE, AND DISTANCE

    // Create distances vector
    std::vector<int> distances(vertices.size()); // distances from source to all other nodes
    // Set initial distances
    for (int i = 0; i < distances.size(); i++) {
        // Using a large number INT_MAX to represent infinity so -1 doesn't break comparisons
        distances[i] = (i == index_source) ? 0 : INT_MAX;
    }

    //create a predecessor vector that keeps track of which airports you've visited in the attempt of finding the shortest path.
    std::vector<int> predecessor(vertices.size(), -1);

    //create a price vector to update the price with each new path update
    std::vector<int> price(vertices.size(), 0);

    //---------------------------------------------------------------------------------------
    // Perform BFS and update distances


    // Use a vector as a queue for manual processing
    std::vector<int> processing_queue;
    // Start with the source index in the queue
    processing_queue.push_back(index_source);

    // Continue as long as there are airports left to explore
    while (!processing_queue.empty()) {
        //Find the index in 'processing_queue' that has the smallest value in distances
        int smallest_index_in_queue = 0;
        for (int i = 1; i < processing_queue.size(); i++) {
            if (distances[processing_queue[i]] < distances[processing_queue[smallest_index_in_queue]]) {
                smallest_index_in_queue = i;
            }
        }
        //Get the actual airport index and remove it from the queue
        int current_vertex = processing_queue[smallest_index_in_queue];
        processing_queue.erase(processing_queue.begin() + smallest_index_in_queue);

        // Check the neighbors of current node
        for (const auto& edge : edges[current_vertex]) {
            // Get the destination index of the current edge
            int neighbor_index = edge.destination_idx; 
            // Calculate the total distance from source to this neighbor
            int new_distance = distances[current_vertex] + edge.distance;

            // If we found a shorter path to this neighbor
            if (new_distance < distances[neighbor_index]) { 
                // Update the shortest distance to this neighbor
                distances[neighbor_index] = new_distance;
                // Update the running price total for this path
                price[neighbor_index] = price[current_vertex] + edge.cost;
                // Track where we came from to reconstruct the path later
                predecessor[neighbor_index] = current_vertex;
                // Add the neighbor to the queue to explore its neighbors
                processing_queue.push_back(neighbor_index);
            }
        }
    }

    // Check if a path was actually found (using a high number check for unreachable nodes)
    if (distances[index_destination] >= 1000000) {
        std::cout << "Shortest route from " << source << " to " << destination << ": None" << std::endl;
        return; 
    }

    // Path Reconstruction
    // Create a vector to store the path in reverse order
    std::vector<T> reconstructed_path;
    // Walk backwards from destination to source using the predecessor links
    for (int current_step = index_destination; current_step != -1; current_step = predecessor[current_step]) {
        reconstructed_path.push_back(vertices[current_step]);
    }

    // Output formatted result
    std::cout << "Shortest route from " << source << " to " << destination << ": ";
    // Loop backwards through the path vector to print from source to destination
    for (int i = reconstructed_path.size() - 1; i >= 0; i--) {
        // Print the airport and an arrow if it's not the last one
        std::cout << reconstructed_path[i] << (i == 0 ? "" : " -> ");
    }
    // Print the final stats for distance and price
    std::cout << ". The length is " << distances[index_destination] << ". The cost is " << price[index_destination] << "." << std::endl;

    return; // No path exists
}

//------------------------------------------------------------------------------------------------------------------------------------------

//  [Evan Done?] 5) count and display the direct flight connections for each airport
//  This works exactly as expected for the Testing sample set. will check again after csv data is functioning
template <typename T>
void WeightedGraph<T>::countDirectFlights() const {

    std::cout << "Total Number of Direct Flights: " << std::endl;

    // 'vertices' has a list of every unique airport vertex
    //  using a hashmap I can count the amount of times each origin has an outgoing
    //  flight as well as every time a flight has one incoming.

    //  hash of key (string)==[ABE, ABQ, etc] and value (int) count of direct flights
    HashMap<std::string, int> airport_map(300);

    //  initialize the hash with all of the unique airports
    for (int i = 0; i < vertices.size(); i++) {
        airport_map.insert(vertices[i]);
    }

    //  loop through edges and add for each flight both ways
    for (int i = 0; i < edges.size(); i++) {
        //  origin airport <here>

        //  for each origin increment self by quantity of edges
        airport_map.incrementValue(vertices[i], edges[i].size());

        // Loop through each edge specifically for the current origin
        for (int j = 0; j < edges[i].size(); j++) {
            //  each edge or incoming connection <here>

            //  for each edge increment destination by 1
            airport_map.incrementValue(edges[i][j].destination);

        }

    }

    // Print out the final tallies from the hashmap
    airport_map.mapOutput();
}
//------------------------------------------------------------------------------------------------------------------------------------------

//  [Evan TODO] 6) Undirected Graph
template <typename T>
WeightedGraph<T> WeightedGraph<T>::undirectedGraph() const {

    /*
        Create an undirected graph from the original directed graph using the following rules:
    
            a. For each pair of vertices u and v, if there is only one directed edge(either (u,v) or (v,u))
                between them, you keep that single edge with its corresponding cost as an undirected
                weighted edge. You can ignore the distance on that edge.
    
            b. For each pair of vertices u and v, if there are two directed edges (u,v) and (v, u) between
                them, you keep the one with the minimum cost value as an undirected weighted edge.
                You can ignore the distance on that edge

            //  Keep the existing edge with the smallest cost [ignore distance] and add the other for undirected, or modify it to match the first
    
            */
    std::cout << "Evan will do this soon" << std::endl;
}

//  [Matthew TODO] 8)  Minimum spanning forest with Kruskals
template <typename T>
void WeightedGraph<T>::minimumSpanningForest() const {

    /*
        Generate a minimum spanning forest using Kruskal’s algorithm. 
    */

    // --- BLOCK 1: GATHER ALL FLIGHTS ---
    // Collect edges into "parallel" vectors to keep track of where each flight 
    // starts, where it ends, and how much it costs.
    std::vector<int> source_indices;
    std::vector<int> destination_indices;
    std::vector<int> edge_costs;

    // For all edges, for each edge add source_indices, destination_indices, 
    // and edge cost to their respective vectors.
    for (int i = 0; i < edges.size(); i++) {
        for (int j = 0; j < edges[i].size(); j++) {
            // Push the current vertex index as the source
            source_indices.push_back(i);
            // Push the edge's destination index
            destination_indices.push_back(edges[i][j].destination_idx);
            // Push the price/cost to use as the weight for Kruskal's
            edge_costs.push_back(edges[i][j].cost); // Use cost as weight 
        }
    }

    // --- BLOCK 2: SORT BY PRICE ---
    // Kruskal's is "greedy"—it always tries to pick the cheapest flight first.
    // Sort (Selection Sort) by cost to organize flights from lowest to highest.
    for (int i = 0; i < edge_costs.size(); i++) {
        int minimum_index = i;
        for (int j = i + 1; j < edge_costs.size(); j++) {
            if (edge_costs[j] < edge_costs[minimum_index]) {
                minimum_index = j;
            }
        }
        // Swap cost, source, and destination to keep them synchronized
        int temporary_cost = edge_costs[i];
        edge_costs[i] = edge_costs[minimum_index];
        edge_costs[minimum_index] = temporary_cost;

        int temporary_source = source_indices[i];
        source_indices[i] = source_indices[minimum_index];
        source_indices[minimum_index] = temporary_source;

        int temporary_destination = destination_indices[i];
        destination_indices[i] = destination_indices[minimum_index];
        destination_indices[minimum_index] = temporary_destination;
    }

    // --- BLOCK 3: GROUP IDENTIFICATION ---
    // Instead of complex DSU logic, we give every airport a "Group ID."
    // At first, every airport is in its own group (Group 0, Group 1, Group 2...).
    std::vector<int> group_id(vertices.size());
    for (int i = 0; i < vertices.size(); i++) {
        group_id[i] = i;
    }

    // Tracker for the total cost of all edges in the forest
    int total_forest_cost = 0;
    std::cout << "Minimum Spanning Forest:" << std::endl;
    std::cout << "Edge       Weight" << std::endl;
    //            MIA - MDW (Cost: 75)

    // --- BLOCK 4: THE CONNECTION PROCESS ---
    // Process Edges in order of increasing cost (the sorted list).
    for (int i = 0; i < edge_costs.size(); i++) {
        int vertex_u = source_indices[i];
        int vertex_v = destination_indices[i];

        // Check if the two airports belong to different groups.
        // If roots are different, there is no cycle (they aren't connected yet).
        if (group_id[vertex_u] != group_id[vertex_v]) {
            
            // Union logic: Since we are connecting them, they must now share the same Group ID.
            // We save the ID we want to change so we don't lose it mid-loop.
            int old_id = group_id[vertex_u];
            int new_id = group_id[vertex_v];

            // Every airport that was in vertex_u's "club" now joins vertex_v's "club."
            for (int k = 0; k < group_id.size(); k++) {
                if (group_id[k] == old_id) {
                    group_id[k] = new_id;
                }
            }

            // Add the cost of this flight to the total running cost.
            total_forest_cost += edge_costs[i];

            // Output the edge included in the forest to match your required format.
            std::cout << vertices[vertex_u] << " - " << vertices[vertex_v] 
                      << " (Cost: " << edge_costs[i] << ")" << std::endl;
        }
    }

    // Output the final calculated cost of the entire forest
    std::cout << "Total Cost of Forest: " << total_forest_cost << std::endl;
}