#include "menua.h"
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
SDL_Texture *loadTexture(const char *path, SDL_Renderer *renderer)
{
    SDL_Surface *loadedSurface = IMG_Load(path);

    SDL_Texture *newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
    SDL_FreeSurface(loadedSurface);
}
int menua_kargatu(void)
{
    SDL_Window *window =
        SDL_CreateWindow("KALAMU", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN);

    // Establecer el icono de la ventana
    const char *iconPath = "./img/menua/Pertsonaia.png"; // Cambia la ruta de la imagen del icono
    SDL_Surface *iconSurface = IMG_Load(iconPath);
    if (!iconSurface)
    {
        fprintf(stderr, "Error al cargar el icono: %s\n", IMG_GetError());
    }
    else
    {
        SDL_SetWindowIcon(window, iconSurface);
        SDL_FreeSurface(iconSurface);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    return PantailaPrintzipala(window, renderer);
}
int PantailaPrintzipala(SDL_Window *window, SDL_Renderer *renderer)
{
    Mix_Music *backgroundMusic = Mix_LoadMUS("./img/menua/musika.mp3");

    // Cargar recursos necesarios
    const char *fondoPath = "./img/menua/imagen1.png";
    SDL_Texture *fondoTexture = IMG_LoadTexture(renderer, fondoPath);

    const char *botonJugarPath = "./img/menua/jolastu.png";
    const char *botonHoverPath = "./img/menua/jolastu_hover.png";
    SDL_Texture *botonJugarTexture = IMG_LoadTexture(renderer, botonJugarPath);
    SDL_Texture *botonHoverTexture = IMG_LoadTexture(renderer, botonHoverPath);

    // Ruta de la imagen de fondo
    const char *imagePath = "./img/menua/imagen1.png";
    // Intentar cargar textura de fondo
    fprintf(stdout, "Cargando la imagen desde: %s\n", imagePath);
    SDL_Texture *texture = IMG_LoadTexture(renderer, imagePath);
    if (!texture)
    {
        fprintf(stderr, "Error al cargar la textura: %s\n", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        IMG_Quit();
        SDL_Quit();
    }
    else
    {
        fprintf(stdout, "Textura cargada correctamente\n");
    }

    // Obtener el tamaño de la textura
    int texW = 0;
    int texH = 0;
    SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
    fprintf(stdout, "Tamaño de la textura: %d x %d\n", texW, texH);

    // Ajustar el tamaño de la textura al tamaño de la ventana
    SDL_Rect dstrect = {0, 0, 1280, 720};

    // Renderizar la textura
    fprintf(stdout, "Renderizando la textura\n");
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Fondo blanco
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_RenderPresent(renderer);
    fprintf(stdout, "Textura renderizada\n");

    // Ruta de la imagen del botón
    const char *buttonPath = "./img/menua/jolastu.png";
    const char *buttonHoverPath = "./img/menua/jolastu_hover.png";

    // Intentar cargar textura del botón
    fprintf(stdout, "Cargando la imagen del botón desde: %s\n", buttonPath);
    SDL_Texture *buttonTexture = IMG_LoadTexture(renderer, buttonPath);
    if (!buttonTexture)
    {
        fprintf(stderr, "Error al cargar la textura del botón: %s\n", IMG_GetError());
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        IMG_Quit();
        SDL_Quit();
    }
    else
    {
        fprintf(stdout, "Textura del botón cargada correctamente\n");
    }

    // Intentar cargar textura del botón cuando el ratón está sobre él
    fprintf(stdout, "Cargando la imagen del botón hover desde: %s\n", buttonHoverPath);
    SDL_Texture *buttonHoverTexture = IMG_LoadTexture(renderer, buttonHoverPath);
    if (!buttonHoverTexture)
    {
        fprintf(stderr, "Error al cargar la textura del botón hover: %s\n", IMG_GetError());
        SDL_DestroyTexture(buttonTexture);
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        IMG_Quit();
        SDL_Quit();
    }
    else
    {
        fprintf(stdout, "Textura del botón hover cargada correctamente\n");
    }

    // Definir la posición y tamaño del botón
    SDL_Rect buttonRect = {300, 550, 200, 100}; // Ajusta estos valores según sea necesario

    // Ruta de la imagen del segundo botón
    const char *buttonPath2 = "./img/menua/ezarpenak.png";
    const char *buttonHoverPath2 = "./img/menua/ezarpenak_hover.png";

    // Intentar cargar textura del segundo botón
    fprintf(stdout, "Cargando la imagen del segundo botón desde: %s\n", buttonPath2);
    SDL_Texture *buttonTexture2 = IMG_LoadTexture(renderer, buttonPath2);
    if (!buttonTexture2)
    {
        fprintf(stderr, "Error al cargar la textura del segundo botón: %s\n", IMG_GetError());
        SDL_DestroyTexture(buttonTexture);
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        IMG_Quit();
        SDL_Quit();
    }
    else
    {
        fprintf(stdout, "Textura del segundo botón cargada correctamente\n");
    }

    // Intentar cargar textura del segundo botón cuando el ratón está sobre él
    fprintf(stdout, "Cargando la imagen del segundo botón hover desde: %s\n", buttonHoverPath2);
    SDL_Texture *buttonHoverTexture2 = IMG_LoadTexture(renderer, buttonHoverPath2);
    if (!buttonHoverTexture2)
    {
        fprintf(stderr, "Error al cargar la textura del segundo botón hover: %s\n", IMG_GetError());
        SDL_DestroyTexture(buttonTexture2);
        SDL_DestroyTexture(buttonTexture);
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        IMG_Quit();
        SDL_Quit();
    }
    else
    {
        fprintf(stdout, "Textura del segundo botón hover cargada correctamente\n");
    }

    SDL_Rect buttonRect2 = {530, 548, 200, 105}; // Ajusta estos valores según sea necesario

    // Ruta de la imagen del tercer botón quit
    const char *buttonPath3 = "./img/menua/irten.png";
    const char *buttonHoverPath3 = "./img/menua/irten_hover.png";

    // Intentar cargar textura del tercer botón
    fprintf(stdout, "Cargando la imagen del tercer botón desde: %s\n", buttonPath3);
    SDL_Texture *buttonTexture3 = IMG_LoadTexture(renderer, buttonPath3);
    if (!buttonTexture3)
    {
        fprintf(stderr, "Error al cargar la textura del tercer botón: %s\n", IMG_GetError());
        SDL_DestroyTexture(buttonTexture2);
        SDL_DestroyTexture(buttonTexture);
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        IMG_Quit();
        SDL_Quit();
    }
    else
    {
        fprintf(stdout, "Textura del tercer botón cargada correctamente\n");
    }

    // Intentar cargar textura del tercer botón cuando el ratón está sobre él
    fprintf(stdout, "Cargando la imagen del tercer botón hover desde: %s\n", buttonHoverPath3);
    SDL_Texture *buttonHoverTexture3 = IMG_LoadTexture(renderer, buttonHoverPath3);
    if (!buttonHoverTexture3)
    {
        fprintf(stderr, "Error al cargar la textura del tercer botón hover: %s\n", IMG_GetError());
        SDL_DestroyTexture(buttonTexture3);
        SDL_DestroyTexture(buttonTexture2);
        SDL_DestroyTexture(buttonTexture);
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        IMG_Quit();
        SDL_Quit();
    }
    else
    {
        fprintf(stdout, "Textura del tercer botón hover cargada correctamente\n");
    }

    SDL_Rect buttonRect3 = {70, 552, 200, 102}; // Ajusta estos valores según sea necesario

    // Ruta de la imagen del cuarto botón
    const char *buttonPath4 = "./img/menua/volumensi.png";
    const char *buttonHoverPath4 = "./img/menua/volumensi_hover.png";

    // Intentar cargar textura del cuarto botón
    fprintf(stdout, "Cargando la imagen del cuarto botón desde: %s\n", buttonPath4);
    SDL_Texture *buttonTexture4 = IMG_LoadTexture(renderer, buttonPath4);
    if (!buttonTexture4)
    {
        fprintf(stderr, "Error al cargar la textura del cuarto botón: %s\n", IMG_GetError());
        SDL_DestroyTexture(buttonTexture3);
        SDL_DestroyTexture(buttonTexture2);
        SDL_DestroyTexture(buttonTexture);
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        IMG_Quit();
        SDL_Quit();
    }
    else
    {
        fprintf(stdout, "Textura del cuarto botón cargada correctamente\n");
    }

    // Intentar cargar textura del cuarto botón cuando el ratón está sobre él
    fprintf(stdout, "Cargando la imagen del cuarto botón hover desde: %s\n", buttonHoverPath4);
    SDL_Texture *buttonHoverTexture4 = IMG_LoadTexture(renderer, buttonHoverPath4);
    if (!buttonHoverTexture4)
    {
        fprintf(stderr, "Error al cargar la textura del cuarto botón hover: %s\n", IMG_GetError());
        SDL_DestroyTexture(buttonTexture4);
        SDL_DestroyTexture(buttonTexture3);
        SDL_DestroyTexture(buttonTexture2);
        SDL_DestroyTexture(buttonTexture);
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        IMG_Quit();
        SDL_Quit();
    }
    else
    {
        fprintf(stdout, "Textura del cuarto botón hover cargada correctamente\n");
    }

    SDL_Rect buttonRect4 = {1150, 0, 130, 110}; // Ajusta estos valores según sea necesario

    // Ruta de la imagen del quinto botón
    const char *buttonPath5 = "./img/menua/volumenno.png";
    const char *buttonHoverPath5 = "./img/menua/volumenno_hover.png";

    // Intentar cargar textura del quinto botón
    fprintf(stdout, "Cargando la imagen del quinto botón desde: %s\n", buttonPath5);
    SDL_Texture *buttonTexture5 = IMG_LoadTexture(renderer, buttonPath5);
    if (!buttonTexture5)
    {
        fprintf(stderr, "Error al cargar la textura del quinto botón: %s\n", IMG_GetError());
        SDL_DestroyTexture(buttonTexture4);
        SDL_DestroyTexture(buttonTexture3);
        SDL_DestroyTexture(buttonTexture2);
        SDL_DestroyTexture(buttonTexture);
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);
        IMG_Quit();
        SDL_Quit();
    }
    else
    {
        fprintf(stdout, "Textura del quinto botón cargada correctamente\n");
    }

    // Intentar cargar textura del quinto botón cuando el ratón está sobre él
    fprintf(stdout, "Cargando la imagen del quinto botón hover desde: %s\n", buttonHoverPath5);
    SDL_Texture *buttonHoverTexture5 = IMG_LoadTexture(renderer, buttonHoverPath5);
    if (!buttonHoverTexture5)
    {
        fprintf(stderr, "Error al cargar la textura del quinto botón hover: %s\n", IMG_GetError());
        SDL_DestroyTexture(buttonTexture5);
        SDL_DestroyTexture(buttonTexture4);
        SDL_DestroyTexture(buttonTexture3);
        SDL_DestroyTexture(buttonTexture2);
        SDL_DestroyTexture(buttonTexture);
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);

        IMG_Quit();
        SDL_Quit();
    }
    else
    {
        fprintf(stdout, "Textura del quinto botón hover cargada correctamente\n");
    }

    SDL_Rect buttonRect5 = {1158, 100, 115, 105}; // Ajusta estos valores según sea necesario
    // Ruta de la imagen del sexto botón
    const char *buttonPath6 = "./img/menua/logoa.png";

    // Intentar cargar textura del sexto botón
    fprintf(stdout, "Cargando la imagen del sexto botón desde: %s\n", buttonPath6);
    SDL_Texture *buttonTexture6 = IMG_LoadTexture(renderer, buttonPath6);
    if (!buttonTexture6)
    {
        fprintf(stderr, "Error al cargar la textura del sexto botón: %s\n", IMG_GetError());
        SDL_DestroyTexture(buttonTexture5);
        SDL_DestroyTexture(buttonTexture4);
        SDL_DestroyTexture(buttonTexture3);
        SDL_DestroyTexture(buttonTexture2);
        SDL_DestroyTexture(buttonTexture);
        SDL_DestroyTexture(texture);
        SDL_DestroyRenderer(renderer);

        IMG_Quit();
        SDL_Quit();
    }
    else
    {
        fprintf(stdout, "Textura del sexto botón cargada correctamente\n");
    }

    SDL_Rect buttonRect6 = {50, 25, 600, 600}; // Ajusta estos valores según sea necesario

    // Bucle de eventos para mantener la ventana abierta

    // Limpiar recursos
    SDL_Rect botonJugarRect = {300, 550, 200, 100};

    int running = 1;
    SDL_Event event;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                if (mouseX > buttonRect.x && mouseX < buttonRect.x + buttonRect.w && mouseY > buttonRect.y &&
                    mouseY < buttonRect.y + buttonRect.h)
                {
                    fprintf(stdout, "Botón clicado\n");
                    return 1; // Llamar a la función para abrir la nueva ventana
                }
                else if (mouseX > buttonRect2.x && mouseX < buttonRect2.x + buttonRect2.w && mouseY > buttonRect2.y &&
                         mouseY < buttonRect2.y + buttonRect2.h)
                {
                    fprintf(stdout, "Segundo botón clicado\n");
                    EzarpenakBotoiarenFuntzioa(window, renderer);
                }
                else if (mouseX > buttonRect3.x && mouseX < buttonRect3.x + buttonRect3.w && mouseY > buttonRect3.y &&
                         mouseY < buttonRect3.y + buttonRect3.h)
                {
                    fprintf(stdout, "Tercer botón clicado\n");
                    running = 0; // JOKOA ITXI
                }
                else if (mouseX > buttonRect4.x && mouseX < buttonRect4.x + buttonRect4.w && mouseY > buttonRect4.y &&
                         mouseY < buttonRect4.y + buttonRect4.h)
                {
                    fprintf(stdout, "Cuarto botón clicado volumen\n");
                    Mix_VolumeMusic(MIX_MAX_VOLUME / 16);
                    // MUSIKA IGO
                }
                else if (mouseX > buttonRect5.x && mouseX < buttonRect5.x + buttonRect5.w && mouseY > buttonRect5.y &&
                         mouseY < buttonRect5.y + buttonRect5.h)
                {
                    fprintf(stdout, "Quinto botón clicado\n");
                    Mix_VolumeMusic(0);
                    // MUSIKA JEITSI
                }
            }
        }

        // Obtener la posición del ratón
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        // Renderizar la textura en cada iteración del bucle
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Fondo blanco
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, &dstrect);

        // Cambiar la textura del botón si el ratón está sobre él
        if (mouseX > buttonRect.x && mouseX < buttonRect.x + buttonRect.w && mouseY > buttonRect.y &&
            mouseY < buttonRect.y + buttonRect.h)
        {
            SDL_RenderCopy(renderer, buttonHoverTexture, NULL, &buttonRect);
        }
        else
        {
            SDL_RenderCopy(renderer, buttonTexture, NULL, &buttonRect);
        }

        // Cambiar la textura del segundo botón si el ratón está sobre él
        if (mouseX > buttonRect2.x && mouseX < buttonRect2.x + buttonRect2.w && mouseY > buttonRect2.y &&
            mouseY < buttonRect2.y + buttonRect2.h)
        {
            SDL_RenderCopy(renderer, buttonHoverTexture2, NULL, &buttonRect2);
        }
        else
        {
            SDL_RenderCopy(renderer, buttonTexture2, NULL, &buttonRect2);
        }

        // Cambiar la textura del tercer botón si el ratón está sobre él
        if (mouseX > buttonRect3.x && mouseX < buttonRect3.x + buttonRect3.w && mouseY > buttonRect3.y &&
            mouseY < buttonRect3.y + buttonRect3.h)
        {
            SDL_RenderCopy(renderer, buttonHoverTexture3, NULL, &buttonRect3);
        }
        else
        {
            SDL_RenderCopy(renderer, buttonTexture3, NULL, &buttonRect3);
        }

        // Cambiar la textura del cuarto botón si el ratón está sobre él
        if (mouseX > buttonRect4.x && mouseX < buttonRect4.x + buttonRect4.w && mouseY > buttonRect4.y &&
            mouseY < buttonRect4.y + buttonRect4.h)
        {
            SDL_RenderCopy(renderer, buttonHoverTexture4, NULL, &buttonRect4);
        }
        else
        {
            SDL_RenderCopy(renderer, buttonTexture4, NULL, &buttonRect4);
        }

        // Cambiar la textura del quinto botón si el ratón está sobre él
        if (mouseX > buttonRect5.x && mouseX < buttonRect5.x + buttonRect5.w && mouseY > buttonRect5.y &&
            mouseY < buttonRect5.y + buttonRect5.h)
        {
            SDL_RenderCopy(renderer, buttonHoverTexture5, NULL, &buttonRect5);
        }
        else
        {
            SDL_RenderCopy(renderer, buttonTexture5, NULL, &buttonRect5);
        }

        // Renderizar el sexto botón sin hover
        SDL_RenderCopy(renderer, buttonTexture6, NULL, &buttonRect6);

        SDL_RenderPresent(renderer);
    }
    Mix_FreeMusic(backgroundMusic);
    Mix_CloseAudio();
    SDL_DestroyTexture(buttonTexture6);
    SDL_DestroyTexture(buttonHoverTexture5);
    SDL_DestroyTexture(buttonTexture5);
    SDL_DestroyTexture(buttonHoverTexture4);
    SDL_DestroyTexture(buttonTexture4);
    SDL_DestroyTexture(buttonHoverTexture3);
    SDL_DestroyTexture(buttonTexture3);
    SDL_DestroyTexture(buttonHoverTexture2);
    SDL_DestroyTexture(buttonTexture2);
    SDL_DestroyTexture(buttonHoverTexture);
    SDL_DestroyTexture(buttonTexture);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    IMG_Quit();
    SDL_Quit();
}

