/*
//  main.c
//  SDL_Introduction : Creation of a gradient from black to white
//
//  Created by Sebastian Morera on 2021-08-21.
 
Concepts important du SDL:
1) Gestion de fênetre
2) Gestion de rendu (permettre de dessiner dans notre fênetre
3) Créer/Charger des textures (Texture (SDL2) est l'équivalent de surface (SDL1.2)

Différences entre SDL2 et SDL:
Pour ouvrir une fenêtre :   SDL_CreateWindow("titre", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN) == SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);
Pour changer le titre:      SDL_SetWindowTitle(window, "titre") == SDL_WM_SetCaption("titre", NULL)
Pour créer une surface:     SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED) == SDL_Surface *ecran = NULL;
Pour colorer une surface:   SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE) == SDL_MapRGB(ecran->format, 0, 0, 255)
Mise à jour de l'écran:     SDL_RenderPresent(renderer) == SDL_Flip(ecran)
*/

#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

#define WINDOW_WIDTH (256)
#define WINDOW_HEIGHT (256)

void SDL_ExitWithError(const char *message);
void PAUSE(void);

int main()
{
    char *title = "SDL Introduction";
    SDL_Window *window = NULL; //, *lignes[256] = {NULL};;
    SDL_Renderer *renderer = NULL;

    // Lancement SDL, chargement de tous les systemes
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        SDL_ExitWithError("Initialisation de la SDL");
    
    // Création fenêtre + rendu
    if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer) != 0)
        SDL_ExitWithError("Impossible de creer la fenetre et le rendu");

    SDL_SetWindowTitle(window, title);
    
    if (SDL_RenderClear(renderer) != 0)     // Nettoyer l'écran, effacer le rendu
        SDL_ExitWithError("Effacement rendu echouee");
    
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    SDL_Rect rectangle;
    for (int i = 0 ; i <= 255 ; i++)
    {
        if (SDL_SetRenderDrawColor(renderer, 0+i, 0+i, 0+i, SDL_ALPHA_OPAQUE) != 0)
            SDL_ExitWithError("Impossible de changer la couleur du rendu");
        
        rectangle.x = 0;
        rectangle.y = i;
        rectangle.w = 256;
        rectangle.h = 256;
        
        if (SDL_RenderFillRect(renderer, &rectangle) != 0)
            SDL_ExitWithError("Impossible de dessiner un rectangle");
        
        SDL_RenderPresent(renderer);    // Raffraichir le rendu
    }
    
    PAUSE(); // Mise en pause du programme
    
    if (SDL_RenderClear(renderer) != 0)     // Nettoyer l'écran, effacer le rendu
        SDL_ExitWithError("Effacement rendu echouee");

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}



void SDL_ExitWithError(const char *message)
{
    SDL_Log("Erreur: %s > %s \n", message ,SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void PAUSE()
{
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}
