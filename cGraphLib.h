struct node{
	int vertex;
	struct node* next;

};

struct adjList{
	struct note *sNode

};


struct graph{
	int nVertices;
	struct adjList* array;

};

struct graph* createGraph(int nVertices){
	struct graph* graph = (struct graph*) malloc(sizeof(struct graph));
	graph->nVertices = nVertices;

	graph->array = (struct adjList*) malloc(nVertices * sizeof(struct adjList));

	int i;
	for (i=0; i < nVertices; ++i){
		graph->array[i].head = NULL;
	}
	return graph;

};



