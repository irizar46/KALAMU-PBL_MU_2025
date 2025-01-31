#define ONGI_ETORRI_MEZUA "Sakatu return hasteko..."
#define JOKOA_SOUND "./sound/sonidoFondo.mp3"
#define REBOTE_SOUND "./sound/reboteAltuago.wav"
#define SALTO_SOUND "./sound/salto.wav"
#define ATERRIZAJE_SOUND "./sound/aterrizajeBaju.wav"
#define PLAYER_ESK "./img/protageldik_esk/geldik1.png"
#define PLAYER_EZK "./img/protageldik_esk/geldik1.png"
#define BACKGROUND_IMAGE "./img/tira1.png"
#define BOKADILLOA_IMAGE "./img/tutorial_hasiera/bokadilloa.png"
#define BOKADILLOA_IMAGE_ezk "./img/tutorial_hasiera/bokadillo_bukaera.png"
#define BUKAERA_FOTOGRAMAK 11
#define VELOCIDAD_MAXIMA_CAIDA 35.0f
#define VELOCIDAD_MAXIMA_HORIZONTAL 0.5f
#define GRAVITY 1 // Gravedad que afecta al jugador
#define MAX_JUMP_FORCE 25
#define TIME_SCALE 0.6
#define platformTamaina 45
#define PERTSONAI_ALTUERA 88
#define PERTSONAI_ZABALERA 63
#define GIPSY_FOTOGRAMAK 6
#define TUTO_FOTOGRAMAK 7
#define PROTAGELDIK 3
#define TIRA1 "./img/background/tira1.png"
#define TIRA2 "./img/background/tira2.png"
#define TIRA3 "./img/background/tira3.png"
#define TIRA4 "./img/background/tira4.png"
#define TIRA5 "./img/background/tira5.png"
#define TIRA6 "./img/background/tira6.png"
#define MAX_PLATAFORMA 24

#include "lib/game02.h"
#include "ebentoak.h"
#include "graphics.h"
#include "imagen.h"
#include "ourTypes.h"
#include "soinua.h"
#include "text.h"
#include <mapa.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>

