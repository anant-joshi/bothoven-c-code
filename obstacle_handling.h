#ifndef OBSTACLE_HANDLING_HEADER
#define OBSTACLE_HANDLING_HEADER 

#include "dijkstras_algo.h"
#include "bothoven_graph.h"
#include "motor_movement.h"
#include "follow_line.h"
#include <stdlib.h>
#define PROX_THRESHOLD 30

char handle_obstacle(int prox, int prev, int next, int num_paths){    //update global next
	if(prox>PROX_THRESHOLD){
		remove_edge(prev, next)
		dijkstra(grid_of_nodes, prev);
		turn_to_path(-num_paths);
		return 1;
	}
	return 0;
}

#endif