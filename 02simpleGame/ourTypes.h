#ifndef OURTYPES_H
#define OURTYPES_H

#define MAX_IMG 100
#include "ebentoak.h"
#include "imagen.h"
#include <stdbool.h>

#include <SDL.h> // Incluimos SDL si las estructuras usan tipos como SDL_Rect

// Definición de la estructura JOKO_ELEMENTUA
typedef struct
{
    SDL_Rect pos; // Posición de la imagen (x, y, ancho, alto)
    int id;       // ID de la imagen del jugador
} JOKO_ELEMENTUA;

// Definición de la enumeración EGOERA
typedef enum
{
    JOLASTEN,
    JOKUA_AMAITU // Perdido
} EGOERA;

typedef struct
{
    int geldirik_eskuin[3];
    int geldirik_ezker[3];
    int eskuin[8];
    int ezker[8];
    int x, y;             // Posición del jugador en el eje X y Y
    int velY;             // Velocidad vertical (para la caída y el salto)
    int velX;             // Velocidad horizontal
    int id;               // ID de la imagen del jugador
    int direccionSalto;   // Dirección del salto: -1 para izquierda, 1 para derecha, 0 para ninguno
    int enSuelo;          // 1 si está en el suelo, 0 si está en el aire
    int direccionJugador; // ID de la imagen del jugador
    int cargandoSalto;
    int enMovimiento;        // 1 si está cargando el salto, 0 si no
    Uint32 inicioCarga;      // Tiempo cuando se empezó a cargar el salto
    Uint32 tiempoCargaSalto; // Tiempo de carga acumulado
} Player;

typedef struct
{
    SDL_Texture *texture; // La textura cargada
    SDL_Rect dest;        // Rectángulo de destino donde se dibujará la imagen
} Irudia;

typedef struct
{
    int x;
    int y;
} Plataforma;

typedef struct
{
    Plataforma plataformas[5][MAX_IMG];
    int zenb[5];
} TodasLasPlataformas;

// Estructura para almacenar todos los mapas
typedef struct
{
    int mapas[5][FILAS][COLUMNAS];
} Mapas;

typedef struct
{
    Plataforma plataformas[MAX_IMG];
    int zenb;
} Erlazioa;

typedef struct
{
    SDL_Renderer *renderer;
    SDL_Window *window;
} App;
// struct hau actualizarYdibujarMapako datuak eguneratuJugadorea edo kolisioak erabiltzen diren funtziora
// datuak pasatzeko erabiltzen da, bakoitzeko posizioei kasu gutxiago egiteko (offseteko posizioa mantendu
// beharkolukete)
#endif
