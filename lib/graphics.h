#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define LARGEUR_CASE 64
#define HAUTEUR_CASE 64

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
SDL_Texture* wall;
SDL_Texture* wall_up;
SDL_Texture* wall_right;
SDL_Texture* wall_down;
SDL_Texture* wall_left;
SDL_Texture* wall_NW_angle;
SDL_Texture* wall_NW_corner;
SDL_Texture* wall_NE_angle;
SDL_Texture* wall_NE_corner;
SDL_Texture* wall_SE_angle;
SDL_Texture* wall_SE_corner;
SDL_Texture* wall_SW_angle;
SDL_Texture* wall_SW_corner;
SDL_Texture* therbe;
SDL_Texture* tmonstre;
SDL_Texture* tperso;
SDL_Texture* tinterface;
// Le timestamp pour limiter les ips
unsigned int ticks;
// La police à afficher
TTF_Font *police;
// Le zoom
int zoom;
// Largeur et hauteur de fenetre
int winx, winy;

#endif