EGOERA jokatu(void)
{
    EGOERA egoera = JOLASTEN;
    SDL_Event ebentu;
    Player jugador;
    Plataforma plataforma[MAX_IMG];
    int backgroundId, bokadilloa, offsetY = 0, numPlataformas = 0, irudia = -1, irudia_bukaera = -1, hasiera = 0,
                                  bukatua = 0;

    Mapas todosLosMapas;
    TodasLasPlataformas todasLasPlataformas;
    Erlazioa erlazioa;

    int currentFrame = 0;
    int idleFrame = 0; // Frame para la animación de estar quieto
    Uint32 lastFrameTime = 0;
    Uint32 lastIdleFrameTime = 0; // Tiempo para la animación de estar quieto
    Uint32 lastTime = SDL_GetTicks();

    int gipsyId[GIPSY_FOTOGRAMAK], tutoiD[TUTO_FOTOGRAMAK], geldik_esk[PROTAGELDIK], geldik_ezk[PROTAGELDIK],
        plataformaIds[MAX_PLATAFORMA], bokadilloa_ezk, amaiera, bukaeraId[BUKAERA_FOTOGRAMAK];

    char idgips[256], idtuto[256], geldik_eskid[256], geldik_ezkid[256], idbukaera[258];

    const char *gipsyID = "./img/gipsy/%d.png";
    const char *tutoID = "./img/tutorial_hasiera/gipsy%d.png";
    const char *geldik_eskuin = "./img/protageldik_esk/geldik%d.png";
    const char *geldik_ezker = "./img/protageldik_ezk/geldik%d.png";
    const char *bukaeraID = "./img/bukaera/bukaera%d.png";

    // Inicialización de elementos
    jugador.x = SCREEN_WIDTH / 2;
    jugador.y = SCREEN_HEIGHT - 180; // Suponiendo que la altura del jugador es 50px
    jugador.velY = 0;
    jugador.enSuelo = 1;
    jugador.cargandoSalto = 0;
    jugador.direccionJugador = 1; // Jugador mirando a la derecha

    int tira1id, tira2id, tira3id, tira4id, tira5id, tira6id;

    bokadilloa = irudiaKargatu(BOKADILLOA_IMAGE);
    bokadilloa_ezk = irudiaKargatu(BOKADILLOA_IMAGE_ezk);
    tira1id = irudiaKargatu(TIRA1);
    tira2id = irudiaKargatu(TIRA2);
    tira3id = irudiaKargatu(TIRA3);
    tira4id = irudiaKargatu(TIRA4);
    tira5id = irudiaKargatu(TIRA5);
    tira6id = irudiaKargatu(TIRA6);

    for (int i = 0; i < GIPSY_FOTOGRAMAK; i++)
    {
        snprintf(idgips, 256, gipsyID, i + 1);
        gipsyId[i] = irudiaKargatu(idgips);
    }
    for (int i = 0; i < BUKAERA_FOTOGRAMAK; i++)
    {
        snprintf(idbukaera, 256, bukaeraID, i + 1);
        bukaeraId[i] = irudiaKargatu(idbukaera);
    }

    for (int i = 0; i < TUTO_FOTOGRAMAK; i++)
    {
        snprintf(idtuto, 256, tutoID, i + 1);
        tutoiD[i] = irudiaKargatu(idtuto);
    }
    for (int i = 0; i < PROTAGELDIK; i++)
    {
        snprintf(geldik_eskid, 256, geldik_eskuin, i + 1);
        geldik_esk[i] = irudiaKargatu(geldik_eskid);

        printf("%d", geldik_esk[i]);
        fflush(stdout);
    }
    for (int i = 0; i < PROTAGELDIK; i++)
    {
        snprintf(geldik_ezkid, 256, geldik_ezker, i + 1);
        geldik_ezk[i] = irudiaKargatu(geldik_ezkid);
        printf("%d", geldik_ezk[i]);
        fflush(stdout);
    }

    int mapa[FILAS][COLUMNAS];

    cargarMapa(mapa, plataforma, &todosLosMapas, &todasLasPlataformas); // numplataformas kendu igual, geo rebisau
    plat_back_karga(plataformaIds, &jugador);

    musika_fondo(JOKOA_SOUND);

    while (egoera == JOLASTEN)
    {
        SDL_Delay(22); // Control de frames por segundo
        Uint32 currentTime = SDL_GetTicks();
        Uint32 deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        while (SDL_PollEvent(&ebentu))
        {
            jugador.enMovimiento = 0;
            prozesatuEbentuak(&ebentu, &jugador, &egoera, &irudia, &hasiera, &amaiera, &irudia_bukaera, &bukatua);
        }
        pantailaGarbitu();

        backgroundId = background(offsetY, tira1id, tira2id, tira3id, tira4id, tira5id, tira6id);

        if (irudia < 0)
        {
            if (offsetY > 0 && offsetY < 5)
            {

                irudiakMarraztu(backgroundId);
                actualizarYdibujarMapa(&todosLosMapas, &todasLasPlataformas, &erlazioa, &offsetY, plataformaIds);

                eguneratuJugador(&jugador, plataforma, numPlataformas, deltaTime, &offsetY, &erlazioa, &amaiera);

                pertsonaiaAnimazioa(&jugador, geldik_ezk, geldik_esk, currentTime, &lastFrameTime, &currentFrame,
                                    &lastIdleFrameTime, &idleFrame);
            }
            else if (offsetY == 0)
            {

                irudiakMarraztu(backgroundId);
                actualizarYdibujarMapa(&todosLosMapas, &todasLasPlataformas, &erlazioa, &offsetY, plataformaIds);

                eguneratuJugador(&jugador, plataforma, numPlataformas, deltaTime, &offsetY, &erlazioa, &amaiera);

                pertsonaiaAnimazioa(&jugador, geldik_ezk, geldik_esk, currentTime, &lastFrameTime, &currentFrame,
                                    &lastIdleFrameTime, &idleFrame);

                irudiaMugitu(tutoiD[1], 180, 845);
                irudiaMugitu(bokadilloa, 280, 680);
                irudiakMarraztu(tutoiD[1]);
                irudiakMarraztu(bokadilloa);
            }
            else
            {
                if (irudia_bukaera < 0)
                {

                    irudiakMarraztu(backgroundId);

                    actualizarYdibujarMapa(&todosLosMapas, &todasLasPlataformas, &erlazioa, &offsetY, plataformaIds);

                    eguneratuJugador(&jugador, plataforma, numPlataformas, deltaTime, &offsetY, &erlazioa, &amaiera);
                    // printf("OffsetY ondoren: %d\n", offsetY);
                    pertsonaiaAnimazioa(&jugador, geldik_ezk, geldik_esk, currentTime, &lastFrameTime, &currentFrame,
                                        &lastIdleFrameTime, &idleFrame);

                    if (offsetY == 5)
                    {

                        irudiaMugitu(tutoiD[6], 900, 130);
                        irudiakMarraztu(tutoiD[6]);
                    }
                    if (amaiera)
                    {
                        irudiaMugitu(bokadilloa_ezk, 700, 45); // Posición fija del personaje estático
                        irudiakMarraztu(bokadilloa_ezk);
                    }
                }

                else
                {
                    if (irudia_bukaera == 0)
                    {
                        setLogicalResolution(2000, 1100);
                    }
                    irudiakMarraztu(bukaeraId[irudia_bukaera]);
                }
                pantailaBerriztu();
            }
        }
        else
        {
            if (irudia == 0)
            {
                setLogicalResolution(2000, 1100);
                offsetY = 1;
            }
            irudiakMarraztu(gipsyId[irudia]);
        }
        pantailaBerriztu();
    }

    // Finalizar el juego
    jokoaBukatu(&jugador, backgroundId);

    return egoera;
}

