#ifndef MENUA_H
#define MENUA_H
// Incluye los tipos personalizados como Player, EGOERA, etc.
#include "ourTypes.h"
#include <SDL.h>

SDL_Texture *loadTexture(const char *path, SDL_Renderer *renderer);
void kontrolenVentana(SDL_Renderer *renderer);
void KreditoenVentana(SDL_Renderer *renderer);
void ZabalduJolasarenPantaila(SDL_Window *window, SDL_Renderer *renderer);
void KontaktoaBotoiarenFuntzioa(SDL_Renderer *renderer);
void EzarpenakBotoiarenFuntzioa(SDL_Window *window, SDL_Renderer *renderer);
int PantailaPrintzipala(SDL_Window *window, SDL_Renderer *renderer);
int menua_kargatu(void);

#endif // GAME02_H