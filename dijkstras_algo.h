#ifndef DIJKSTRAS_ALGO_HEADER
#define DIJKSTRAS_ALGO_HEADER

#include <stdlib.h>
#include <limits.h>

int sp_parent[NUM_GRAPH_NODES];
int dist[NUM_GRAPH_NODES];
char sptSet[NUM_GRAPH_NODES]

int min_graph_distance(){
    // Initialize min value
    int min = INT_MAX, min_index,v;
 
    for (v = 0; v < NUM_GRAPH_NODES; v++)
        if (!sptSet[v] && dist[v] <= min)
            min = dist[v], min_index = v;
 
    return min_index;
}
 
// Function to print shortest path from source to j
// using parent array
void printPath(int j){
    // Base Case : If j is source
    if (sp_parent[j]==-1)
        return;
 
    printPath(parent, parent[j]);
	//do stuff here
	//move_to(j) (from curr_position)
	//TODO: add curr_pos as a global variable indicating the robot's current position
}
 
// Funtion that implements Dijkstra's single source shortest path
// algorithm for a graph represented using adjacency matrix
// representation
void dijkstra(int graph[NUM_GRAPH_NODES][NUM_GRAPH_NODES], int src){
	int i,u,v,count;
    //dist[NUM_GRAPH_NODES]; 
    // The output array. dist[i] will hold
    // the shortest distance from src to i
 
    // sptSet[i] will true if vertex i is included / in shortest
    // path tree or shortest distance from src to i is finalized
    //char sptSet[NUM_GRAPH_NODES];
 
    // Initialize all distances as INFINITE and stpSet[] as false
    for (i = 0; i < NUM_GRAPH_NODES; i++){
        sp_tree[0] = -1;
        dist[i] = INT_MAX;
        sptSet[i] = 0;
    }
 
    // Distance of source vertex from itself is always 0
    dist[src] = 0;
 
    // Find shortest path for all vertices
    for (count = 0; count < NUM_GRAPH_NODES-1; count++){
        // Pick the minimum distance vertex from the set of
        // vertices not yet processed. u is always equal to src
        // in first iteration.
        u = min_graph_distance(dist, sptSet);
 
        // Mark the picked vertex as processed
        sptSet[u] = 1;
 
        // Update dist value of the adjacent vertices of the
        // picked vertex.
        for (v = 0; v < NUM_GRAPH_NODES; v++)
            if (!sptSet[v] && graph[u][v] &&  dist[u] + graph[u][v] < dist[v]){
                sp_tree[v]  = u;
                dist[v] = dist[u] + graph[u][v];
            }  
    }
}
#endif