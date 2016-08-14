#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define LARGEUR_CASE 64
#define HAUTEUR_CASE 64
#define ZOOM_DEFAULT 256

typedef struct sprite_struct {
	SDL_Texture* img;
	SDL_Rect location;
	SDL_Point center;
}* Sprite;

/* loading functions */
Sprite spriteFromURI(char* URI, int x, int y, int width, int height,
	                 int center_x, int center_y);
int displaySprite(Sprite sprite, int x, int y);
int displaySpriteOnGrid(Sprite sprite, int x, int y);
int displaySpriteOnGridWithOffset(Sprite sprite, int x, int y, int offx, int offy);
int displayObjectSpriteOnGrid(Sprite sprite, int x, int y);
int displayObjectSpriteOnGridWithRotation(Sprite sprite, int x, int y, double angle);

/* Fonctions SDL */
int Init_Graphics();
int Quit_Graphics();
int chargement_images();
int afficher_texte(int x, int y, const char* text);
int afficher_case(int x, int y, SDL_Texture* img);
int afficher_image(int x, int y, int w, int h, SDL_Texture* img);
int maj_ecran();
//The window we'll be rendering to
SDL_Window* gWindow;
//The surface contained by the window
SDL_Renderer* gRenderer;
// Les images à afficher
Sprite wall;
Sprite wall_up;
Sprite wall_right;
Sprite wall_down;
Sprite wall_left;
Sprite wall_NW_angle;
Sprite wall_NW_corner;
Sprite wall_NE_angle;
Sprite wall_NE_corner;
Sprite wall_SE_angle;
Sprite wall_SE_corner;
Sprite wall_SW_angle;
Sprite wall_SW_corner;
Sprite therbe;
Sprite tmonstre;
Sprite tperso;
Sprite tinterface;
// Le timestamp pour limiter les ips
unsigned int ticks;
// La police à afficher
TTF_Font *police;
// Le zoom
float zoom;
// Largeur et hauteur de fenetre
int winx, winy;
// scroll
int scrollx, scrolly;

#endif
