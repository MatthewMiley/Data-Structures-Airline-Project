#include "WeightedGraph.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <set>
#include <iostream>

int main(void) {

    /* IMPLEMENTATION OF THE ORIGINAL GRAPH */

    WeightedGraph<std::string> TEST_Airport_Graph;

    //  =================================================================================================================================
    //  EVERYTHING BETWEEN THE TWO === LINES IS FOR TESTING PURPOSES ONLY DO NOT INCLUDE IN FINAL

    // A vector of limited airports for quick testing as recommended by Igor
    std::vector<std::string> TEST_airports = {"ABE","ABQ","ABY","ACT"};
    // create a node for every unique airport using the vector
    for (int i = 0; i < (int)TEST_airports.size(); i++ ) {
        TEST_Airport_Graph.insertVertex(TEST_airports[i]);
    }

    // 2D vector of all of the origins/destinations of flights (again, quicker for me and quicker for the computer)
    std::vector<std::vector<std::string>> TEST_flight_labels = {
        {"ABE", "ABQ"},{"ABE", "ABY"},{"ABQ", "ACT"},{"ACT", "ABE"}};

    // 2D vector of all of the costs/distances of flights
    std::vector<std::vector<int>> TEST_flight_weights_distance_cost = {
        {424, 374},{744, 106},{274, 225},{194, 123}};


        //  Create the edges
        for (size_t i = 0; i < TEST_flight_labels.size(); i++)
        TEST_Airport_Graph.insertEdge( TEST_flight_labels[i][0], TEST_flight_labels[i][1], TEST_flight_weights_distance_cost[i][0], TEST_flight_weights_distance_cost[i][1]);

    //  =================================================================================================================================


    //  ---------------------------------------------------------------------------------------------------------------------------------  
    //  COMMENTED OUT FOR TESTING PURPOSES EVERYTHING BETWEEN THE --- LINES IS INTEDNED FOR THE FINAL AFTER REVISION
    
    // // // Open csv file
    // std::ifstream file("airports.csv");

    // // check that file opened correctly
    // if (!file.is_open()) {
    //     std::cerr << "Error: could not open airports.csv\n";
    //     return 1;
    // }

    // std::string line;

    // // vector of strings of airport names 
    // std::vector<std::string> airports;

    // // flights represented by 2 2D vectors: one for labels and one for distance/cost 
    // std::vector<std::vector<std::string>> flight_labels;
    // std::vector<std::vector<int>> flight_weights_distance_cost;

    // // Use set only to avoid duplicate airport inserts
    // std::set<std::string> airport_set;

    // // Skip header
    // std::getline(file, line);

    // // execute loop on each line to extract data
    // while (std::getline(file, line)) {

    //     // temp container, stores split fields from one row
    //     std::vector<std::string> csv_fields;
        
    //     // temp string, builds current field character by character
    //     std::string current_csv_field = "";

    //     // split csv line into fields using comma separator
    //     for (int i = 0; i < (int)line.size(); i++) {
    //         char current_char = line[i];

    //         if (current_char == ',') {
    //             csv_fields.push_back(current_csv_field);
    //             current_csv_field = "";
    //         } 
            
    //         else {
    //             current_csv_field += current_char;
    //         }
    //     }
    //     // push back after processing 
    //     csv_fields.push_back(current_csv_field);

    //     // extract values
    //     std::string origin = csv_fields[0];
    //     std::string dest   = csv_fields[1];

    //     int distance = std::stoi(csv_fields[4]);
    //     int cost     = std::stoi(csv_fields[5]);

    //     // collect unique airports for later insertion as graph nodes
    //     if (airport_set.insert(origin).second) {
    //         airports.push_back(origin); //"***" where each * is a letter?
    //     }
    //     if (airport_set.insert(dest).second)
    //         airports.push_back(dest);

    //     // collect distances and costs for later insertion of edges
    //     flight_labels.push_back({origin, dest});
    //     flight_weights_distance_cost.push_back({distance, cost});
    // }

    // file.close();

    // // build vertices
    // for (int i = 0; i < (int)airports.size(); i++) {
    //     Airport_Graph.insertVertex(airports[i]);
    // }

    // // build edges (unchanged style)
    // for (size_t i = 0; i < flight_labels.size(); i++) {
    //     Airport_Graph.insertEdge(
    //         flight_labels[i][0], // start node
    //         flight_labels[i][1], // end node
    //         flight_weights_distance_cost[i][0], // distance
    //         flight_weights_distance_cost[i][1] // cost
    //     );
    // }

    //  MANDATORY INCLUDE IN FINAL
    //  THE ABOVE IS COMMENTED OUT FOR TESTING PURPOSES
    //  ---------------------------------------------------------------------------------------------------------------------------------  

    
    //Testing Code Below Here:
    
    //  generic print to view the graph status
    TEST_Airport_Graph.print();
    
    std::cout << std::endl;

    //  Shortest Path
    TEST_Airport_Graph.shortestPath("BNA", "ATL");
    
    std::cout << std::endl;

    //  Task 5 direct flight count
    TEST_Airport_Graph.countDirectFlights();

    return 0;
}