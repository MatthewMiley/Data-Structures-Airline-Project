#include "WeightedGraph.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <set>
#include <iostream>

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

        // temp container, stores split fields from one row
        std::vector<std::string> csv_fields;
        
        // temp string, builds current field character by character
        std::string current_csv_field = "";

        // split csv line into fields using comma separator
        for (int i = 0; i < (int)line.size(); i++) {
            char current_char = line[i];

            if (current_char == ',') {
                csv_fields.push_back(current_csv_field);
                current_csv_field = "";
            } 
            
            else {
                current_csv_field += current_char;
            }
        }
        // push back after processing 
        csv_fields.push_back(current_csv_field);

        // extract values
        std::string origin = csv_fields[0];
        std::string dest   = csv_fields[1];

        int distance = std::stoi(csv_fields[4]);
        int cost     = std::stoi(csv_fields[5]);

        // collect unique airports for later insertion as graph nodes
        if (airport_set.insert(origin).second) {
            airports.push_back(origin); //"***" where each * is a letter?
        }
        if (airport_set.insert(dest).second)
            airports.push_back(dest);

        // collect distances and costs for later insertion of edges
        flight_labels.push_back({origin, dest});
        flight_weights_distance_cost.push_back({distance, cost});
    }

    file.close();

    // build vertices
    for (int i = 0; i < (int)airports.size(); i++) {
        Airport_Graph.insertVertex(airports[i]);
    }

    // build edges (unchanged style)
    for (size_t i = 0; i < flight_labels.size(); i++) {
        Airport_Graph.insertEdge(
            flight_labels[i][0], // start node
            flight_labels[i][1], // end node
            flight_weights_distance_cost[i][0], // distance
            flight_weights_distance_cost[i][1] // cost
        );
    }

    return 0;
}