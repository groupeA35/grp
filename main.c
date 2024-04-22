#include "fonction.h"

int main() {
    SDL_Surface *ecran = NULL;
    SDL_Event event;
    int machineWins = 0;
    int playerWins = 0;
    int draws = 0;

    if (SDL_Init(SDL_INIT_VIDEO) == -1) {
        fprintf(stderr, "SDL Initialization Error: %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() == -1) {
        fprintf(stderr, "SDL_ttf Initialization Error: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    ecran = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (ecran == NULL) {
        fprintf(stderr, "SDL Video Mode Setting Error: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    SDL_WM_GrabInput(SDL_GRAB_ON); // This grabs input focus
    SDL_WM_SetCaption("Tic Tac Toe", NULL);

    for (int game = 0; game < 3; game++) {
        Tic t;
        initTic(&t);
        int tour = 1;
        int continuer = 1;

        while (continuer) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    continuer = 0;
                    break;
                } else if (event.type == SDL_MOUSEBUTTONDOWN && tour % 2 == 0) {
                    int x = event.button.x / CASE_WIDTH;
                    int y = event.button.y / CASE_HEIGHT;
                    int coup = 3 * y + x;
                    if (t.tabsuivi[coup] == 0) {
                        t.tabsuivi[coup] = -1;
                        tour++;
                    }
                } else if (event.type == SDL_KEYDOWN) {
                    if (tour % 2 == 0) { // Check if it's player O's turn
                        switch (event.key.keysym.sym) {
                            case SDLK_ESCAPE:
                                continuer = 0; // Exit the game if Escape is pressed
                                break;
                            case SDLK_2:
                                if (t.tabsuivi[7] == 0) { // Place O at position 7
                                    t.tabsuivi[7] = -1;
                                    tour++;
                                }
                                break;
                            case SDLK_3:
                                if (t.tabsuivi[8] == 0) { // Place O at position 8
                                    t.tabsuivi[8] = -1;
                                    tour++;
                                }
                                break;
                            case SDLK_4:
                                if (t.tabsuivi[3] == 0) { // Place O at position 3
                                    t.tabsuivi[3] = -1;
                                    tour++;
                                }
                                break;
                            case SDLK_5:
                                if (t.tabsuivi[4] == 0) { // Place O at position 4
                                    t.tabsuivi[4] = -1;
                                    tour++;
                                }
                                break;
                            case SDLK_6:
                                if (t.tabsuivi[5] == 0) { // Place O at position 5
                                    t.tabsuivi[5] = -1;
                                    tour++;
                                }
                                break;
                            case SDLK_1:
                                if (t.tabsuivi[6] == 0) { // Place O at position 1
                                    t.tabsuivi[6] = -1;
                                    tour++;
                                }
                                break;
                            
                            default:
                                break;
                        }
                    }
                }
            }

            afficherTic(t, ecran);

            if (tour >= 9 || atilganer(t.tabsuivi) != 0) {
                continuer = 0;
                break;
            }

            if (tour % 2 == 1 && atilganer(t.tabsuivi) == 0 && tour < 9) {
                calcul_coup(t.tabsuivi);
                tour++;
            }
        }

        Resultat(t.tabsuivi, ecran);

        int result = atilganer(t.tabsuivi);
        if (result == 1) {
            machineWins++;
        } else if (result == -1) {
            playerWins++;
        } else {
            draws++;
        }

        SDL_Delay(2000);

        liberer(t);
    }

    printf("Machine wins: %d\n", machineWins);
    printf("Player wins: %d\n", playerWins);
    printf("Draws: %d\n", draws);

    TTF_Quit();
    SDL_Quit();
    return 0;
}

