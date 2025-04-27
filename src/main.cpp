#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<bits/stdc++.h>

#include "Game.h"
#include "Constants.h"
#include "Entity.h"

#include "Utilities.h"

Game *game = new Game();

int main(int argc, char* args[]) {
    game->initSDL("vuhailc06", SCREEN_WIDTH, SCREEN_HEIGHT);
    game->loadMedia();
    game->initEntity();

    int frameStart, frameTime;

    while (game->running()) {
        frameStart = SDL_GetTicks();
        game->gameLoop();
        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < frameDelay) {
            SDL_Delay(frameDelay - frameTime);
        }
    }   
    
    game->cleanUp();

    return 0;   
}