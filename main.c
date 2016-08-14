#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "lib/graphics.h"
#include "header.h"
#include "maze.h"

int is_wall(Game game, int x, int y) {
	return game->map[x][y] == 0;
}

Game init_game() {
	int i;
	Game game = malloc(sizeof(struct game_struct));
	srand(time(NULL));

	// map
	generateMaze(game);

	// player
	game->player.x = 1;
	game->player.y = 1;
	game->player.direction = 2;
	game->player.lifes = 10;
	game->player.keys = 0;
	game->player.papers = 0;

	// robots
	for(i=0; i<ROBOTS_NUMBER; i++) {
		int x = 0;
		int y = 0;
		while (is_wall(game, x, y)) {
			x = (rand()%(MAP_SIZE-2)) +1;
			y = (rand()%(MAP_SIZE-2)) +1;
		}
		game->robots[i].x = x;
		game->robots[i].y = y;

		game->robots[i].direction = rand()%4;
		game->robots[i].rotation_direction = -1 + (2*(rand()%2));
		game->robots[i].alive = 1;
	}

	// continue
	game->quit_game = 0;

	return game;
}

void display_wall(Game game, int x, int y) {
	// North-West
	if (x == 0 || y == 0) {
		displaySpriteOnGridWithOffset(wall, x, y, 0, 0);
	} else if (game->map[x][y-1] == 1 && game->map[x-1][y] == 1) {
		displaySpriteOnGridWithOffset(wall_NW_corner, x, y, 0, 0);
	} else if (game->map[x][y-1] == 0 && game->map[x-1][y] == 1) {
		displaySpriteOnGridWithOffset(wall_left, x, y, 0, 0);
	} else if (game->map[x][y-1] == 1 && game->map[x-1][y] == 0) {
		displaySpriteOnGridWithOffset(wall_up, x, y, 0, 0);
	} else if (game->map[x][y-1] == 0 && game->map[x-1][y] == 0 && game->map[x-1][y-1] == 1) {
		displaySpriteOnGridWithOffset(wall_NW_angle, x, y, 0, 0);
	} else {
		displaySpriteOnGridWithOffset(wall, x, y, 0, 0);
	}

	// North-East
	if (x == MAP_SIZE-1 || y == 0) {
		displaySpriteOnGridWithOffset(wall, x, y, 32, 0);
	} else if (game->map[x][y-1] == 1 && game->map[x+1][y] == 1) {
		displaySpriteOnGridWithOffset(wall_NE_corner, x, y, 32, 0);
	} else if (game->map[x][y-1] == 0 && game->map[x+1][y] == 1) {
		displaySpriteOnGridWithOffset(wall_right, x, y, 32, 0);
	} else if (game->map[x][y-1] == 1 && game->map[x+1][y] == 0) {
		displaySpriteOnGridWithOffset(wall_up, x, y, 32, 0);
	} else if (game->map[x][y-1] == 0 && game->map[x+1][y] == 0 && game->map[x+1][y-1] == 1) {
		displaySpriteOnGridWithOffset(wall_NE_angle, x, y, 32, 0);
	} else {
		displaySpriteOnGridWithOffset(wall, x, y, 32, 0);
	}

	// South_East
	if (x == MAP_SIZE-1 || y == MAP_SIZE-1) {
		displaySpriteOnGridWithOffset(wall, x, y, 32, 32);
	} else if (game->map[x][y+1] == 1 && game->map[x+1][y] == 1) {
		displaySpriteOnGridWithOffset(wall_SE_corner, x, y, 32, 32);
	} else if (game->map[x][y+1] == 0 && game->map[x+1][y] == 1) {
		displaySpriteOnGridWithOffset(wall_right, x, y, 32, 32);
	} else if (game->map[x][y+1] == 1 && game->map[x+1][y] == 0) {
		displaySpriteOnGridWithOffset(wall_down, x, y, 32, 32);
	} else if (game->map[x][y+1] == 0 && game->map[x+1][y] == 0 && game->map[x+1][y+1] == 1) {
		displaySpriteOnGridWithOffset(wall_SE_angle, x, y, 32, 32);
	} else {
		displaySpriteOnGridWithOffset(wall, x, y, 32, 32);
	}

	// South_West
	if (x == 0 || y == MAP_SIZE-1) {
		displaySpriteOnGridWithOffset(wall, x, y, 0, 32);
	} else if (game->map[x][y+1] == 1 && game->map[x-1][y] == 1) {
		displaySpriteOnGridWithOffset(wall_SW_corner, x, y, 0, 32);
	} else if (game->map[x][y+1] == 0 && game->map[x-1][y] == 1) {
		displaySpriteOnGridWithOffset(wall_left, x, y, 0, 32);
	} else if (game->map[x][y+1] == 1 && game->map[x-1][y] == 0) {
		displaySpriteOnGridWithOffset(wall_down, x, y, 0, 32);
	} else if (game->map[x][y+1] == 0 && game->map[x-1][y] == 0 && game->map[x-1][y+1] == 1) {
		displaySpriteOnGridWithOffset(wall_SW_angle, x, y, 0, 32);
	} else {
		displaySpriteOnGridWithOffset(wall, x, y, 0, 32);
	}
}