void kontrolenVentana(SDL_Renderer *renderer)
{

    // Cargar la imagen de fondo
    const char *imagePath = "./img/menua/imagen1_hover.png";
    SDL_Texture *texture = IMG_LoadTexture(renderer, imagePath);

    // Ajustar el tamaño de la textura al tamaño de la ventana
    SDL_Rect dstrect = {0, 0, 1280, 720};

    // Cargar la textura del primer botón y su hover
    const char *buttonPath = "./img/menua/atzera.png";
    const char *buttonHoverPath = "./img/menua/atzera_hover.png";
    SDL_Texture *buttonTexture = IMG_LoadTexture(renderer, buttonPath);
    SDL_Texture *buttonHoverTexture = IMG_LoadTexture(renderer, buttonHoverPath);

    SDL_Rect buttonRect = {20, 20, 200, 100}; // Ajusta la posición y el tamaño del botón

    // Cargar la textura del segundo botón
    const char *secondButtonPath = "./img/menua/kontrolakk.png";
    SDL_Texture *secondButtonTexture = IMG_LoadTexture(renderer, secondButtonPath);

    SDL_Rect secondButtonRect = {150, 60, 1000, 600}; // Ajusta la posición y el tamaño del segundo botón

    // Bucle principal
    int running = 1;
    SDL_Event event;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                if (mouseX > buttonRect.x && mouseX < buttonRect.x + buttonRect.w && mouseY > buttonRect.y &&
                    mouseY < buttonRect.y + buttonRect.h)
                {
                    fprintf(stdout, "Primer botón clicado\n");
                    running = 0; // Salir del menú de configuración
                }
                else if (mouseX > secondButtonRect.x && mouseX < secondButtonRect.x + secondButtonRect.w &&
                         mouseY > secondButtonRect.y && mouseY < secondButtonRect.y + secondButtonRect.h)
                {
                    fprintf(stdout, "Segundo botón clicado\n");
                    // Agregar acción para el segundo botón
                }
            }
        }

        // Obtener la posición del ratón
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        // Renderizar fondo y botones
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, &dstrect);

        // Cambiar la textura del primer botón si el ratón está sobre él
        if (mouseX > buttonRect.x && mouseX < buttonRect.x + buttonRect.w && mouseY > buttonRect.y &&
            mouseY < buttonRect.y + buttonRect.h)
        {
            SDL_RenderCopy(renderer, buttonHoverTexture, NULL, &buttonRect);
        }
        else
        {
            SDL_RenderCopy(renderer, buttonTexture, NULL, &buttonRect);
        }

        SDL_RenderCopy(renderer, secondButtonTexture, NULL, &secondButtonRect);
        SDL_RenderPresent(renderer);
    }

    // Liberar recursos
    SDL_DestroyTexture(secondButtonTexture);
    SDL_DestroyTexture(buttonHoverTexture);
    SDL_DestroyTexture(buttonTexture);
    SDL_DestroyTexture(texture);
}

