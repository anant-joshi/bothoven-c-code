#ifndef MNP_POSITIONS_HEADER
#define MNP_POSITIONS_HEADER

	#ifndef MAX_MNP_NODE_VALUES
	#define MAX_MNP_NODE_VALUES 6
	#endif
	
	#ifndef NUM_MNP_NODES
	#define NUM_MNP_NODES 33
	#endif

typedef struct{
	int node_indexes[MAX_MNP_NODE_VALUES]
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

void init_mnp(){
	int i;
	for(i = 0; i < 24; i++){
		add_mnp_info(i, NULL); 
	}
	add_mnp_info(24, {0,1,23,24,25,42});
	add_mnp_info(25, {24,25,26,27,42,43});
	add_mnp_info(26, {3,4,5,26,27,28});
	add_mnp_info(27, {7,8,9,29,30,31});
	add_mnp_info(28, {30,31,32,33,44,45});
	add_mnp_info(29, {11,12,13,32,33,34});
	add_mnp_info(30, {15,16,17,35,36,37});
	add_mnp_info(31, {36,37,38,39,46,47});
	add_mnp_info(32, {19,20,21,38,39,40});
}

#endif