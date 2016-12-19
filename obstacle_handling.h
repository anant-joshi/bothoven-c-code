#ifndef OBSTACLE_HANDLING_HEADER
#define OBSTACLE_HANDLING_HEADER 

#include "dijkstras_algo.h"
#include "bothoven_graph.h"
#include "motor_movement.h"
#include "follow_line.h"
#include "obstacle_handling.h"
#include <stdlib.h>

#define PROX_THRESHOLD 30
#define SHARP_THRESHOLD 100

char handle_obstacle(int curr, int next, int num_paths){    //update global next
	unsigned char analog, distance;
	char sensor = pick_sensor(curr,next);
	if(sensor == 1){
		analog = ADC_Conversion(11); 		// add params
		distance = Sharp_GP2D12_estimation(analog);
		if(distance>SHARP_THRESHOLD){
		remove_edge(curr, next)
		dijkstra(grid_of_nodes, curr);
		turn_to_path(-num_paths);
		return 1;
	}
	return 0;
	}

	else{
		distance = ADC_Conversion(11);    //add params
		if(distance<PROX_THRESHOLD){
		remove_edge(curr, next)
		dijkstra(grid_of_nodes, curr);
		turn_to_path(-num_paths);
		return 1;
	}
	return 0;
	}

}


#endif
