#ifndef BOTHOVEN_GRAPH_HEADER
#define BOTHOVEN_GRAPH_HEADER

#ifndef NUM_GRAPH_NODES
#define NUM_GRAPH_NODES 48
#endif

#ifndef MAX_NEIGHBOURS
#define MAX_NEIGHBOURS 4
#endif

typedef struct{
	int x;
	int y;
	int neighbours[MAX_NEIGHBOURS];
}both_node;


both_node bothoven_nodes[NUM_GRAPH_NODES]; //array of struct nodes
							//nodes are according to their indices

char grid_of_nodes[NUM_GRAPH_NODES][NUM_GRAPH_NODES];

init_both_node(int index, int x, int y){
	int i, k = 0;
	both_node[index].x = x;
	both_node[index].y = y;
	for(i = 0; i< MAX_NEIGHBOURS; i++){
		both_node[index].neighbours[i] = -1;
	}
	for(i = 0; i < NUM_GRAPH_NODES; i++){
		if(grid_of_nodes[index][i]){
			both_node[index].neighbours[k++] = i;
		}
	}
}



void add_edge(int i, int j, int weight){
	grid_of_nodes[i][j] = grid_of_nodes[j][i] = weight; 
}

void remove_edge(int i, int j){
	grid_of_nodes[i][j] = grid_of_nodes[j][i] = 0;
}

void add_edges_to_graph(){
	add_edge(0,1,1);
	add_edge(1,2,1);
	add_edge(2,3,1);
	add_edge(3,4,1);
	add_edge(4,5,1);
	add_edge(5,6,1);
	add_edge(6,7,1);
	add_edge(7,8,1);
	add_edge(8,9,1);
	add_edge(9,10,1);
	add_edge(10,11,1);	
	add_edge(11,12,1);
	add_edge(12,13,1);

	add_edge(13,14,1);
	add_edge(14,15,1);
	add_edge(15,16,1);
	add_edge(16,17,1);
	add_edge(17,18,1);
	add_edge(18,19,1);
	add_edge(19,20,1);
	add_edge(20,21,1);
	add_edge(21,22,1);
	add_edge(22,23,1);
	add_edge(23,1,1);
	add_edge(2,26,1);
	add_edge(2,25,1);

	add_edge(25,26,1);
	add_edge(6,28,1);
	add_edge(6,29,1);
	add_edge(10,31,1);
	add_edge(10,32,1);
	add_edge(31,32,1);
	add_edge(14,34,1);
	add_edge(14,35,1);
	add_edge(18,37,1);
	add_edge(18,38,1);
	add_edge(37,38,1);
	add_edge(22,40,1);
	add_edge(22,41,1);

	add_edge(24,25,1);
	add_edge(24,41,1);
	add_edge(27,26,1);
	add_edge(27,28,1);
	add_edge(30,29,1);
	add_edge(30,31,1);
	add_edge(33,32,1);
	add_edge(33,34,1);
	add_edge(36,35,1);
	add_edge(36,37,1);
	add_edge(39,38,1);
	add_edge(39,40,1);
	add_edge(24,42,1);

	add_edge(42,43,1);
	add_edge(43,27,1);
	add_edge(30,44,1);
	add_edge(44,45,1);
	add_edge(45,33,1);
	add_edge(36,46,1);
	add_edge(46,47,1);
	add_edge(47,39,1);
	add_edge(39,24,2);
	add_edge(27,30,2);
	add_edge(33,36,2);
}

void init_grid_of_nodes(){
	int i,j;
	for(i = 0; i< NUM_GRAPH_NODES; i++)
		for(j = 0; j < NUM_GRAPH_NODES; j++)
			grid_of_nodes[i][j] = 0;
	add_edges_to_graph();
}

#endif