void KreditoenVentana(SDL_Renderer *renderer)
{
    // Cargar las texturas
    const char *imagePath = "./img/menua/imagen1_hover.png"; // Imagen de fondo
    SDL_Texture *backgroundTexture = IMG_LoadTexture(renderer, imagePath);

    const char *buttonPath = "./img/menua/atzera.png";
    const char *buttonHoverPath = "./img/menua/atzera_hover.png";
    SDL_Texture *buttonTexture = IMG_LoadTexture(renderer, buttonPath);
    SDL_Texture *buttonHoverTexture = IMG_LoadTexture(renderer, buttonHoverPath);

    SDL_Rect buttonRect = {-20, 20, 200, 100}; // Ajusta según sea necesario

    const char *secondButtonPath = "./img/menua/kredituak.png";
    SDL_Texture *secondButtonTexture = IMG_LoadTexture(renderer, secondButtonPath);

    SDL_Rect secondButtonRect = {150, 60, 1000, 600}; // Ajusta según sea necesario

    // Mantener la ventana de kreditoak abierta hasta que se cierre
    int running = 1;
    SDL_Event event;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                if (mouseX > buttonRect.x && mouseX < buttonRect.x + buttonRect.w && mouseY > buttonRect.y &&
                    mouseY < buttonRect.y + buttonRect.h)
                {
                    fprintf(stdout, "Primer botón clicado\n");
                    running = 0; // Puedes añadir una acción para cuando se haga clic en el primer botón
                }
                else if (mouseX > secondButtonRect.x && mouseX < secondButtonRect.x + secondButtonRect.w &&
                         mouseY > secondButtonRect.y && mouseY < secondButtonRect.y + secondButtonRect.h)
                {
                    fprintf(stdout, "Segundo botón clicado\n");
                    // Puedes añadir una acción para cuando se haga clic en el segundo botón
                }
            }
        }

        // Obtener la posición del ratón
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        // Limpiar la ventana y renderizar la nueva imagen de fondo
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

        // Cambiar la textura del primer botón si el ratón está sobre él
        if (mouseX > buttonRect.x && mouseX < buttonRect.x + buttonRect.w && mouseY > buttonRect.y &&
            mouseY < buttonRect.y + buttonRect.h)
        {
            SDL_RenderCopy(renderer, buttonHoverTexture, NULL, &buttonRect);
        }
        else
        {
            SDL_RenderCopy(renderer, buttonTexture, NULL, &buttonRect);
        }

        // Renderizar el segundo botón
        SDL_RenderCopy(renderer, secondButtonTexture, NULL, &secondButtonRect);

        // Presentar todo
        SDL_RenderPresent(renderer);
    }

    // Liberar recursos
    SDL_DestroyTexture(secondButtonTexture);
    SDL_DestroyTexture(buttonHoverTexture);
    SDL_DestroyTexture(buttonTexture);
    SDL_DestroyTexture(backgroundTexture);
}

