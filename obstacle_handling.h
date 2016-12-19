#include "dijkstras_algo.h"
#include "bothoven_graph.h"
#include <stdlib.h>
#define PROX_THRESHOLD 30

char check(int prox, int prev, int next){    //update global next
	if(prox>PROX_THRESHOLD){
		remove_egde(prev, next)
		dijkstra(grid_of_nodes, prev);
		return 1;
	}
	return 0;
}
