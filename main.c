#include <stdio.h>
#include <math.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "lib/graphics.h"

#define VITESSE 4
#define MAP_SIZE 20
#define ROBOTS_NUMBER 5

typedef struct player_struct
{
	int x;
	int y;
	int direction;
	int lifes;
	int papers;
	int keys;
} Player;

typedef struct robot_struct
{
	int x;
	int y;
	int direction;
	int alive
} Robot;

typedef struct game_struct
{
	Player player;
	Robot robots[ROBOTS_NUMBER];
	int map[MAP_SIZE][MAP_SIZE];
	int quit_game;
	
}* Game;

int init_game()
{
	int i, j, obj;
	Game game = malloc(sizeof(struct game_struct));
	srand(time(NULL));

	// map
	for(i=0;i<MAP_SIZE;i++)
	{
		for(j=0;j<MAP_SIZE;j++)
		{
			game->map[i][j]=1;
		}
	}
	
	// player
	game->player.x = 1;
	game->player.y = 1;
	game->player.lifes = 10;
	game->player.keys = 0;
	game->player.papers = 0;
	
	// robots
	for(i=0; i<ROBOTS_NUMBER; i++){
		game->robots[i].x = i+2;
		game->robots[i].y = i+2;
	}
	
	// continue
	game->quit_game = 0;
	
	return game;
}

int display(Game game)
{
	int i, j;

	// sol
	for(i=0; i<MAP_SIZE; i++){
		for(j=0; j<MAP_SIZE; j++){
			switch(game->map[i][j]){
			case 1:
				afficher_case(i, j, therbe);
			break;
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

	while(SDL_PollEvent(&event)) {
		if(event.key.type == SDL_KEYDOWN) {
			// Gestion des évènements
			if (event.key.keysym.sym == SDLK_UP) {
					game->player.y--;
			} else if (event.key.keysym.sym == SDLK_RIGHT) {
					game->player.x++;
			} else if (event.key.keysym.sym == SDLK_DOWN) {
					game->player.y++;
			} else if (event.key.keysym.sym == SDLK_LEFT) {
					game->player.x--;
			} else if (event.key.keysym.sym == SDLK_ESCAPE) {
				game->quit_game = 1;
			}
		}

		if(event.wheel.type == SDL_MOUSEWHEEL)
		{
			zoom += event.wheel.y;
			if(zoom > 256)
				zoom = 256;
			if(zoom < 128)
				zoom = 128;
		}

		if(event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
		{
			puts("Resize");
			winx = event.window.data1;
			winy = event.window.data2;
		}
	}
	return 0;
}

/* Main */
int main() {
	Game game;
	SDL_Event event;

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