void prozesatuEbentuak(SDL_Event *ebentu, Player *jugador, EGOERA *egoera, int *irudia, int *hasiera, int *amaiera,
                       int *irudia_bukaera, int *bukatua)
{
    const int playerSpeed = 7;

    if (ebentu->type == SDL_QUIT)
    {
        *egoera = JOKUA_AMAITU;
    }
    else if (ebentu->type == SDL_KEYDOWN)
    {
        switch (ebentu->key.keysym.sym)
        {
        case SDLK_x:
            *egoera = JOKUA_AMAITU;
            break;

        // Movimiento solo permitido si no se está cargando un salto
        case SDLK_LEFT:
            if (!jugador->cargandoSalto && jugador->enSuelo) // Solo si está en el suelo y no está cargando el salto
            {
                jugador->x -= playerSpeed;
            }
            jugador->direccionJugador = -1;
            jugador->enMovimiento = 1;
            // Cambiar la dirección del personaje a la izquierda
            break;

        case SDLK_RIGHT:
            if (!jugador->cargandoSalto && jugador->enSuelo) // Solo si está en el suelo y no está cargando el salto
            {
                jugador->x += playerSpeed;
            }
            jugador->direccionJugador = 1;
            jugador->enMovimiento = 1;
            // Cambiar la dirección del personaje a la derecha
            break;

        case SDLK_SPACE:
            if (jugador->enSuelo && !jugador->cargandoSalto &&
                *hasiera == 1) // Solo si está en el suelo y no está cargando el salto
            {
                jugador->cargandoSalto = 1;            // Comienza a cargar el salto
                jugador->inicioCarga = SDL_GetTicks(); // Guardamos el tiempo de inicio de carga
                                                       // Reproducir el sonido de salto
            }
            break;
        case SDLK_h:
            if (*hasiera == 0)
            {
                *irudia += 1;
                if (*irudia >= GIPSY_FOTOGRAMAK)
                {

                    *irudia = -1;
                    setLogicalResolution(1080, 1080);
                    *hasiera = 1;
                }
                break;
            }
        case SDLK_l:

            if (*amaiera == 1) // Solo si está en el suelo y no está cargando el salto
            {
                *irudia_bukaera += 1;
                if (*irudia_bukaera >= BUKAERA_FOTOGRAMAK)
                {
                    *irudia_bukaera = -1;
                    setLogicalResolution(1080, 1080);
                    *bukatua = 1;
                }
                if (*bukatua == 1)
                {
                    *egoera = JOKUA_AMAITU;
                }
            }

            // Cambiar la dirección del personaje a la izquierda
            break;
        }
    }
    else if (ebentu->type == SDL_KEYUP)
    {
        if (ebentu->key.keysym.sym == SDLK_SPACE)
        {
            // Si el jugador suelta la tecla de salto, se aplica el salto
            if (jugador->enSuelo && jugador->cargandoSalto)
            {

                // Determinar la dirección del salto:
                if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT]) // Si LEFT está presionado
                {
                    jugador->direccionSalto = -1; // Salto hacia la izquierda
                }
                else if (SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT]) // Si RIGHT está presionado
                {
                    jugador->direccionSalto = 1; // Salto hacia la derecha
                }
                else
                {
                    jugador->direccionSalto = 0; // Salto completamente vertical
                }

                // Calculamos el tiempo de carga
                Uint32 tiempoCargado = SDL_GetTicks() - jugador->inicioCarga + 200;

                // Aplicar salto proporcionalmente según el tiempo cargado
                jugador->velY = (int)(-roundf((tiempoCargado / 600.0f) * MAX_JUMP_FORCE));
                if (jugador->velY < -MAX_JUMP_FORCE)
                {
                    jugador->velY = -MAX_JUMP_FORCE; // Limitar la fuerza vertical
                }

                // Componente horizontal del salto (basado en la dirección en la que saltamos)
                if (jugador->direccionSalto != 0)
                {
                    jugador->velX = jugador->direccionSalto * abs(jugador->velY) / 2; // Proporcional a la
                }
                else
                {
                    jugador->velX = 0; // Sin movimiento horizontal si es un salto vertical
                }
                jugador->cargandoSalto = 0; // Deja de cargar el salto
                jugador->enSuelo = 0;
                // Reproducir el sonido de salto
                // El jugador ya no está en el suelo
            }
        }
        else if (ebentu->key.keysym.sym == SDLK_LEFT || ebentu->key.keysym.sym == SDLK_RIGHT)
        {
            // No hacemos nada con direccionJugador cuando se suelta la tecla de movimiento,
            // para que el personaje no cambie de dirección durante el salto.
        }
        // soinu_Efektoak(SALTO_SOUND);
    }
}