void ZabalduJolasarenPantaila(SDL_Window *window, SDL_Renderer *renderer)
{

    // Limpiar la pantalla con un color de fondo (blanco en este caso)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Cargar la imagen de fondo
    const char *imagePath = "./img/menua/imagen1_hover.png";
    SDL_Texture *texture = IMG_LoadTexture(renderer, imagePath);

    // Ajustar el tamaño de la textura al tamaño de la ventana
    SDL_Rect dstrect = {0, 0, 1280, 720};

    // Renderizar la textura de fondo
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_RenderPresent(renderer);

    // Mantener el contenido en pantalla hasta que se cierre la ventana

    // Liberar la textura y recursos
    SDL_DestroyTexture(texture);

    // Destruir el renderer y la ventana
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void KontaktoaBotoiarenFuntzioa(SDL_Renderer *renderer)
{

    // Cargar la imagen de fondo
    const char *backgroundPath = "./img/menua/imagen1_hover.png"; // Ruta de la imagen de fondo
    SDL_Texture *backgroundTexture = IMG_LoadTexture(renderer, backgroundPath);

    // Ajustar el tamaño de la textura al tamaño de la ventana
    SDL_Rect dstrect = {0, 0, 1280, 720};

    // Cargar las texturas de los botones
    const char *newButtonPath = "./img/menua/atzera.png";
    const char *newButtonHoverPath = "./img/menua/atzera_hover.png";
    SDL_Texture *newButtonTexture = IMG_LoadTexture(renderer, newButtonPath);
    SDL_Texture *newButtonHoverTexture = IMG_LoadTexture(renderer, newButtonHoverPath);

    SDL_Rect newButtonRect = {-20, 20, 180, 100}; // Posición y tamaño del botón

    const char *additionalButtonPath = "./img/menua/kontaktuak.png";
    SDL_Texture *additionalButtonTexture = IMG_LoadTexture(renderer, additionalButtonPath);

    SDL_Rect additionalButtonRect = {150, 60, 1000, 600}; // Posición y tamaño del botón adicional

    // Bucle principal
    int running = 1;
    SDL_Event event;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                if (mouseX > newButtonRect.x && mouseX < newButtonRect.x + newButtonRect.w &&
                    mouseY > newButtonRect.y && mouseY < newButtonRect.y + newButtonRect.h)
                {
                    fprintf(stdout, "Nuevo botón clicado\n");
                    running = 0; // Salir del menú
                }
                else if (mouseX > additionalButtonRect.x && mouseX < additionalButtonRect.x + additionalButtonRect.w &&
                         mouseY > additionalButtonRect.y && mouseY < additionalButtonRect.y + additionalButtonRect.h)
                {
                    fprintf(stdout, "Botón adicional clicado\n");
                    // Agregar acción para este botón
                }
            }
        }

        // Renderizar el fondo y los botones
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, backgroundTexture, NULL, &dstrect);
        SDL_RenderCopy(renderer, newButtonTexture, NULL, &newButtonRect);
        SDL_RenderCopy(renderer, additionalButtonTexture, NULL, &additionalButtonRect);
        SDL_RenderPresent(renderer);
    }

    // Liberar recursos
    SDL_DestroyTexture(additionalButtonTexture);
    SDL_DestroyTexture(newButtonTexture);
    SDL_DestroyTexture(newButtonHoverTexture);
    SDL_DestroyTexture(backgroundTexture);
}

