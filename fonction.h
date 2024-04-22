#ifndef FONCTION_H_INCLUDED
#define FONCTION_H_INCLUDED

#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_gfxPrimitives.h>
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600
#define CASE_WIDTH (WINDOW_WIDTH / 3)
#define CASE_HEIGHT (WINDOW_HEIGHT / 3)

typedef struct
{
    SDL_Surface *img;
    SDL_Surface *imgO;
    SDL_Surface *imgX;
    int tabsuivi[9];
    int num;
    TTF_Font *police;
    SDL_Color color_txt;
    char texte[50];
    SDL_Rect tabPos[3][3];
} Tic;

void initTic(Tic* t);
void afficherTic(Tic t, SDL_Surface *ecran);
int atilganer(int tabsuivi[]);
void Resultat(int tabsuivi[], SDL_Surface *ecran);
void liberer(Tic t);
int minimax(int tabsuivi[9], int joueur);
void calcul_coup(int tabsuivi[9]);

#endif // FONCTION_H_INCLUDED





