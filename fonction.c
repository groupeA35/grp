#include "fonction.h"


void initTic(Tic *t)
{
    t->img = IMG_Load("images.png");
    t->imgO = IMG_Load("o.png");
    t->imgX = IMG_Load("x.png");

    int x = 30, y = 30;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            t->tabPos[i][j].x = x;
            t->tabPos[i][j].y = y;
            x += CASE_WIDTH;
        }
        x = 30;
        y += CASE_HEIGHT;
    }

    for (int i = 0; i < 9; i++)
    {
        t->tabsuivi[i] = 0;
    }

    t->num = 0;
    t->police = TTF_OpenFont("arial.ttf", 24);
    if (t->police == NULL)
    {
        printf("Failed to load font: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    t->color_txt.r = 255;
    t->color_txt.g = 255;
    t->color_txt.b = 255;
  
}



void afficherTic(Tic t, SDL_Surface *ecran)
{
    SDL_BlitSurface(t.img, NULL, ecran, NULL);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            SDL_Rect pos = t.tabPos[i][j];
            if (t.tabsuivi[i * 3 + j] == 1)
                SDL_BlitSurface(t.imgX, NULL, ecran, &pos);
            else if (t.tabsuivi[i * 3 + j] == -1)
                SDL_BlitSurface(t.imgO, NULL, ecran, &pos);
        }
    }

   /* SDL_Surface *textSurface = TTF_RenderText_Blended(t.police, t.texte, t.color_txt);
    SDL_Rect textRect;
    textRect.x = (WINDOW_WIDTH - textSurface->w) / 2;
    textRect.y = (WINDOW_HEIGHT - textSurface->h);
    SDL_BlitSurface(textSurface, NULL, ecran, &textRect);
    SDL_FreeSurface(textSurface);*/

    SDL_Flip(ecran);
}

int atilganer(int tabsuivi[])
{
    int lignes_gagnantes[8][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}, {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, {0, 4, 8}, {2, 4, 6}};
    for (int i = 0; i < 8; i++)
    {
        if (tabsuivi[lignes_gagnantes[i][0]] != 0 && tabsuivi[lignes_gagnantes[i][0]] == tabsuivi[lignes_gagnantes[i][1]] && tabsuivi[lignes_gagnantes[i][0]] == tabsuivi[lignes_gagnantes[i][2]])
            return tabsuivi[lignes_gagnantes[i][0]];
    }
    return 0;
}

void Resultat(int tabsuivi[], SDL_Surface *ecran)
{ 
    SDL_Color textColor = {255, 255, 255};
    int winner = atilganer(tabsuivi);
    char texte[50]; 
    for (int i = 0; i < 50; i++) {
        texte[i] = '\0';
    }

    if (winner != 0)
    {
        if (winner == 1)
            sprintf(texte, "HARD LUCK!");
        else if (winner == -1)
            sprintf(texte, "GOOD!");
    }
    else
    {
        sprintf(texte, "It's a draw!");
    }

    
    TTF_Font *police = TTF_OpenFont("arial.ttf", 24);
    if (police == NULL)
    {
        printf("Failed to load font: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    SDL_Surface *textSurface = TTF_RenderText_Blended(police, texte, textColor);
    SDL_Rect textRect;
    textRect.x = (WINDOW_WIDTH - textSurface->w) / 2;
    textRect.y = (WINDOW_HEIGHT - textSurface->h)/2;
    SDL_BlitSurface(textSurface, NULL, ecran, &textRect);
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(police);

    
    SDL_Flip(ecran);
}

void liberer(Tic t)
{
    SDL_FreeSurface(t.img);
    SDL_FreeSurface(t.imgO);
    SDL_FreeSurface(t.imgX);
    TTF_CloseFont(t.police);
}

int minimax(int tabsuivi[9], int joueur)
{
    int gagnant = atilganer(tabsuivi);
    if (gagnant != 0)
    {
        if ((joueur == 1 && gagnant == 1) || (joueur == -1 && gagnant == -1))
            return 1;
        else
            return -1;
    }

    int meilleure_valeur = (joueur == 1) ? -1 : 1;

    for (int i = 0; i < 9; i++)
    {
        if (tabsuivi[i] == 0)
        {
            tabsuivi[i] = joueur;
            int valeur_coup = minimax(tabsuivi, -joueur);
            tabsuivi[i] = 0;
            if (joueur == 1)
            {
                if (valeur_coup > meilleure_valeur)
                    meilleure_valeur = valeur_coup;
            }
            else
            {
                if (valeur_coup < meilleure_valeur)
                    meilleure_valeur = valeur_coup;
            }
        }
    }
    return meilleure_valeur;
}

void calcul_coup(int tabsuivi[9])
{
    int meilleure_valeur = -2;
    int meilleur_coup = -1;
    for (int i = 0; i < 9; i++)
    {
        if (tabsuivi[i] == 0)
        {
            tabsuivi[i] = 1;
            int valeur_coup = minimax(tabsuivi, -1);
            tabsuivi[i] = 0;
            if (valeur_coup > meilleure_valeur)
            {
                meilleure_valeur = valeur_coup;
                meilleur_coup = i;
            }
        }
    }
    if (meilleur_coup != -1)
        tabsuivi[meilleur_coup] = 1;
}

