#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "lib/graphics.h"

#define VITESSE 4
#define MAP_SIZE 20
#define ROBOTS_NUMBER 5

typedef struct player_struct {
	int x;
	int y;
	int direction;
	int lifes;
	int papers;
	int keys;
} Player;

typedef struct robot_struct {
	int x;
	int y;
	int direction;
	int rotation_direction;
	int alive;
} Robot;

typedef struct game_struct {
	Player player;
	Robot robots[ROBOTS_NUMBER];
	int map[MAP_SIZE][MAP_SIZE];
	int quit_game;

}* Game;

Game init_game() {
	int i, j;
	Game game = malloc(sizeof(struct game_struct));
	srand(time(NULL));

	// map
	srand(time(NULL));
	for(i=0; i<MAP_SIZE; i++) {
		for(j=0; j<MAP_SIZE; j++) {
			game->map[i][j] = 0;
		}
	}

	for (j=1; j<=MAP_SIZE-2; j++) {
		game->map[j][1] = 1;
		game->map[j][MAP_SIZE-2] = 1;
	}
	for (j=1; j<=MAP_SIZE-2; j++) {
		game->map[1][j] = 1;
		game->map[MAP_SIZE-2][j] = 1;
	}
	for (i=0; i<10; i++) {
		// rand coord
		int x_origin = (rand()%(MAP_SIZE-2)) +1;
		int x_destination = (rand()%(MAP_SIZE-2)) +1;
		int y_origin = (rand()%(MAP_SIZE-2)) +1;
		int y_destination = (rand()%(MAP_SIZE-2)) +1;

		for (j=x_origin; j<=x_destination; j++) {
			game->map[j][y_origin] = 1;
			game->map[j][y_destination] = 1;
		}
		for (j=y_origin; j<=y_destination; j++) {
			game->map[x_origin][j] = 1;
			game->map[x_destination][j] = 1;
		}
	}

	// player
	game->player.x = 1;
	game->player.y = 1;
	game->player.lifes = 10;
	game->player.keys = 0;
	game->player.papers = 0;

	// robots
	for(i=0; i<ROBOTS_NUMBER; i++) {
		int x = 0;
		int y = 0;
		while (game->map[x][y] == 0) {
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
	if (game->map[x][y-1] == 1 && game->map[x-1][y] == 1) {
		afficher_image(x*LARGEUR_CASE * zoom/256, y*HAUTEUR_CASE * zoom/256,
			32*zoom/256, 32*zoom/256, wall_NW_corner);
	} else if (game->map[x][y-1] == 0 && game->map[x-1][y] == 1) {
		afficher_image(x*LARGEUR_CASE * zoom/256, y*HAUTEUR_CASE * zoom/256,
			32*zoom/256, 32*zoom/256, wall_left);
	} else if (game->map[x][y-1] == 1 && game->map[x-1][y] == 0) {
		afficher_image(x*LARGEUR_CASE * zoom/256, y*HAUTEUR_CASE * zoom/256,
			32*zoom/256, 32*zoom/256, wall_up);
	} else if (game->map[x][y-1] == 0 && game->map[x-1][y] == 0 && game->map[x-1][y-1] == 1) {
		afficher_image(x*LARGEUR_CASE * zoom/256, y*HAUTEUR_CASE * zoom/256,
			32*zoom/256, 32*zoom/256, wall_NW_angle);
	} else {
		afficher_image(x*LARGEUR_CASE * zoom/256, y*HAUTEUR_CASE * zoom/256,
			32*zoom/256, 32*zoom/256, wall);
	}

	// North-East
	if (game->map[x][y-1] == 1 && game->map[x+1][y] == 1) {
		afficher_image((x*LARGEUR_CASE+32) * zoom/256, y*HAUTEUR_CASE * zoom/256,
			32*zoom/256, 32*zoom/256, wall_NE_corner);
	} else if (game->map[x][y-1] == 0 && game->map[x+1][y] == 1) {
		afficher_image((x*LARGEUR_CASE+32) * zoom/256, y*HAUTEUR_CASE * zoom/256,
			32*zoom/256, 32*zoom/256, wall_right);
	} else if (game->map[x][y-1] == 1 && game->map[x+1][y] == 0) {
		afficher_image((x*LARGEUR_CASE+32) * zoom/256, y*HAUTEUR_CASE * zoom/256,
			32*zoom/256, 32*zoom/256, wall_up);
	} else if (game->map[x][y-1] == 0 && game->map[x+1][y] == 0 && game->map[x+1][y-1] == 1) {
		afficher_image((x*LARGEUR_CASE+32) * zoom/256, y*HAUTEUR_CASE * zoom/256,
			32*zoom/256, 32*zoom/256, wall_NE_angle);
	} else {
		afficher_image((x*LARGEUR_CASE+32) * zoom/256, y*HAUTEUR_CASE * zoom/256,
			32*zoom/256, 32*zoom/256, wall);
	}

	// South_East
	if (game->map[x][y+1] == 1 && game->map[x+1][y] == 1) {
		afficher_image((x*LARGEUR_CASE+32) * zoom/256, (y*HAUTEUR_CASE+32) * zoom/256,
			32*zoom/256, 32*zoom/256, wall_SE_corner);
	} else if (game->map[x][y+1] == 0 && game->map[x+1][y] == 1) {
		afficher_image((x*LARGEUR_CASE+32) * zoom/256, (y*HAUTEUR_CASE+32) * zoom/256,
			32*zoom/256, 32*zoom/256, wall_right);
	} else if (game->map[x][y+1] == 1 && game->map[x+1][y] == 0) {
		afficher_image((x*LARGEUR_CASE+32) * zoom/256, (y*HAUTEUR_CASE+32) * zoom/256,
			32*zoom/256, 32*zoom/256, wall_down);
	} else if (game->map[x][y+1] == 0 && game->map[x+1][y] == 0 && game->map[x+1][y+1] == 1) {
		afficher_image((x*LARGEUR_CASE+32) * zoom/256, (y*HAUTEUR_CASE+32) * zoom/256,
			32*zoom/256, 32*zoom/256, wall_SE_angle);
	} else {
		afficher_image((x*LARGEUR_CASE+32) * zoom/256, (y*HAUTEUR_CASE+32) * zoom/256,
			32*zoom/256, 32*zoom/256, wall);
	}

	// South_West
	if (game->map[x][y+1] == 1 && game->map[x-1][y] == 1) {
		afficher_image(x*LARGEUR_CASE * zoom/256, (y*HAUTEUR_CASE+32) * zoom/256,
			32*zoom/256, 32*zoom/256, wall_SW_corner);
	} else if (game->map[x][y+1] == 0 && game->map[x-1][y] == 1) {
		afficher_image(x*LARGEUR_CASE * zoom/256, (y*HAUTEUR_CASE+32) * zoom/256,
			32*zoom/256, 32*zoom/256, wall_left);
	} else if (game->map[x][y+1] == 1 && game->map[x-1][y] == 0) {
		afficher_image(x*LARGEUR_CASE * zoom/256, (y*HAUTEUR_CASE+32) * zoom/256,
			32*zoom/256, 32*zoom/256, wall_down);
	} else if (game->map[x][y+1] == 0 && game->map[x-1][y] == 0 && game->map[x-1][y+1] == 1) {
		afficher_image(x*LARGEUR_CASE * zoom/256, (y*HAUTEUR_CASE+32) * zoom/256,
			32*zoom/256, 32*zoom/256, wall_SW_angle);
	} else {
		afficher_image(x*LARGEUR_CASE * zoom/256, (y*HAUTEUR_CASE+32) * zoom/256,
			32*zoom/256, 32*zoom/256, wall);
	}
}

int display(Game game) {
	int i, j;

	// sol
	for(i=0; i<MAP_SIZE; i++) {
		for(j=0; j<MAP_SIZE; j++) {
			afficher_case(i, j, therbe);
			if (game->map[i][j] == 0) {
				display_wall(game, i, j);
			}
		}
	}

	// élements & objets
	// display player
	afficher_image((game->player.x*LARGEUR_CASE + (64-35)/2) *zoom/256,
	              (game->player.y*HAUTEUR_CASE + (64-45)/2) *zoom/256,
	              35*zoom/256, 45*zoom/256, tperso);

	//display robots
	for(i=0; i<ROBOTS_NUMBER; i++) {
		afficher_image((game->robots[i].x*LARGEUR_CASE + (64-49)/2) *zoom/256, (game->robots[i].y*HAUTEUR_CASE + (64-43)/2) *zoom/256, 49*zoom/256, 43*zoom/256, tmonstre);
	}


	// Interface
	char str [2];
	afficher_image(10, 10, 200, 100, tinterface);
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
	int player_moved = 0;

	Player next_player = game->player;

	while(SDL_PollEvent(&event)) {
		if(event.key.type == SDL_KEYDOWN) {
			// Gestion des évènements
			if (event.key.keysym.sym == SDLK_UP) {
					next_player.y--;
					player_moved = 1;
			} else if (event.key.keysym.sym == SDLK_RIGHT) {
					next_player.x++;
					player_moved = 1;
			} else if (event.key.keysym.sym == SDLK_DOWN) {
					next_player.y++;
					player_moved = 1;
			} else if (event.key.keysym.sym == SDLK_LEFT) {
					next_player.x--;
					player_moved = 1;
			} else if (event.key.keysym.sym == SDLK_ESCAPE) {
				game->quit_game = 1;
				player_moved = 1;
			}
		}

		if(event.wheel.type == SDL_MOUSEWHEEL) {
			zoom += event.wheel.y*8;
			if(zoom > 256)
				zoom = 256;
			if(zoom < 128)
				zoom = 128;
		}

		if(event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
			winx = event.window.data1;
			winy = event.window.data2;
		}
	}

	if (player_moved == 0) {
		return 0;
	}

	// collisions
	if (game->map[next_player.x][next_player.y] != 0) {
		game->player.x = next_player.x;
		game->player.y = next_player.y;
	}

	// robots mouvement
	for (size_t i = 0; i < ROBOTS_NUMBER; i++) {
		Robot robot = game->robots[i];
		if (robot.direction == 0) {
			if (game->map[robot.x][robot.y-1] != 0) {
				robot.y--;
			} else {
				robot.direction = (robot.direction + robot.rotation_direction)%4;
			}
		} else if (robot.direction == 1) {
			if (game->map[robot.x+1][robot.y] != 0) {
				robot.x++;
			} else {
				robot.direction = (robot.direction + robot.rotation_direction)%4;
			}
		} else if (robot.direction == 2) {
			if (game->map[robot.x][robot.y+1] != 0) {
				robot.y++;
			} else {
				robot.direction = (robot.direction + robot.rotation_direction)%4;
			}
		} else {
			if (game->map[robot.x-1][robot.y] != 0) {
				robot.x--;
			} else {
				robot.direction = (robot.direction + robot.rotation_direction)%4;
			}
		}
		game->robots[i] = robot;
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
