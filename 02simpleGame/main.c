#include "ebentoak.h"
#include "graphics.h"
#include "imagen.h"
#include "lib/game02.h"
#include "menua.h"
#include "ourTypes.h"
#include "soinua.h"
#include "text.h"
#include <stdio.h>

int main(int argc, char *str[])
{

    // Liberar recursos de SDL
    int jarraitu = 0; // Variable para decidir si seguir jugando
    EGOERA egoera;
    // Variable para almacenar el estado del juego

    // Inicializar el entorno SDL

    jarraitu = menua_kargatu();
    if (sgHasieratu() == -1)
    {
        fprintf(stderr, "Unable to set video: %s\n", SDL_GetError());
        return 1;
    }

    // Activar el sistema de texto
    textuaGaitu();

    // Mostrar la pantalla de inicio del juego
    jokoaAurkeztu();

    // Bucle principal del juego
    do
    {
        // Llamar a la función principal de juego, que devuelve el estado del juego
        egoera = jokatu();

    } while (jarraitu); // Continuar jugando si la variable 'jarraitu' es no cero

    sgItxi();

    return 0; // Finalizar el programa correctamente
}