void eguneratuJugador(Player *jugador, Plataforma plataformas[], int numPlataformas, Uint32 deltaTime, int *offsetY,
                      Erlazioa *erlazioa, int *amaiera)
{
    int i;
    int sobrePlataforma = 0;

    // Aplicar gravedad
    if (!jugador->enSuelo)
    {
        jugador->velY += GRAVITY; // Incrementar velocidad vertical por gravedad
        if (jugador->velY > VELOCIDAD_MAXIMA_CAIDA)
        {
            jugador->velY = (int)VELOCIDAD_MAXIMA_CAIDA;
            jugador->x += jugador->velX; // Actualizar posición en Y
                                         // Limitar velocidad máxima de caída
        }
        jugador->y += jugador->velY; // Actualizar posición en Y
    }

    // Limitar la velocidad horizontal solo si el jugador está en el suelo
    if (jugador->enSuelo)
    {
        if (jugador->velX > VELOCIDAD_MAXIMA_HORIZONTAL)
        {
            jugador->velX = (int)VELOCIDAD_MAXIMA_HORIZONTAL;
        }
        else if (jugador->velX < -VELOCIDAD_MAXIMA_HORIZONTAL)
        {
            jugador->velX = (int)-VELOCIDAD_MAXIMA_HORIZONTAL;
        }
    }

    // Actualizar posición horizontal
    jugador->x += jugador->velX;

    // Comprobar colisiones con las plataformas
    for (i = 0; i < erlazioa->zenb; i++) // Recorremos todas las plataformas
    {
        Plataforma plataforma = erlazioa->plataformas[i];
        if (!sobrePlataforma)
        {
            jugador->enSuelo = 0;
        }
        if (jugador->x + PERTSONAI_ZABALERA > plataforma.x && jugador->x < plataforma.x &&
            jugador->y < plataforma.y + platformTamaina && jugador->y + PERTSONAI_ALTUERA > plataforma.y)
        {
            if (!jugador->enSuelo)
            {
                jugador->velX = -jugador->velX;
                jugador->velX = (int)(jugador->velX * 0.6f);
            }
            soinu_Efektoak(REBOTE_SOUND);
            printf("%d da", jugador->velY);
            jugador->x = plataforma.x - PERTSONAI_ZABALERA;

            printf("errebotatu du\n\n\n");
            fflush(stdout);
        }
        // ezkerreko errebote

        else if (jugador->x < plataforma.x + platformTamaina && jugador->x + PERTSONAI_ZABALERA > plataforma.x &&
                 jugador->y < plataforma.y + platformTamaina && jugador->y + PERTSONAI_ALTUERA > plataforma.y)
        {

            if (!jugador->enSuelo)
            {
                jugador->velX = -jugador->velX;
                jugador->velX = (int)(jugador->velX * 0.6);
            }
            if (!(jugador->velY < 0 && jugador->velY > 0))
            {
                jugador->x = plataforma.x + platformTamaina;
            }
            soinu_Efektoak(REBOTE_SOUND);
        }

        // Comprobar si el jugador está cayendo sobre una plataforma
        if (jugador->y + PERTSONAI_ALTUERA <= plataforma.y &&
            jugador->y + PERTSONAI_ALTUERA + jugador->velY >= plataforma.y &&
            jugador->x + PERTSONAI_ZABALERA > plataforma.x && jugador->x < plataforma.x + platformTamaina)
        {
            jugador->y = plataforma.y - PERTSONAI_ALTUERA; // Colocar al jugador sobre la plataforma
            jugador->velY = 0;                             // Detener la caída
            jugador->enSuelo = 1;                          // Indicar que está en el suelo
            sobrePlataforma = 1;
            break; // Salimos del bucle ya que hemos detectado colisión
        }
        // plataforma gainean salto

        else if (jugador->y + PERTSONAI_ALTUERA <= plataforma.y &&
                 jugador->y + PERTSONAI_ALTUERA + jugador->velY > plataforma.y &&
                 jugador->x + PERTSONAI_ZABALERA > plataforma.x + 5 && jugador->x + 5 < plataforma.x + platformTamaina)
        {
            // Colocamos al jugador justo encima de la plataforma
            jugador->y = plataforma.y - PERTSONAI_ALTUERA; // Colocar al jugador en la parte superior de la plataforma
            jugador->velY = 0;                             // Detener la caída
            jugador->enSuelo = 1;
            soinu_Efektoak(ATERRIZAJE_SOUND);
        }
        // plataforma azpian salto

        else if (jugador->y >= plataforma.y + platformTamaina &&
                 jugador->y + jugador->velY < plataforma.y + platformTamaina &&
                 jugador->x + PERTSONAI_ZABALERA > plataforma.x && jugador->x < plataforma.x + platformTamaina &&
                 jugador->velY < 0)
        {
            {

                jugador->velY += GRAVITY;
                jugador->velY = 0;
                jugador->velX = (int)(jugador->velX * 0.8f);
                soinu_Efektoak(REBOTE_SOUND);

                printf("%d ensuelo? %d velY? %d sobreplat?\n\n\n", jugador->enSuelo, jugador->velY, sobrePlataforma);
            }
        }
    }

    // Limitar el movimiento dentro de los bordes de la pantalla
    if (jugador->x < 0) // Límite izquierdo
    {
        jugador->x = 0;
        if (jugador->velX < 0) // Solo invertir si el jugador se mueve hacia el borde
        {
            jugador->velX = (int)(-jugador->velX * 0.7f); // Rebote con menor pérdida de velocidad
            soinu_Efektoak(REBOTE_SOUND);                 // Sonido del rebote
        }
    }
    if (jugador->x > SCREEN_WIDTH - PERTSONAI_ZABALERA) // Límite derecho
    {
        jugador->x = SCREEN_WIDTH - PERTSONAI_ZABALERA;
        if (jugador->velX > 0) // Solo invertir si el jugador se mueve hacia el borde
        {
            jugador->velX = (int)(-jugador->velX * 0.7f); // Rebote con menor pérdida de velocidad
            soinu_Efektoak(REBOTE_SOUND);                 // Sonido del rebote
        }
    }

    // Actualizar offsetY si el jugador toca los límites superior o inferior de la pantalla
    if (jugador->y + PERTSONAI_ALTUERA <= 0) // Límite superior
    {
        *offsetY += 1;
        jugador->y = SCREEN_HEIGHT - PERTSONAI_ALTUERA;
    }
    else if (jugador->y + PERTSONAI_ALTUERA >= SCREEN_HEIGHT) // Límite inferior
    {
        *offsetY -= 1;
        jugador->y = 0 - PERTSONAI_ALTUERA;
    }

    // Comprobar condición de finalización del juego
    if (*offsetY == 5 && jugador->y < 180 && jugador->x + PERTSONAI_ZABALERA > 675)
    {
        *amaiera = 1;
    }
    else
    {
        *amaiera = 0;
    }
}

