#include <dijkstras_algo.h>
#include <bothoven_graph.h>
#include <stdlib.h>
#define PROX_THRESHOLD 30

void check(int prox, int prev, int next){    //updatte global next
	if(prox>PROX_THRESHOLD){
		remove_egde(prev, next)
		dijkstra(graph, prev);
	}
}