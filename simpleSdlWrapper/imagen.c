#include "imagen.h"
#include "graphics.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

int irudiarenPosizioaAurkitu(int id);

typedef struct Img
{
    int id;
    SDL_Surface *imagen;
    SDL_Texture *texture;
    SDL_Rect dest;
} IMG;

IMG irudiak[MAX_IMG];
int irudiKop = 0;
int id = 0;

int irudiaKargatu(char *fileName)
{
    int colorkey;
    SDL_Surface *surface;
    SDL_Renderer *gRenderer = getRenderer();

    if (irudiKop < MAX_IMG)
    {
        surface = IMG_Load(fileName);
        if (surface == NULL)
        {
            fprintf(stderr, "Couldn't load %s: %s\n", fileName, SDL_GetError());
            return -1;
        }
        else
        {
            colorkey = SDL_MapRGB(surface->format, 255, 0, 255);
            SDL_SetColorKey(surface, SDL_TRUE, colorkey);
            irudiak[irudiKop].texture = SDL_CreateTextureFromSurface(gRenderer, surface);
            irudiak[irudiKop].dest.x = irudiak[irudiKop].dest.y = 0;
            irudiak[irudiKop].dest.w = surface->w;
            irudiak[irudiKop].dest.h = surface->h;
            SDL_FreeSurface(surface);
            irudiak[irudiKop].id = id;
            irudiKop++;
            id++;
        }
    }
    else
    {
        printf("Has superado el maixmo de Imagens por aplicaci�n.Para aumentar imagen.h\n");
        return -1;
    }

    return id - 1;
}

void irudiaMugitu(int numImg, int x, int y)
{
    int id = irudiarenPosizioaAurkitu(numImg);
    if (id >= 0)
    {
        irudiak[id].dest.x = x;
        irudiak[id].dest.y = y;
    }
}

void matrizeIrudiaMugitu(int plataformaId, int x, int y)
{
    // Verificar que la textura no sea NULL
    SDL_Texture *texture = irudiak[plataformaId].texture;
    SDL_Renderer *gRenderer = getRenderer();
    int plataformaTamaina;

    plataformaTamaina = SCREEN_WIDTH / COLUMNAS;

    if (texture == NULL)
    {
        printf("Error: La textura con id %d no se ha cargado correctamente.\n", plataformaId);
        return;
    }

    // Crear un rectángulo destino para dibujar la imagen
    SDL_Rect destRect;
    destRect.x = x;
    destRect.y = y;

    // Establecemos el tamaño de la celda en el rectángulo destino
    destRect.w = plataformaTamaina; // Ancho de la celda
    destRect.h = plataformaTamaina; // Alto de la celda

    // Dibujar la textura en la pantalla con el nuevo tamaño escalado
    SDL_RenderCopy(gRenderer, texture, NULL, &destRect);
}

void irudiakMarraztu(irudia)
{
    int i = irudia;

    irudiaMarraztu(irudiak[i].texture, &irudiak[i].dest);
}

void irudiaKendu(int id)
{
    int i = 0, pos = 0;

    pos = irudiarenPosizioaAurkitu(id);
    SDL_DestroyTexture(irudiak[pos].texture);
    for (i = pos; i < irudiKop; i++)
    {

        irudiak[i] = irudiak[i + 1];
    }
    irudiKop--;
}

int irudiarenPosizioaAurkitu(int id)
{
    int i = 0;

    for (i = 0; i < irudiKop; i++)
    {
        if (id == irudiak[i].id)
        {
            return i;
        }
    }
    return -1;
}