void jokoaBukatu(Player *jugador, int backgroundId)
{
    irudiaKendu(jugador->id);
    irudiaKendu(backgroundId);
    sgItxi(); // Cerrar la ventana SDL
}

#define PLATAFORMA_TAMAINA 45
#define MAX_IMG 100

int mapa[FILAS][COLUMNAS]; // Declaración externa del mapa

void cargarMapa(int mapa[FILAS][COLUMNAS], Plataforma plataforma[MAX_IMG], Mapas *todosLosMapas,
                TodasLasPlataformas *todasLasPlataformas)
{
    // Mapa básico donde 1 representa una plataforma y 0 espacio vacío
    int mapa5[FILAS][COLUMNAS] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 19, 20, 19, 20, 19, 20, 19, 20, 19, 20, 19, 20, 18, 18, 18, 18, 18, 19, 20, 19, 20},
        {0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 23, 21, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 21, 21, 21, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 21, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 22, 22, 0, 0, 0, 0, 0, 21, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 21, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 21, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 21, 0, 0, 0},
        {0, 0, 0, 23, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 21, 23, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 21, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 22, 22, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    };
    int mapa4[FILAS][COLUMNAS] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 17, 15, 16, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 15, 15, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {17, 17, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 16, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 15, 15, 16, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 16, 17, 0, 0, 0, 0, 17, 17, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };
    int mapa3[FILAS][COLUMNAS] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 13, 13, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 8, 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 13, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 12, 14, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12, 12, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 6, 6, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 8, 8, 6, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 10, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 0, 0, 0, 0, 0, 9, 9, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 10, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 11, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 11, 11, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    };
    int mapa2[FILAS][COLUMNAS] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 6, 6, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 8, 8, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 8, 8, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 6, 8, 8, 8, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    };
    int mapa1[FILAS][COLUMNAS] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1},
        {2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2},
        {2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2},
        {2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2},
        {2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2},
        {2, 2, 2, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 2, 2},
        {2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

    };

    // Copiar los datos de cada mapa predefinido a la estructura de mapas
    for (int i = 0; i < FILAS; i++)
    {
        for (int j = 0; j < COLUMNAS; j++)
        {
            todosLosMapas->mapas[0][i][j] = mapa1[i][j];
            todosLosMapas->mapas[1][i][j] = mapa2[i][j];
            todosLosMapas->mapas[2][i][j] = mapa3[i][j];
            todosLosMapas->mapas[3][i][j] = mapa4[i][j];
            todosLosMapas->mapas[4][i][j] = mapa5[i][j];
        }
    }

    todasLasPlataformas->zenb[0] = inicializarPlataformas(todosLosMapas->mapas[0], todasLasPlataformas->plataformas[0]);
    todasLasPlataformas->zenb[1] = inicializarPlataformas(todosLosMapas->mapas[1], todasLasPlataformas->plataformas[1]);
    todasLasPlataformas->zenb[2] = inicializarPlataformas(todosLosMapas->mapas[2], todasLasPlataformas->plataformas[2]);
    todasLasPlataformas->zenb[3] = inicializarPlataformas(todosLosMapas->mapas[3], todasLasPlataformas->plataformas[3]);
    todasLasPlataformas->zenb[4] = inicializarPlataformas(todosLosMapas->mapas[4], todasLasPlataformas->plataformas[4]);
}

