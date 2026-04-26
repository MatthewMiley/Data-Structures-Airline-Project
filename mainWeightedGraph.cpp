#include "WeightedGraph.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <set>
#include <iostream>
#include <stdexcept>

int main(void) {

    /* IMPLEMENTATION OF THE ORIGINAL GRAPH */

    WeightedGraph<std::string> Airport_Graph;    

    // Open csv file
    std::ifstream file("airports.csv");

    // check that file opened correctly
    if (!file.is_open()) {
        std::cerr << "Error: could not open airports.csv\n";
        return 1;
    }

    std::string line;

    // vector of strings of airport names 
    std::vector<std::string> airports;

    // flights represented by 2 2D vectors: one for labels and one for distance/cost 
    std::vector<std::vector<std::string>> flight_labels;
    std::vector<std::vector<int>> flight_weights_distance_cost;

    // Use set only to avoid duplicate airport inserts
    std::set<std::string> airport_set;

    // Skip header
    std::getline(file, line);

    // execute loop on each line to extract data
    while (std::getline(file, line)) {
        // Skip empty lines to prevent processing errors
        if (line.empty() || line.find_first_not_of(" \t\n\r") == std::string::npos) {
            continue;
        }

        std::vector<std::string> csv_fields;
        std::string current_csv_field = "";
        
        // NEW QUOTE-AWARE PARSING LOGIC
        bool inQuotes = false;
        for (int i = 0; i < (int)line.size(); i++) {
            char current_char = line[i];

            // Ignore Windows carriage returns
            if (current_char == '\r') continue;

            // Toggle quote mode
            if (current_char == '\"') {
                inQuotes = !inQuotes;
                continue; 
            }

            // Only split on comma if we are NOT inside a quoted city name
            if (current_char == ',' && !inQuotes) {
                csv_fields.push_back(current_csv_field);
                current_csv_field = "";
            } 
            else {
                current_csv_field += current_char;
            }
        }
        csv_fields.push_back(current_csv_field);

        // Ensure the row has enough columns (Distance is index 4, Cost is index 5)
        if (csv_fields.size() < 6) {
            continue;
        }

        try {
            std::string origin = csv_fields[0];
            std::string dest   = csv_fields[1];

            // std::stoi will now receive clean numbers
            int distance = std::stoi(csv_fields[4]);
            int cost     = std::stoi(csv_fields[5]);

            // collect unique airports
            if (airport_set.insert(origin).second) {
                airports.push_back(origin); 
            }
            if (airport_set.insert(dest).second) {
                airports.push_back(dest);
            }

            flight_labels.push_back({origin, dest});
            flight_weights_distance_cost.push_back({distance, cost});
        } 
        catch (const std::exception& e) {
            // Silently skip malformed rows
            continue;
        }
    }

    file.close();

    // build vertices
    for (int i = 0; i < (int)airports.size(); i++) {
        Airport_Graph.insertVertex(airports[i]);
    }

    // build edges using the updated 4-parameter insertEdge
    for (size_t i = 0; i < flight_labels.size(); i++) {
        Airport_Graph.insertEdge(
            flight_labels[i][0], 
            flight_labels[i][1], 
            flight_weights_distance_cost[i][0], 
            flight_weights_distance_cost[i][1]
        );
    }
    //----------------------------------------------------------------------------------------------------
    std::cout << "All Unique Airports: " << std::endl;
    Airport_Graph.print();
    std::cout << "------------------------------------------" << std::endl;

    // [Matthew TODO][DONE] Find shortest path by distance between origin airport and destination
    // Must output path and total distance
    Airport_Graph.shortestPath("BNA", "ATL");
    std::cout << "------------------------------------------" << std::endl;

    // [Evan DONE] 5) count and display the direct flight connections for each airport
    Airport_Graph.countDirectFlights();
    std::cout << "------------------------------------------" << std::endl;
    
    // [Evan TODO] 6) creat a undirected graph from the original using minimum cost routes
    WeightedGraph<std::string> undirectedAirportGraph = Airport_Graph.undirectedGraph();
    std::cout << "------------------------------------------" << std::endl;

    // [Matthew DONE] 8) Minimum spanning forest with Kruskals
    // Generate a minimum spanning forest using Kruskal’s algorithm.
    Airport_Graph.minimumSpanningForest();
    std::cout << "------------------------------------------" << std::endl;

    return 0;
}