int display(Game game) {
	int i, j;

	// sol
	for(i=0; i<MAP_SIZE; i++) {
		for(j=0; j<MAP_SIZE; j++) {
			displaySpriteOnGrid(therbe, i, j);
			if (game->map[i][j] == 0) {
				display_wall(game, i, j);
			}
		}
	}

	// élements & objets
	// display player
	displayObjectSpriteOnGridWithRotation(tperso,
		game->player.x, game->player.y,
		90*((game->player.direction+3)%4));

	//display robots
	for(i=0; i<ROBOTS_NUMBER; i++) {
		displayObjectSpriteOnGridWithRotation(tmonstre,
			game->robots[i].x, game->robots[i].y,
			90*((game->robots[i].direction+3)%4));
	}


	// Interface
	char str [2];
	displaySprite(tinterface, 10, 10);
	afficher_texte(25, 15, "Vie:");
	sprintf(str, "%d", game->player.lifes);
	afficher_texte(125, 15, str);
	afficher_texte(25, 45, "Pièces:");
	sprintf(str, "%d", game->player.papers);
	afficher_texte(125, 45, str);
	afficher_texte(25, 75, "Clés:");
	sprintf(str, "%d", game->player.keys);
	afficher_texte(125, 75, str);

	maj_ecran();
	return 0;
}

int game_state(Game game) {
	SDL_Event event;

	while(SDL_PollEvent(&event)) {
		int player_moved = 0;
		Player next_player = game->player;
		int new_scrollx = scrollx;
		int new_scrolly = scrolly;
		if(event.key.type == SDL_KEYDOWN) {
			// Gestion des évènements
			if (event.key.keysym.sym == SDLK_UP) {
					next_player.y--;
					next_player.direction = 0;
					player_moved = 1;
					new_scrolly+=64;
			} else if (event.key.keysym.sym == SDLK_RIGHT) {
					next_player.x++;
					next_player.direction = 1;
					player_moved = 1;
					new_scrollx-=64;
			} else if (event.key.keysym.sym == SDLK_DOWN) {
					next_player.y++;
					next_player.direction = 2;
					player_moved = 1;
					new_scrolly-=64;
			} else if (event.key.keysym.sym == SDLK_LEFT) {
					next_player.x--;
					next_player.direction = 3;
					player_moved = 1;
					new_scrollx+=64;
			} else if (event.key.keysym.sym == SDLK_ESCAPE) {
				game->quit_game = 1;
				player_moved = 1;
			}
		}

		/*if(event.wheel.type == SDL_MOUSEWHEEL) {
			zoom += event.wheel.y*8;
			if(zoom > 512)
				zoom = 512;
			if(zoom < 8)
				zoom = 8;
		}*/

		if(event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
			winx = event.window.data1;
			winy = event.window.data2;
		}

		if (player_moved == 1) {
			// collisions
			if (!is_wall(game, next_player.x, next_player.y)) {
				game->player = next_player;
				scrollx = new_scrollx;
				scrolly = new_scrolly;
			}

			// robots mouvement
			for (size_t i = 0; i < ROBOTS_NUMBER; i++) {
				Robot robot = game->robots[i];
				if (rand()%(MAP_SIZE/2) == 0) {
					robot.direction = (robot.direction + robot.rotation_direction+4)%4;
				} else  if (robot.direction == 0) {
					if (!is_wall(game, robot.x, robot.y-1)) {
						robot.y--;
					} else {
						robot.direction = (robot.direction + robot.rotation_direction+4)%4;
					}
				} else if (robot.direction == 1) {
					if (!is_wall(game, robot.x+1, robot.y)) {
						robot.x++;
					} else {
						robot.direction = (robot.direction + robot.rotation_direction+4)%4;
					}
				} else if (robot.direction == 2) {
					if (!is_wall(game, robot.x, robot.y+1)) {
						robot.y++;
					} else {
						robot.direction = (robot.direction + robot.rotation_direction+4)%4;
					}
				} else {
					if (!is_wall(game, robot.x-1, robot.y)) {
						robot.x--;
					} else {
						robot.direction = (robot.direction + robot.rotation_direction+4)%4;
					}
				}
				game->robots[i] = robot;
			}
		}
	}

	return 0;
}

/* Main */
int main() {
	Game game;

	//Init SDL2
	Init_Graphics();

	//Init Jeu
	game = init_game();

	// Jeu
	do {
		display(game);
		game_state(game);
	} while(!game->quit_game);

	//Quit SDL
	SDL_DestroyWindow( gWindow );
	SDL_Quit();

	return 0;
}
