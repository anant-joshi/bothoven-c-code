#ifndef MNP_POSITIONS_HEADER
#define MNP_POSITIONS_HEADER

	#ifndef MAX_MNP_NODE_VALUES
	#define MAX_MNP_NODE_VALUES 6
	#endif
	
	#ifndef NUM_MNP_NODES
	#define NUM_MNP_NODES 33
	#endif
#include "dijkstras_algo.h"

typedef struct{
	int node_indexes[MAX_MNP_NODE_VALUES];
}mnp_node;

mnp_node note_positions[NUM_MNP_NODES];

void add_mnp_info(int mnp, int arr[MAX_MNP_NODE_VALUES]){
	int i;
	for(i = 0; i< MAX_MNP_NODE_VALUES; i++) note_positions[mnp].node_indexes[i] = -1;
	if(mnp < 24){
		note_positions[mnp].node_indexes[0] = mnp;		
	}else{
		for(i = 0; i< MAX_MNP_NODE_VALUES; i++)
			note_positions[mnp].node_indexes[i] = arr[i];
	}
}

int optimum_node_from_mnp(int mnp){
	int min_dist_index,i, min_dist;
	mnp_node node = note_positions[mnp];
	min_dist = 5000;
	for(i = 0; i<NUM_MNP_NODES && node.node_indexes[i]!=-1; i++){
		if(dist[node.node_indexes[i]]<min_dist){
			min_dist = dist[node.node_indexes[i]];
			min_dist_index = node.node_indexes[i];
		}
	}
	return min_dist_index;
}

void init_mnp(){
	int i;
	int arr1[6] = {0,1,23,24,25,42};
	int arr2[6] = {24,25,26,27,42,43};
	int arr3[6]= {3,4,5,26,27,28};
	int arr4[6]= {7,8,9,29,30,31};
	int arr5[6]= {30,31,32,33,44,45};
	int arr6[6]= {11,12,13,32,33,34};
	int arr7[6]= {15,16,17,35,36,37};
	int arr8[6]= {36,37,38,39,46,47};
	int arr9[6]= {19,20,21,38,39,40};

	for(i = 0; i < 24; i++){
		add_mnp_info(i, NULL); 
	}
	add_mnp_info(24, arr1);
	add_mnp_info(25, arr2);
	add_mnp_info(26, arr3);
	add_mnp_info(27, arr4);
	add_mnp_info(28, arr5);
	add_mnp_info(29, arr6);
	add_mnp_info(30, arr7);
	add_mnp_info(31, arr8);
	add_mnp_info(32, arr9);
}

#endif