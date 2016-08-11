#include <stdio.h>
#include <math.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "graphics.h"

int Init_Graphics()
{
	SDL_Init( SDL_INIT_VIDEO);
	gWindow = SDL_CreateWindow( "Laby", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
	TTF_Init();
	chargement_images();
	zoom = 256;
	winx = SCREEN_WIDTH;
	winy = SCREEN_HEIGHT;
}

int Quit_Graphics()
{
	//Quit SDL
	SDL_DestroyWindow( gWindow );
	SDL_Quit();
}

int chargement_images()
{
	//Clear screen
	SDL_RenderClear( gRenderer );
	SDL_Surface* stmp = NULL;
	stmp = IMG_Load("img/Tiles/tile_342.png");
	wall = SDL_CreateTextureFromSurface( gRenderer, stmp );
	stmp = IMG_Load("img/Tiles/tile_11.png");
	therbe = SDL_CreateTextureFromSurface( gRenderer, stmp );
	stmp = IMG_Load("img/Robot 1/robot1_machine.png");
	tmonstre = SDL_CreateTextureFromSurface( gRenderer, stmp );
	stmp = IMG_Load("img/Survivor 1/survivor1_stand.png");
	tperso = SDL_CreateTextureFromSurface( gRenderer, stmp );
	stmp = IMG_Load("img/Interface.png");
	tinterface = SDL_CreateTextureFromSurface( gRenderer, stmp );

	// Font
	police = TTF_OpenFont("Gabriela.ttf", 25);
	return 0;
}

int afficher_texte(int x, int y, const char* text)
{
	SDL_Color color;
	color.r = 0;
	color.g = 0;
	color.b = 0;
	color.a = 255;
	SDL_Texture* img = SDL_CreateTextureFromSurface( gRenderer, TTF_RenderUTF8_Blended(police, text, color) );
	SDL_Rect pos;
	pos.x = x;
	pos.y = y;
	TTF_SizeUTF8(police, text, &pos.w, &pos.h);
	//Render texture to screen
	SDL_RenderCopy( gRenderer, img, NULL, &pos );
	return 0;
}

int afficher_case(int x, int y, SDL_Texture* img)
{
	afficher_image(x*LARGEUR_CASE * zoom/256, y*HAUTEUR_CASE * zoom/256, LARGEUR_CASE*zoom/256, HAUTEUR_CASE*zoom/256, img);
	return 0;
}

int afficher_image(int x, int y, int w, int h, SDL_Texture* img)
{
	SDL_Rect pos;
	pos.x = x;
	pos.y = y;
	pos.w = w;
	pos.h = h;
	//Render texture to screen
	SDL_RenderCopy( gRenderer, img, NULL, &pos );
	return 0;
}

int maj_ecran()
{
	//Update screen
	SDL_RenderPresent( gRenderer );
	SDL_RenderClear( gRenderer );
	if((SDL_GetTicks() - ticks) < (1000/30))
		SDL_Delay((1000/30) - (SDL_GetTicks() - ticks));
	ticks = SDL_GetTicks();
	return 0;
}