void actualizarYdibujarMapa(Mapas *todosLosMapas, TodasLasPlataformas *todasLasPlataformas, Erlazioa *erlazioa,
                            int *offsetY, int plataformaIds[MAX_PLATAFORMA])
{
    int(*mapa)[COLUMNAS];
    Plataforma *plataformas;
    int zenb;

    // Seleccionar la matriz adecuada en función de offsetY
    // printf("%d\n", *offsetY);

    switch (*offsetY)
    { // plataformas = ... hurrengo moduan ourtypesen definitutako struct bateko arreglo baten balioa beste balio bati
    // pasatzen ari zarelako da. Sobrare hau punteroen bitartez ezin da egin eta ondorioz memcpy erabiliz eginda dago.
    // memcpyk bigarrengo datue lehenengon kopiatzen do hirugarrenaren tamainarekin.
    case 1:
        mapa = todosLosMapas->mapas[0];
        plataformas = todasLasPlataformas->plataformas[0];
        zenb = todasLasPlataformas->zenb[0];
        break;
    case 2:
        mapa = todosLosMapas->mapas[1];
        plataformas = todasLasPlataformas->plataformas[1];
        zenb = todasLasPlataformas->zenb[1];
        break;
    case 3:
        mapa = todosLosMapas->mapas[2];
        plataformas = todasLasPlataformas->plataformas[2];
        zenb = todasLasPlataformas->zenb[2];
        break;
    case 4:
        mapa = todosLosMapas->mapas[3];
        plataformas = todasLasPlataformas->plataformas[3];
        zenb = todasLasPlataformas->zenb[3];
        break;
    case 5:
        mapa = todosLosMapas->mapas[4];
        plataformas = todasLasPlataformas->plataformas[4];
        zenb = todasLasPlataformas->zenb[4];
        break;
    case 6:

        return;
    default:
        mapa = todosLosMapas->mapas[0];
        plataformas = todasLasPlataformas->plataformas[0];
        zenb = todasLasPlataformas->zenb[0];
        break;
    }
    // Copiar las plataformas seleccionadas a erlazioa
    for (int i = 0; i < zenb; i++)
    {
        erlazioa->plataformas[i] = plataformas[i];
    }
    erlazioa->zenb = zenb;

    // Dibujar la matriz seleccionada
    dibujarMapa(mapa, plataformaIds);
}

// Dibuja todas las plataformas del mapa
void dibujarMapa(int mapa[FILAS][COLUMNAS], int *plataformaIds)
{

    for (int i = 1; i < FILAS; i++)
    {
        for (int j = 0; j < COLUMNAS; j++)
        {
            if (mapa[i][j] > 0 && mapa[i][j] < 24)

            // Si hay una plataforma en esta celda
            {
                int x = j * PLATAFORMA_TAMAINA; // Coordenada X
                int y = i * PLATAFORMA_TAMAINA; // Coordenada Y

                matrizeIrudiaMugitu(plataformaIds[mapa[i][j] - 1], x, y);
            }
        }
    }
}

int inicializarPlataformas(int mapa[FILAS][COLUMNAS], Plataforma plataforma[MAX_IMG])
{
    int zenb = 0;
    for (int i = 1; i < FILAS; i++)
    {
        for (int j = 0; j < COLUMNAS; j++)
        {
            if (mapa[i][j] > 0 && mapa[i][j] < 25)
            {
                plataforma[zenb].x = j * PLATAFORMA_TAMAINA; // hemen matrizeko plataforma zenbakiaz gain
                                                             // igual structeko arrayaren plataforma posiziao jarri?
                plataforma[zenb].y = i * PLATAFORMA_TAMAINA;
                zenb++;
                // printf("Plataforma %d: x = %d, y = %d\n", zenb, plataforma[zenb].x, plataforma[zenb].y);
            }
        }
    }

    for (int g = zenb; g < MAX_IMG; g++)
    {
        plataforma[g].x = -1;
        plataforma[g].y = -1;
        // printf("Plataforma g:%d: x = g:%d, y = g:%d\n", g, plataforma[g].x, plataforma[g].y);
    }

    return zenb; // Devolver la cantidad de plataformas
}

int background(int offsetY, int tira1id, int tira2id, int tira3id, int tira4id, int tira5id, int tira6id)
{
    int backgroundId = 0;

    switch (offsetY)
    {
    case 1:
        backgroundId = tira1id;
        break;
    case 2:
        backgroundId = tira2id;
        break;
    case 3:
        backgroundId = tira3id;
        break;
    case 4:
        backgroundId = tira4id;
        break;
    case 5:
        backgroundId = tira5id;
        break;
    case 6:
        backgroundId = tira6id;
        break;
    default:
        backgroundId = tira1id;
        break;
    }

    return backgroundId;
}

