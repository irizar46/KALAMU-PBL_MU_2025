#ifndef GAME02_H
#define GAME02_H

#include "mapa.h" // Incluye los tipos personalizados como Player, EGOERA, etc.
#include "ourTypes.h"
#define MAX_PLATAFORMA 24
#define PROTAGELDIK 3

// Declaración de las funciones utilizadas en game02.c

EGOERA jokatu(void); // Función para jugar el juego, devuelve el estado final del juego
void prozesatuEbentuak(SDL_Event *ebentu, Player *jugador, EGOERA *egoera, int *irudia, int *hasiera, int *amaiera,
                       int *irudia_bukaera, int *bukatua);

void eguneratuJugador(Player *jugador, Plataforma plataformas[MAX_IMG], int numPlataformas, Uint32 deltaTime,
                      int *offsetY, Erlazioa *erlazioa, int *amaiera);
void jokoaBukatu(Player *jugador, int backgroundId);
void cargarMapa(int mapa[FILAS][COLUMNAS], Plataforma plataforma[MAX_IMG], Mapas *todosLosMapas,
                TodasLasPlataformas *todasLasPlataformas);
void actualizarYdibujarMapa(Mapas *todosLosMapas, TodasLasPlataformas *todasLasPlataformas, Erlazioa *erlazioa,
                            int *offsetY, int plataformaIds[MAX_PLATAFORMA]);
int inicializarPlataformas(int mapa[FILAS][COLUMNAS], Plataforma plataforma[MAX_IMG]);
int background(int offsetY, int tira1id, int tira2id, int tira3id, int tira4id, int tira5id, int tira6id);
void plat_back_karga(int plataformaIds[MAX_PLATAFORMA], Player *jugador);
int hayPlataformaDebajo(Player *jugador, Plataforma plataformas[], int numPlataformas);
void pertsonaiaAnimazioa(Player *jugador, int geldik_ezk[PROTAGELDIK], int geldik_esk[PROTAGELDIK], int currentTime,
                         int *lastFrameTime, int *currentFrame, int *lastIdleFrameTime, int *idleFrame);

#endif
