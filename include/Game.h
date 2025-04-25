#pragma once

#include<SDL2/SDL.h>
#include "Entity.h"

class Game {
private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
public:
    Game();
    void initSDL(const char *p_title, int p_w, int p_h);
    void loadMedia();
    void initEntity();
    SDL_Texture *loadTexture(const char *p_filePath);

    bool running();
    void clear();
    void handleEvents();
    void gameUpdate();
    void render(SDL_Texture *p_tex);
    void render(Entity &p_entity, SDL_Rect src = {0, 0, 0, 0});
    void renderText(string s, SDL_Rect src = {0, 0, 0, 0});
    void gameRender();
    void cleanUp();
    void gameLoop();

    int detectGesture();
    void spawnGhost();
};