void plat_back_karga(int plataformaIds[MAX_PLATAFORMA], Player *jugador)
{
#define goranLurra "./img/plataformak/offset1/goranLurra45x45.png"
#define lurrikEz1 "./img/plataformak/offset1/lurrikEz45x45.png"
#define eskubian "./img/plataformak/offset1/eskubian45x45.png"
#define ezkerrean "./img/plataformak/offset1/ezkerrean45x45.png"
#define beheran "./img/plataformak/offset1/beheran45x45.png"
#define lurBeltza "./img/plataformak/offset2/lurBeltza45x45.png"
#define lurGorria "./img/plataformak/offset2/lurGorria45x45.png"
#define lurMarroia "./img/plataformak/offset2/lurMarroia45x45.png"
#define elurBeltza "./img/plataformak/offset3/elurBeltz45x45.png"
#define elurGorri "./img/plataformak/offset3/elurGorri45x45.png"
#define elurMarroi "./img/plataformak/offset3/elurMarroi45x45.png"
#define elurZuriBeltz "./img/plataformak/offset3/elurZuriBeltz45x45.png"
#define elurZuriGorri "./img/plataformak/offset3/elurZuriGorri45x45.png"
#define elurZuriMarroi "./img/plataformak/offset3/elurZuriMarroi45x45.png"
#define HoriaBeltza "./img/plataformak/offset4/HoriaBeltza45x45.png"
#define HoriaGorria "./img/plataformak/offset4/HoriaGorria45x45.png"
#define HoriaMarroia "./img/plataformak/offset4/HoriaMarroia45x45.png"
#define BerdeaMarroia "./img/plataformak/offset5/BerdeaMarroia45x45.png"
#define BerdeBeltza "./img/plataformak/offset5/BerdeBeltza45x45.png"
#define BerdeGrisa "./img/plataformak/offset5/BerdeGrisa45x45.png"
#define LurGabeGrisa "./img/plataformak/offset5/LurGabeGrisa45x45.png"
#define TxerriBeltza "./img/plataformak/offset5/TxerriBeltza45x45.png"
#define TxerriGrisa "./img/plataformak/offset5/TxerriGrisa45x45.png"
#define TxerriMarroia "./img/plataformak/offset5/TxerriMarroia45x45.png"

    plataformaIds[0] = irudiaKargatu(goranLurra);
    plataformaIds[1] = irudiaKargatu(lurrikEz1);
    plataformaIds[2] = irudiaKargatu(eskubian);
    plataformaIds[3] = irudiaKargatu(ezkerrean);
    plataformaIds[4] = irudiaKargatu(beheran);
    plataformaIds[5] = irudiaKargatu(lurBeltza);
    plataformaIds[6] = irudiaKargatu(lurGorria);
    plataformaIds[7] = irudiaKargatu(lurMarroia);
    plataformaIds[8] = irudiaKargatu(elurBeltza);
    plataformaIds[9] = irudiaKargatu(elurGorri);
    plataformaIds[10] = irudiaKargatu(elurMarroi);
    plataformaIds[11] = irudiaKargatu(elurZuriBeltz);
    plataformaIds[12] = irudiaKargatu(elurZuriGorri);
    plataformaIds[13] = irudiaKargatu(elurZuriMarroi);
    plataformaIds[14] = irudiaKargatu(HoriaBeltza);
    plataformaIds[15] = irudiaKargatu(HoriaGorria);
    plataformaIds[16] = irudiaKargatu(HoriaMarroia);
    plataformaIds[17] = irudiaKargatu(BerdeaMarroia);
    plataformaIds[18] = irudiaKargatu(BerdeBeltza);
    plataformaIds[19] = irudiaKargatu(BerdeGrisa);
    plataformaIds[20] = irudiaKargatu(LurGabeGrisa);
    plataformaIds[21] = irudiaKargatu(TxerriBeltza);
    plataformaIds[22] = irudiaKargatu(TxerriGrisa);
    plataformaIds[23] = irudiaKargatu(TxerriMarroia);

    jugador->geldirik_eskuin[0] = irudiaKargatu("img/pertsonaia_dena/geldik_eskuin1_ofi.png");
    jugador->geldirik_eskuin[1] = irudiaKargatu("img/pertsonaia_dena/geldik_eskuin2_ofi.png");
    jugador->geldirik_eskuin[2] = irudiaKargatu("img/pertsonaia_dena/Saltoa_eskuin.png");

    jugador->geldirik_ezker[0] = irudiaKargatu("img/pertsonaia_dena/geldik_ezker1_ofi.png");
    jugador->geldirik_ezker[1] = irudiaKargatu("img/pertsonaia_dena/geldik_ezker2_ofi.png");
    jugador->geldirik_ezker[2] = irudiaKargatu("img/pertsonaia_dena/Saltoa_ezker.png");

    jugador->eskuin[0] = irudiaKargatu("img/pertsonaia_dena/animazio_esk1.png");
    jugador->eskuin[1] = irudiaKargatu("img/pertsonaia_dena/animazio_esk2.png");
    jugador->eskuin[2] = irudiaKargatu("img/pertsonaia_dena/animazio_esk3.png");
    jugador->eskuin[3] = irudiaKargatu("img/pertsonaia_dena/animazio_esk4.png");
    jugador->eskuin[4] = irudiaKargatu("img/pertsonaia_dena/animazio_esk5.png");
    jugador->eskuin[5] = irudiaKargatu("img/pertsonaia_dena/animazio_esk6.png");
    jugador->eskuin[6] = irudiaKargatu("img/pertsonaia_dena/animazio_esk7.png");
    jugador->eskuin[7] = irudiaKargatu("img/pertsonaia_dena/animazio_esk8.png");

    jugador->ezker[0] = irudiaKargatu("img/pertsonaia_dena/animazio_ezk1.png");
    jugador->ezker[1] = irudiaKargatu("img/pertsonaia_dena/animazio_ezk2.png");
    jugador->ezker[2] = irudiaKargatu("img/pertsonaia_dena/animazio_ezk3.png");
    jugador->ezker[3] = irudiaKargatu("img/pertsonaia_dena/animazio_ezk4.png");
    jugador->ezker[4] = irudiaKargatu("img/pertsonaia_dena/animazio_ezk5.png");
    jugador->ezker[5] = irudiaKargatu("img/pertsonaia_dena/animazio_ezk6.png");
    jugador->ezker[6] = irudiaKargatu("img/pertsonaia_dena/animazio_ezk7.png");
    jugador->ezker[7] = irudiaKargatu("img/pertsonaia_dena/animazio_ezk8.png");
}

