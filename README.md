# Data-Structures-Airline-Project
Data structures project around managing an airport.


Here is the list of things your project should support:

1) Read the information from the dataset (a csv file) and create a weighted directed graph. Each edge
must store two weights: Distance and Cost.

3) Find the shortest by distance path between a given origin airport and destination airport. The
algorithm must output both the path and its total length. If such a path does not exist, the program
must display an appropriate message.

5) Find the shortest by distance paths between a given origin airport to each airport located in a given
destination state. The algorithm must output each path and its corresponding length. If no such
paths exist, the program must display an appropriate message.

7) Find the shortest by distance path between a given origin airport and destination airport with a
specified number of stops. A stop is defined as an intermediate airport between the origin and
destination. The path must include exactly the specified number of stops. The algorithm must
output the path, total distance, and total cost. If no such path exists, the program must display an
appropriate message.

9) Count and display the total number of direct flight connections for each airport. You must consider
both outbound and inbound flights. For example, if Tampa airport has direct inbound flights from
Miami, Orlando, and Atlanta, then its inbound count is 3. If Tampa has a direct outbound flight
only to New York, then its outbound count is 1. Therefore, the total number of direct flight
connections for Tampa is 4. The list of airports must be sorted in descending order based on the
total number of direct flight connections.

11) Create an undirected graph from the original directed graph using the following rules:
a. For each pair of vertices u and v, if there is only one directed edge(either (u,v) or (v,u))
between them, you keep that single edge with its corresponding cost as an undirected
weighted edge. You can ignore the distance on that edge.
b. For each pair of vertices u and v, if there are two directed edges (u,v) and (v, u) between
them, you keep the one with the minimum cost value as an undirected weighted edge.
You can ignore the distance on that edge.

13) Generate a minimum spanning tree using Prim’s algorithm. The algorithm must output both the
edges in the MST and its total cost. In this step, cost must be used as the edge weight. If the graph
is disconnected, the program must report that an MST cannot be formed. A connected graph is one
in which a path exists between every pair of vertices.

15) Generate a minimum spanning forest using Kruskal’s algorithm. The algorithm must output the
edges included in the forest and its total cost. In this step, cost must be used as the edge weight. If
the graph is disconnected, the program must output a minimum spanning forest consisting of
one minimum spanning tree for each connected component.