void EzarpenakBotoiarenFuntzioa(SDL_Window *window, SDL_Renderer *renderer)
{

    // Cargar la imagen de fondo
    const char *imagePath = "./img/menua/imagen1_hover.png"; // Cambia la ruta de la imagen
    SDL_Texture *texture = IMG_LoadTexture(renderer, imagePath);

    // Ajustar el tamaño de la textura al tamaño de la ventana
    SDL_Rect dstrect = {0, 0, 1280, 720};

    // Renderizar la textura de fondo
    SDL_RenderCopy(renderer, texture, NULL, &dstrect);
    SDL_RenderPresent(renderer);

    // Agregar un botón adicional
    const char *buttonPath = "./img/menua/atzera.png";
    const char *buttonHoverPath = "./img/menua/atzera_hover.png";
    SDL_Texture *buttonTexture = IMG_LoadTexture(renderer, buttonPath);
    SDL_Texture *buttonHoverTexture = IMG_LoadTexture(renderer, buttonHoverPath);

    SDL_Rect buttonRect = {-20, 20, 180, 100}; // Ajusta estos valores según sea necesario

    // Cargar la textura del nuevo botón
    const char *newButtonPath = "./img/menua/kreditoak.png";
    const char *newButtonHoverPath = "./img/menua/kreditoak_hover.png";
    SDL_Texture *newButtonTexture = IMG_LoadTexture(renderer, newButtonPath);
    SDL_Texture *newButtonHoverTexture = IMG_LoadTexture(renderer, newButtonHoverPath);

    SDL_Rect newButtonRect = {300, 300, 180, 100}; // Ajusta estos valores según sea necesario

    // Cargar la textura del tercer botón
    const char *thirdButtonPath = "./img/menua/kontaktoa.png";
    const char *thirdButtonHoverPath = "./img/menua/kontaktoa_hover.png";
    SDL_Texture *thirdButtonTexture = IMG_LoadTexture(renderer, thirdButtonPath);
    SDL_Texture *thirdButtonHoverTexture = IMG_LoadTexture(renderer, thirdButtonHoverPath);

    SDL_Rect kontaktoaButtonRect = {500, 300, 180, 100}; // Ajusta estos valores según sea necesario

    // Cargar la textura del cuarto botón
    const char *fourthButtonPath = "./img/menua/kontrolak.png";
    const char *fourthButtonHoverPath = "./img/menua/kontrolak_hover.png";
    SDL_Texture *fourthButtonTexture = IMG_LoadTexture(renderer, fourthButtonPath);
    SDL_Texture *fourthButtonHoverTexture = IMG_LoadTexture(renderer, fourthButtonHoverPath);

    SDL_Rect KontrolakButtonRect = {710, 296, 170, 98}; // Ajusta estos valores según sea necesario

    // Mantener la ventana de configuración abierta hasta que se cierre
    int running = 1;
    SDL_Event event;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = 0;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                if (mouseX > buttonRect.x && mouseX < buttonRect.x + buttonRect.w && mouseY > buttonRect.y &&
                    mouseY < buttonRect.y + buttonRect.h)
                {
                    fprintf(stdout, "Botón clicado\n");
                    PantailaPrintzipala(window, renderer);
                }
                else if (mouseX > newButtonRect.x && mouseX < newButtonRect.x + newButtonRect.w &&
                         mouseY > newButtonRect.y && mouseY < newButtonRect.y + newButtonRect.h)
                {
                    fprintf(stdout, "Nuevo botón clicado\n");
                    KreditoenVentana(renderer); // Llamar a la función para abrir la nueva ventana
                }
                else if (mouseX > kontaktoaButtonRect.x && mouseX < kontaktoaButtonRect.x + kontaktoaButtonRect.w &&
                         mouseY > kontaktoaButtonRect.y && mouseY < kontaktoaButtonRect.y + kontaktoaButtonRect.h)
                {
                    fprintf(stdout, "Tercer botón clicado\n");
                    KontaktoaBotoiarenFuntzioa(renderer); // Llamar a la función para abrir la nueva ventana
                }
                else if (mouseX > KontrolakButtonRect.x && mouseX < KontrolakButtonRect.x + KontrolakButtonRect.w &&
                         mouseY > KontrolakButtonRect.y && mouseY < KontrolakButtonRect.y + KontrolakButtonRect.h)
                {
                    fprintf(stdout, "Cuarto botón clicado\n");
                    kontrolenVentana(renderer); // Aquí puedes agregar la acción que deseas realizar cuando se haga
                                                // clic en el cuarto botón
                }
            }
        }

        // Obtener la posición del ratón
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);

        // Renderizar la textura de fondo y los botones en cada iteración del bucle
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, NULL, &dstrect);

        // Cambiar la textura del botón si el ratón está sobre él
        if (mouseX > buttonRect.x && mouseX < buttonRect.x + buttonRect.w && mouseY > buttonRect.y &&
            mouseY < buttonRect.y + buttonRect.h)
        {
            SDL_RenderCopy(renderer, buttonHoverTexture, NULL, &buttonRect);
        }
        else
        {
            SDL_RenderCopy(renderer, buttonTexture, NULL, &buttonRect);
        }

        // Cambiar la textura del nuevo botón si el ratón está sobre él
        if (mouseX > newButtonRect.x && mouseX < newButtonRect.x + newButtonRect.w && mouseY > newButtonRect.y &&
            mouseY < newButtonRect.y + newButtonRect.h)
        {
            SDL_RenderCopy(renderer, newButtonHoverTexture, NULL, &newButtonRect);
        }
        else
        {
            SDL_RenderCopy(renderer, newButtonTexture, NULL, &newButtonRect);
        }

        // Cambiar la textura del tercer botón si el ratón está sobre él
        if (mouseX > kontaktoaButtonRect.x && mouseX < kontaktoaButtonRect.x + kontaktoaButtonRect.w &&
            mouseY > kontaktoaButtonRect.y && mouseY < kontaktoaButtonRect.y + kontaktoaButtonRect.h)
        {
            SDL_RenderCopy(renderer, thirdButtonHoverTexture, NULL, &kontaktoaButtonRect);
        }
        else
        {
            SDL_RenderCopy(renderer, thirdButtonTexture, NULL, &kontaktoaButtonRect);
        }

        // Cambiar la textura del cuarto botón si el ratón está sobre él
        if (mouseX > KontrolakButtonRect.x && mouseX < KontrolakButtonRect.x + KontrolakButtonRect.w &&
            mouseY > KontrolakButtonRect.y && mouseY < KontrolakButtonRect.y + KontrolakButtonRect.h)
        {
            SDL_RenderCopy(renderer, fourthButtonHoverTexture, NULL, &KontrolakButtonRect);
        }
        else
        {
            SDL_RenderCopy(renderer, fourthButtonTexture, NULL, &KontrolakButtonRect);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(fourthButtonHoverTexture);
    SDL_DestroyTexture(fourthButtonTexture);
    SDL_DestroyTexture(thirdButtonHoverTexture);
    SDL_DestroyTexture(thirdButtonTexture);
    SDL_DestroyTexture(newButtonHoverTexture);
    SDL_DestroyTexture(newButtonTexture);
    SDL_DestroyTexture(buttonHoverTexture);
    SDL_DestroyTexture(buttonTexture);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
}