void pertsonaiaAnimazioa(Player *jugador, int geldik_ezk[PROTAGELDIK], int geldik_esk[PROTAGELDIK], int currentTime,
                         int *lastFrameTime, int *currentFrame, int *lastIdleFrameTime, int *idleFrame)
{

    if ((jugador->cargandoSalto == 1) && (jugador->enSuelo == 1))
    {
        if (jugador->direccionJugador == 1)
        {
            irudiaMugitu(jugador->geldirik_eskuin[2], jugador->x, jugador->y);
            irudiakMarraztu(jugador->geldirik_eskuin[2]);
        }
        else
        {
            irudiaMugitu(jugador->geldirik_ezker[2], jugador->x, jugador->y);
            irudiakMarraztu(jugador->geldirik_ezker[2]);
        }
    }
    else if ((jugador->enMovimiento == 1) && (jugador->enSuelo == 1))
    {
        // Animación de movimiento (4 frames)
        if (currentTime - *lastFrameTime > 170) // Cambiar frame cada 100ms
        {
            *currentFrame = (*currentFrame + 1) % 8; // Ciclo de 4 frames
            *lastFrameTime = currentTime;
        }
        if (jugador->direccionJugador == 1)
        {
            irudiaMugitu(jugador->eskuin[*currentFrame], jugador->x, jugador->y);
            irudiakMarraztu(jugador->eskuin[*currentFrame]);
        }
        else
        {
            irudiaMugitu(jugador->ezker[*currentFrame], jugador->x, jugador->y);
            irudiakMarraztu(jugador->ezker[*currentFrame]);
        }
    }
    else if (jugador->enMovimiento == 0 && jugador->enSuelo == 1)
    {
        if (currentTime - *lastIdleFrameTime > 400) // Cambiar frame cada 200ms
        {
            *idleFrame = (*idleFrame + 1) % 2; // Cambiar entre los 2 frames disponibles
            *lastIdleFrameTime = currentTime;
        }
        if (jugador->direccionJugador == 1)
        {
            irudiaMugitu(jugador->geldirik_eskuin[*idleFrame], jugador->x, jugador->y);
            irudiakMarraztu(jugador->geldirik_eskuin[*idleFrame]);
        }
        else
        {
            irudiaMugitu(jugador->geldirik_ezker[*idleFrame], jugador->x, jugador->y);
            irudiakMarraztu(jugador->geldirik_ezker[*idleFrame]);
        }
    }
    else
    {
        if (jugador->direccionJugador == 1)
        {
            irudiaMugitu(jugador->geldirik_eskuin[0], jugador->x, jugador->y);
            irudiakMarraztu(jugador->geldirik_eskuin[0]);
        }
        else if (jugador->direccionJugador == -1)
        {
            irudiaMugitu(jugador->geldirik_ezker[0], jugador->x, jugador->y);
            irudiakMarraztu(jugador->geldirik_ezker[0]);
        }
    }
}
