#include <stdlib.h>
#include "header.h"

struct map_graph_converter {
	size_t x;
	size_t y;
	size_t i;
	size_t value;
};

typedef struct map_graph_converter Nodes;
typedef struct map_graph_converter Edges;

int generateMaze(Game game);
