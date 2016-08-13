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

	return 0;
}

int Quit_Graphics()
{
	//Quit SDL
	SDL_DestroyWindow( gWindow );
	SDL_Quit();

	return 0;
}

Sprite spriteFromURI(char* URI, int x, int y, int width, int height,
	                 int center_x, int center_y){
	Sprite sprite = malloc(sizeof(struct sprite_struct));
	SDL_Surface* stmp = IMG_Load(URI);
	sprite->img = SDL_CreateTextureFromSurface(gRenderer, stmp);
	sprite->location.x = x;
	sprite->location.y = y;
	sprite->location.w = width;
	sprite->location.h = height;
	sprite->center.x = center_x;
	sprite->center.y = center_y;
	return sprite;
}

int chargement_images()
{
	//Clear screen
	SDL_RenderClear( gRenderer );
	wall = spriteFromURI("img/New Tiles/wall_full.png", 0, 0, 32, 32, 16, 16);
	wall_up = spriteFromURI("img/New Tiles/wall_up.png", 0, 0, 32, 32, 16, 16);
	wall_right = spriteFromURI("img/New Tiles/wall_right.png", 0, 0, 32, 32, 16, 16);
	wall_down = spriteFromURI("img/New Tiles/wall_down.png", 0, 0, 32, 32, 16, 16);
	wall_left = spriteFromURI("img/New Tiles/wall_left.png", 0, 0, 32, 32, 16, 16);
	wall_NW_angle = spriteFromURI("img/New Tiles/wall_NW_angle.png", 0, 0, 32, 32, 16, 16);
	wall_NW_corner = spriteFromURI("img/New Tiles/wall_NW_corner.png", 0, 0, 32, 32, 16, 16);
	wall_NE_angle = spriteFromURI("img/New Tiles/wall_NE_angle.png", 0, 0, 32, 32, 16, 16);
	wall_NE_corner = spriteFromURI("img/New Tiles/wall_NE_corner.png", 0, 0, 32, 32, 16, 16);
	wall_SE_angle = spriteFromURI("img/New Tiles/wall_SE_angle.png", 0, 0, 32, 32, 16, 16);
	wall_SE_corner = spriteFromURI("img/New Tiles/wall_SE_corner.png", 0, 0, 32, 32, 16, 16);
	wall_SW_angle = spriteFromURI("img/New Tiles/wall_SW_angle.png", 0, 0, 32, 32, 16, 16);
	wall_SW_corner = spriteFromURI("img/New Tiles/wall_SW_corner.png", 0, 0, 32, 32, 16, 16);
	therbe = spriteFromURI("img/Tiles/tile_11.png", 0, 0, 64, 64, 32, 32);
	tmonstre = spriteFromURI("img/Robot 1/robot1_machine.png", 0, 0, 49, 43, 25, 22);
	tperso = spriteFromURI("img/Survivor 1/survivor1_stand.png", 0, 0, 35, 43, 18, 22);
	tinterface = spriteFromURI("img/Interface.png", 0, 0, 200, 100, 100, 50);

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

int displaySprite(Sprite sprite, int x, int y) {
	SDL_Rect pos = sprite->location;
	pos.x = x;
	pos.y = y;
	return SDL_RenderCopy(gRenderer, sprite->img, &sprite->location, &pos );
}

int displaySpriteOnGrid(Sprite sprite, int x, int y) {
	SDL_Rect pos = sprite->location;
	pos.x = x*LARGEUR_CASE * zoom/256;
	pos.y = y*HAUTEUR_CASE * zoom/256;
	pos.w = pos.w * zoom/256;
	pos.h = pos.h * zoom/256;
	return SDL_RenderCopy(gRenderer, sprite->img, &sprite->location, &pos );
}

int displaySpriteOnGridWithOffset(Sprite sprite, int x, int y, int offx, int offy) {
	SDL_Rect pos = sprite->location;
	pos.x = (x*LARGEUR_CASE+offx) * zoom/256;
	pos.y = (y*HAUTEUR_CASE+offy) * zoom/256;
	pos.w = pos.w * zoom/256;
	pos.h = pos.h * zoom/256;
	return SDL_RenderCopy(gRenderer, sprite->img, &sprite->location, &pos );
}

int displayObjectSpriteOnGrid(Sprite sprite, int x, int y) {
	SDL_Rect pos = sprite->location;
	pos.x = (x*LARGEUR_CASE+LARGEUR_CASE/2-sprite->center.x) * zoom/256;
	pos.y = (y*HAUTEUR_CASE+HAUTEUR_CASE/2-sprite->center.y) * zoom/256;
	pos.w = pos.w * zoom/256;
	pos.h = pos.h * zoom/256;
	return SDL_RenderCopy(gRenderer, sprite->img, &sprite->location, &pos );
}

int displayObjectSpriteOnGridWithRotation(Sprite sprite, int x, int y, double angle) {
	SDL_Rect pos = sprite->location;
	SDL_Point center = sprite->center;
	pos.x = (x*LARGEUR_CASE+LARGEUR_CASE/2-sprite->center.x) * zoom/256;
	pos.y = (y*HAUTEUR_CASE+HAUTEUR_CASE/2-sprite->center.y) * zoom/256;
	pos.w = pos.w * zoom/256;
	pos.h = pos.h * zoom/256;
	center.x = center.x * zoom/256;
	center.y = center.y * zoom/256;
	return SDL_RenderCopyEx(gRenderer, sprite->img, &sprite->location, &pos,
	                        angle, &sprite->center, SDL_FLIP_NONE);
}

int display_image_with_rotation(int x, int y, int w, int h, int cx, int cy, double angle, SDL_Texture* img) {
	SDL_Rect pos;
	pos.x = x;
	pos.y = y;
	pos.w = w;
	pos.h = h;
	SDL_Point point;
	point.x = cx;
	point.y = cy;
	return SDL_RenderCopyEx(gRenderer, img,
					 NULL, &pos,
                     angle, &point,
                     SDL_FLIP_NONE);
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
