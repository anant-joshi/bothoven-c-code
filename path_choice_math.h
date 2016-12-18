#ifndef PATH_CHOICE_MATH_HEADER
#define PATH_CHOICE_MATH_HEADER 

//Header file containing all the maths required to choose a path

#include "bothoven_graph.h"
#include <math.h>
#include <stdlib.h>

both_node coordinates_transform(int curr_node_index, int prev_node_index, int given_node_index){
	float a1,a0,b1,b0,x,y,A,B,S,X,Y;
	both_node new_node;
	a1 = bothoven_nodes[prev_node_index].x;
	b1 = bothoven_nodes[prev_node_index].y;
	a0 = bothoven_nodes[curr_node_index].x;
	b0 = bothoven_nodes[curr_node_index].y;
	x = bothoven_nodes[given_node_index].x;
	y = bothoven_nodes[given_node_index].y;
	A = a1-a0;
	B = b1-b0;
	S = sqrt(A*A+B*B);
	X = (B*(y-b0)-A*(x-a0))/S;
	Y = -(B*(x-a0)+A*(y-b0))/S;
	new_node.x = X;
	new_node.y = Y;
	new_node.neighbours = NULL;
}

float get_angle(both_node node){
	float x,y;
	x = node.x;
	y = node.y;
	return (y<0)?-atan(y/x):atan(y/x);
}

/*
	Function Name:	path_number
	Input:			node index of current, node index of previous, and node index of node to be visited
	Output: 		The number of the paths before the path to be taken (-ve indicates clockwise direction movement)
	Logic:			Transform axes for all neighbours
					Get the relative angles of the neighbouring nodes

	Example Call:	path_number(<curr_index>,<prev_index>,<next_index>);
*/

int path_number(int curr_index, int prev_index, int next_index){
	int i,j, m = 0;
	both_node neighbours[MAX_NEIGHBOURS], selected;
	float *angles, theta;
	j = 0;
	for(i = 0; i<MAX_NEIGHBOURS; i++){
		if(bothoven_nodes[curr_index].neighbours[i]>=0)
			neighbours[j++] = coordinates_transform(curr_index, prev_index, bothoven_nodes[curr_index].neighbours[i]);
	}
	selected = coordinates_transform(curr_index, prev_index, next_index);
	theta = get_angle(selected);
	angles = malloc(sizeof(float)*j);
	for(i=0, j=0; i<MAX_NEIGHBOURS; i++){
		if(bothoven_nodes[curr_index].neighbours[i]>=0){
			angles[j] = get_angle(neighbours[j]);
			j++;
		}
	}
	for(i = 0; i<j; i++){
		if(theta<0){
			if(angles[i]<0 && angles[i]>theta && fabs(theta-angles[i])>0.001){
				m--;
			}
		}else{
			if(angles[i]>=0 && angles[i]<theta && fabs(theta-angles[i])>0.001){
				m++;
			}
		}
	}
	return m;
}

#endif