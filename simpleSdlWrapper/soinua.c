#define SOINUA_C
#include "soinua.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>
// #include <cstring>

void musicUnload(void);
void soundsUnload();

Mix_Chunk *soinuak[MAX_SOUNDS];
int soinuKop = 0;
Mix_Music *musika = NULL;

void audioInit()
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }
}

int loadSound(char *fileName)
{
    if (soinuKop == MAX_SOUNDS)
    {
        return -1;
    }
    if ((soinuak[soinuKop] = Mix_LoadWAV(fileName)) == NULL)
    {
        printf("Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        return -1;
    }
    soinuKop++;
    return soinuKop - 1;
}

int loadTheMusic(char *fileName)
{
    int wasPlaying = 0;

    if (musika != NULL)
    {
        wasPlaying = (Mix_PlayingMusic() != 1);
        Mix_HaltMusic();
        // Mix_FreeMusic(musika);
    }
    if ((musika = Mix_LoadMUS(fileName)) == NULL)
    {
        return 0;
    }
    if (wasPlaying)
    {
        Mix_PlayMusic(musika, -1);
    }
    return 1;
}

int playSound(int idSound)
{
    if ((idSound <= 0) && (idSound >= soinuKop))
    {
        return -1;
    }
    Mix_PlayChannel(0, soinuak[idSound], 0);
    return idSound;
}

int playMusic(void)
{
    if (musika != NULL)
    {
        Mix_PlayMusic(musika, -1);
        return 1;
    }
    return 0;
}

void toggleMusic(void)
{
    if (musika != NULL)
    {
        if (Mix_PlayingMusic() != 0)
        {
            if (Mix_PausedMusic())
            {
                Mix_ResumeMusic();
            }
            else
            {
                Mix_PauseMusic();
            }
        }
        else
        {
            playMusic();
        }
    }
}

void musicUnload(void)
{
    if (musika != NULL)
    {
        Mix_HaltMusic();
        Mix_FreeMusic(musika);
    }
}

void soundsUnload()
{
    int i;

    for (i = 0; i < soinuKop; i++)
    {
        Mix_FreeChunk(soinuak[i]);
        soinuak[i] = NULL;
    }
    soinuKop = 0;
}

void audioTerminate(void)
{
    Mix_HaltChannel(-1);
    soundsUnload();
    musicUnload();
    Mix_Quit();
}

void soinu_Efektoak(char *filename)
{
    int soundId;

    soundId = loadSound(filename); // WAV
    if (soundId < 0)
    {
        printf("Failed to load sound: %s\n", filename);
        return;
    }
    if (soundId < 0)
    {
        printf("ondo: %s\n", filename);
        return;
    }

    Mix_PlayChannel(-1, soinuak[soundId], 0); // wav

    if (Mix_Playing(soundId) == 0)
    {
        soundsUnload();
    }
}

void musika_fondo(char *file)
{
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        return;
    }

    Mix_Music *bgm = Mix_LoadMUS(file);
    if (bgm == NULL)
    {
        printf("Failed to load background music! SDL_mixer Error: %s\n", Mix_GetError());
        return;
    }

    Mix_PlayMusic(bgm, -1);
}