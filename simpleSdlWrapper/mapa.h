// map.h
#ifndef MAPA_H
#define MAPA_H

#define FILAS 24
#define COLUMNAS 24
#define TILE_SIZE 45
#define MAX_IMG 100

#include "lib/game02.h"
#include "ourTypes.h"

extern int mapa[FILAS][COLUMNAS]; // Declaración externa del mapa

// Funciones para el manejo del mapa
void cargarMapa(int mapa[FILAS][COLUMNAS], Plataforma plataformas[MAX_IMG], Mapas *todosLosMapas,
                TodasLasPlataformas *todasLasPlataformas);
void dibujarMapa(int mapa[FILAS][COLUMNAS], int *plataformaIds);
void cambiarPantalla(int nuevoMapa[FILAS][COLUMNAS], int mapa[FILAS][COLUMNAS]);
#endif // MAPA_H