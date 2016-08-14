#include "maze.h"
#include <stdlib.h>
#include <stdio.h>

int generateMaze(Game game) {
	// place nodes
	puts("place nodes");
	int graph[MAP_SIZE][MAP_SIZE];
	for(size_t i=0; i<MAP_SIZE; i++) {
		for(size_t j=0; j<MAP_SIZE; j++) {
			game->map[i][j] = i%2 * j%2;
			//game->map[i][j] = 0;
			graph[i][j] = -1;
		}
	}

	// create sets
	puts("create sets");
	Nodes sets[SETS_NUMBER];
	for (size_t i = 0; i < SETS_NUMBER; i++) {
		sets[i].i = i;
		sets[i].value = 1;
		sets[i].x = (i%SETS_ROW)*2+1;
		sets[i].y = (i/SETS_ROW)*2+1;
		graph[sets[i].x][sets[i].y] = i;
		//printf("%2zi: (%2zi, %2zi)\n", sets[i].i, sets[i].x, sets[i].y);
	}

	// list edges
	puts("create edges");
	Edges edges[EDGES_NUMBER];
	for (size_t i = 0; i < EDGES_NUMBER; i++) {
		edges[i].i = i;
		edges[i].value = 0;
		if (i%EDGES_DOUBLE_ROW < EDGES_DOUBLE_ROW/2) {
			edges[i].x = (i%EDGES_DOUBLE_ROW)*2 + 2;
			edges[i].y = (i/EDGES_DOUBLE_ROW)*2 + 1;
		} else {
			edges[i].x = (i%EDGES_DOUBLE_ROW)*2 - (EDGES_DOUBLE_ROW-2);
			edges[i].y = (i/EDGES_DOUBLE_ROW)*2 + 2;
		}
		//graph[edges[i].x][edges[i].y] = -i-1;
		//printf("%2zi: (%2zi, %2zi)\n", walls[i].i, walls[i].x, walls[i].y);
	}

	// randomize walls
	puts("randomize walls");
	for (size_t i = 0; i < EDGES_NUMBER; i++) {
		size_t j = rand()%((EDGES_NUMBER)-i)+i;
		int tmp;
		tmp = edges[i].x;
		edges[i].x = edges[j].x;
		edges[j].x = tmp;
		tmp = edges[i].y;
		edges[i].y = edges[j].y;
		edges[j].y = tmp;
	}

	// select connections
	puts("connect maze");
	int sets_left = SETS_NUMBER;
	for (size_t i = 0; sets_left > 1; i++) {
		size_t wall_id = i;
		size_t x = edges[wall_id].x;
		size_t y = edges[wall_id].y;
		if (edges[wall_id].y%2 == 1) {
			/*printf("%2zi: (%2zi, %2zi):%3zi != %2zi: (%2zi, %2zi):%3zi\n",
				   graph[x-1][y], sets[-graph[x-1][y]-1].x, sets[-graph[x-1][y]-1].y, sets[-graph[x-1][y]-1].i,
				   graph[x+1][y], sets[-graph[x+1][y]-1].x, sets[-graph[x+1][y]-1].y, sets[-graph[x+1][y]-1].i);*/
			if (sets[graph[x-1][y]].i != sets[graph[x+1][y]].i) {
				// horizontal
				edges[wall_id].value = 1;
				game->map[edges[wall_id].x][edges[wall_id].y] = 1;
				int left_set = sets[graph[x-1][y]].i;
				int right_set = sets[graph[x+1][y]].i;
				for (size_t j = 0; j < SETS_NUMBER; j++) {
					if (sets[j].i == right_set) {
						sets[j].i = left_set;
					}
				}

				sets_left--;
			}
		} else {
			// vertical
			/*printf("%2zi: (%2zi, %2zi):%3zi != %2zi: (%2zi, %2zi):%3zi\n",
				   graph[x][y-1], sets[-graph[x][y-1]-1].x, sets[-graph[x][y-1]-1].y, sets[-graph[x][y-1]-1].i,
				   graph[x][y+1], sets[-graph[x][y+1]-1].x, sets[-graph[x][y+1]-1].y, sets[-graph[x][y+1]-1].i);*/
			if (sets[graph[x][y-1]].i != sets[graph[x][y+1]].i) {
				// horizontal
				edges[wall_id].value = 1;
				game->map[edges[wall_id].x][edges[wall_id].y] = 1;
				int left_set = sets[graph[x][y-1]].i;
				int right_set = sets[graph[x][y+1]].i;
				for (size_t j = 0; j < SETS_NUMBER; j++) {
					if (sets[j].i == right_set) {
						sets[j].i = left_set;
					}
				}
				sets_left--;
			}
		}
	}

	// create map
	puts("create map");
	// nodes
	for (size_t i = 0; i < SETS_NUMBER; i++) {
		game->map[sets[i].x][sets[i].y] = sets[i].value;
	}
	// edges
	for (size_t i = 0; i < EDGES_NUMBER; i++) {
		game->map[edges[i].x][edges[i].y] = edges[i].value;
	}

	return 0;
}
