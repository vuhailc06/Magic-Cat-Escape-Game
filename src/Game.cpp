#include "Game.h"
#include "Entity.h"
#include "Cat.h"
#include "Ghost.h"
#include "Constants.h"
#include "Utilities.h"

using namespace std;

enum GameStateName {
    GameOpenning,
    GamePlaying,
    GameEnding,
    TotalGameState
};

enum GameTextureName{
    CatTexture,
    CatDieTexture,
    GhostTexture,
    BackGroundTexture,
    ChantingTexture,
    CastingRedTexture,
    CastingBlueTexture,
    CastingYellowTexture,
    CastingGreenTexture,
    CastingHeartTexture,
    AttackPackTexture,
    HeartTexture,
    BonusTexture,
    FailureTexture,
    OpenningTexture,
    TotalGameTexutre
};

enum CatStateName {
    CatIdle,
    Chanting,
    CatDie,
    Red,
    Blue,
    Green, 
    Yellow,
    Heart,
    TotalCatState
};

SDL_Texture* GameTexture[TotalGameTexutre] = {NULL};
Cat cat[TotalCatState];
vector<Ghost> vecGhost;
Ghost ghost;
Entity attackPack, heart, bonusHeart;
int lastMagic, SCORE, GameState;

Mix_Chunk* ghostDieSound, *swipeEffect;

TTF_Font* font;

Game::Game() {
    isRunning = 1;
    GameState = GameOpenning;
    window = NULL;
    renderer = NULL;
}

bool Game::running() {
    return isRunning;
}

void Game::initSDL(const char *p_title, int p_w, int p_h) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "Failed to initialize SDL." << SDL_GetError();
    }
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0) {
        std::cout << "Failed to initialize SDL_image." << IMG_GetError();
    }
    if (TTF_Init() == -1) {
        std::cout << "Failed to initialize TTF. ", TTF_GetError();
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "Mix_OpenAudio Error: " << Mix_GetError();
    }
    window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED && SDL_RENDERER_PRESENTVSYNC); 
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
};

void Game::clear() {
    SetColor(renderer, whiteColor);
    SDL_RenderClear(renderer);
}

SDL_Texture *Game::loadTexture(const char *p_filePath) {
    SDL_Texture *texture = NULL;
    texture = IMG_LoadTexture(renderer, p_filePath);
    if (texture == NULL) {
        std::cout << "Failed to load texture: " << SDL_GetError() << "\n";
    }
    return texture;
}

void Game::loadMedia() {
    //images
    GameTexture[BackGroundTexture] = loadTexture("res/images/level1_stage.png");
    GameTexture[CatTexture] = loadTexture("res/images/idleCat.png");
    GameTexture[GhostTexture] = loadTexture("res/images/ghost.png");
    GameTexture[CastingRedTexture] = loadTexture("res/images/castingRed.png");
    GameTexture[CastingBlueTexture] = loadTexture("res/images/castingBlue.png");
    GameTexture[CastingYellowTexture] = loadTexture("res/images/castingYellow.png");
    GameTexture[CastingGreenTexture] = loadTexture("res/images/castingGreen.png");
    GameTexture[ChantingTexture] = loadTexture("res/images/catChanting.png");
    GameTexture[GhostTexture] = loadTexture("res/images/ghost.png");
    GameTexture[AttackPackTexture] = loadTexture("res/images/attackPack.png");
    GameTexture[CatDieTexture] = loadTexture("res/images/catDie.png");
    GameTexture[HeartTexture] = loadTexture("res/images/heart.png");
    GameTexture[BonusTexture] = loadTexture("res/images/bonusHeart.png");
    GameTexture[CastingHeartTexture] = loadTexture("res/images/castingHeart.png");
    GameTexture[FailureTexture] = loadTexture("res/images/failure.png");
    GameTexture[OpenningTexture] = loadTexture("res/images/open2.png");
    //fonts
    font = TTF_OpenFont("res/fonts/arial.ttf", 38);
    TTF_SetFontStyle(font, TTF_STYLE_BOLD);
    if (!font) {
        cout << "Failed to load font: " << TTF_GetError();
    }

    //musics
    Mix_Music* music = Mix_LoadMUS("res/sounds/backgroundsound.mp3");
    Mix_PlayMusic(music, -1);
    ghostDieSound = Mix_LoadWAV("res/sounds/diesound.wav");
    swipeEffect = Mix_LoadWAV("res/sounds/swipeeffect.wav");
}

void Game::initEntity() {
    cat[CatIdle].init(GameTexture[CatTexture], 100, 100, 20, 120);
    cat[Chanting].init(GameTexture[ChantingTexture], 150, 150, 6, 100);
    cat[Red].init(GameTexture[CastingRedTexture], 150, 150, 5, 100);
    cat[Blue].init(GameTexture[CastingBlueTexture], 150, 150, 5, 100);
    cat[Green].init(GameTexture[CastingGreenTexture], 150, 150, 5, 100);
    cat[Yellow].init(GameTexture[CastingYellowTexture], 150, 150, 5, 100);
    cat[Heart].init(GameTexture[CastingHeartTexture], 155, 155, 8, 60);
    cat[CatDie].init(GameTexture[CatDieTexture], 150, 150, 10, 100);

    cat[CatIdle].setHealth(CatHealth);
    cat[CatIdle].setX(SCREEN_WIDTH / 2); 
    cat[CatIdle].setY(SCREEN_HEIGHT / 2);
    for (int i = Chanting; i < TotalCatState; i++) {
        cat[i].setX(cat[CatIdle].getX() - 50);
        cat[i].setY(cat[CatIdle].getY() - 50);
    }

    cat[Heart].setX(cat[CatIdle].getX() + 50);
    cat[Heart].setX(cat[CatIdle].getY() + 180);

    SDL_SetTextureBlendMode(GameTexture[GhostTexture], SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(GameTexture[GhostTexture], 180); 

    attackPack.init(GameTexture[AttackPackTexture], 30, 30, 4, 0);
    bonusHeart.init(GameTexture[BonusTexture], 30, 30, 1, 0);
    heart.init(GameTexture[HeartTexture], 50, 50, 2, 0);
}

void Game::spawnGhost() {
    Ghost newGhost;
    newGhost.init(GameTexture[GhostTexture], 150, 150, 8, 100);

    int side = RandNum(0, 1);
    newGhost.setX(side ? SCREEN_WIDTH : 0);
    newGhost.setY(RandNum(0, SCREEN_HEIGHT));
    if (side == 0) newGhost.setFlip(SDL_FLIP_HORIZONTAL);

    int hard = RandNum(1, 1000);
    int numSymbol = RandNum(3, 6);

    bool hasHeart = 0;
    for (int i = 0; i < numSymbol; i++) {
        int tmp = RandNum(1, 100);
        if (tmp >= 97 && !hasHeart) {
            hasHeart = 1;
            newGhost.addSymbol(Heart);
        }
        else newGhost.addSymbol(RandNum(Red, Yellow));
    }
    vecGhost.push_back(newGhost);
}

bool drawing = false;
vector<pair<int, int>> points;

void Game::resetGame() {
    loadMedia();
    initEntity();
    vecGhost.clear();
    cat[CatIdle].setHealth(CatHealth);
    SCORE = 0;
}   

void Game::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT) {
        isRunning = false;
        return;
    };
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_RETURN) {
            GameState = GamePlaying;
        }
        if (event.key.keysym.sym == SDLK_r && GameState == GameEnding) {
            resetGame();
            GameState = GameOpenning;
        }
    }
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
            drawing = true;
        }
    }
    else if (event.type == SDL_MOUSEBUTTONUP) {
            drawing = false;
            points.clear();
    }
    else if (event.type == SDL_MOUSEMOTION) {
        if (drawing) points.push_back({event.motion.x, event.motion.y});
    }
}

int Game::detectGesture() {
    if ((int)points.size() == 0) return CatIdle;
    
    if (detectRed(points)) {
        SetColor(renderer, redColor);
        return Red;
    }
    if (detectBlue(points)) {
        SetColor(renderer, blueColor);
        return Blue;
    }
    if (detectYellow(points)) {
        SetColor(renderer, yellowColor);
        return Yellow;
    }
    if (detectGreen(points)) {
        SetColor(renderer, greenColor);
        return Green;
    }

    if (detectHeart(points)) {
        SetColor(renderer, pinkColor);
        return Heart;
    }
    
    return Chanting;
}

bool attacked = 0, playedSound;
int spawnGhostTime;

void Game::gameUpdate() {
    if (GameState != GamePlaying) return;

    if (SDL_GetTicks() - spawnGhostTime > spawnGhostDelay) {
        spawnGhost();
        spawnGhostTime = SDL_GetTicks();
    }

    auto collision = [](int ghostX, int ghostY) -> bool {
        int catX = cat[CatIdle].getX(), catY = cat[CatIdle].getY();
        if (ghostX < catX) {
            ghostX += ghost.getWidth();
            if (ghostY > catY) ghostY -= ghost.getHeight();
        } 
        else ghostX += 50;
        return distance(ghostX, ghostY, cat[CatIdle].getX(), cat[CatIdle].getY()) <= 120;
    };

    //cat die 
    if (cat[CatIdle].getHealth() == 0) {
        Mix_HaltMusic();
        cat[CatDie].setFrameDelay(200);
        if (cat[CatDie].getCur() >= 9) {
            GameState = GameEnding;
            return;
        }
        cat[CatDie].update();
        return;
    }

    for (int i = 0; i < (int)vecGhost.size(); i++) {
        auto &curGhost = vecGhost[i];
        //ghost attack cat
        if (!collision(curGhost.getX(), curGhost.getY())) curGhost.GhostMoving(cat[CatIdle].getX(), cat[CatIdle].getY());
        else if (!curGhost.isDead()) {
            curGhost.setFrameDelay(300);
            curGhost.update();
            if (curGhost.getCur() > 3) {
                curGhost.setCurrentFrame(0);
                cat[CatIdle].setHealth(cat[CatIdle].getHealth() - 1);
            }
        }
        
        if (curGhost.getSize() > 0 && !drawing && !attacked && lastMagic == curGhost.getFirstSymbol()) {
            if (lastMagic == Heart) {
                cat[CatIdle].setHealth(min(CatHealth, cat[CatIdle].getHealth() + 1));
                SCORE += 10;
            }
            else SCORE += 5;
            curGhost.removeSymbol();
        }

        //ghost die
        if (curGhost.getCur() >= 4) curGhost.update();
        else if (curGhost.getSize() == 0) {
            Mix_PlayChannel(-1, ghostDieSound, 0);
            curGhost.setCurrentFrame(4);
            curGhost.setDead();
            curGhost.setFrameDelay(100);
        } 
        if (curGhost.getCur() >= 7) {
            SCORE += 20;
            vecGhost.erase(vecGhost.begin() + i);
        }  
    }

    if (cat[CatIdle].getHealth() == 0) return;

    if (!attacked) attacked = 1;
    //cat update
    cat[CatIdle].update();
    if (drawing) {
        for (int i = Red; i <= Heart; i++) {
            cat[i].setCurrentFrame(0);
            cat[i].setFrameStart(SDL_GetTicks());
        }
        cat[Chanting].update();
        lastMagic = detectGesture();
        attacked = 0;
        playedSound = 0;
    }
    else {
        if (lastMagic == CatIdle || lastMagic == Chanting) return;
        if (!playedSound) {
            Mix_PlayChannel(-1, swipeEffect, 0);
            playedSound = 1;
        }
        if (cat[lastMagic].getCur() < cat[lastMagic].getNumFrames() - 1) {
            cat[lastMagic].update();
        }
        else {
            playedSound = 0;
            attacked = 0;
            cat[lastMagic].setCurrentFrame(0);
            lastMagic = 0;
        }
    }
}

SDL_Texture* Game::loadTextureFromText(string& p_text, TTF_Font* font, SDL_Color textColor) {
    char* text = &p_text[0];
    SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, text, textColor);
    SDL_Texture* message = NULL;
    message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    if (message == NULL)
        cout << "Failed to create texture from surface.";

    SDL_FreeSurface(surfaceMessage);
    return message;
}

void Game::renderText(double p_x, double p_y, string p_text, TTF_Font* font, SDL_Color textColor, SDL_Color backgroundColor) {
    char* text = &p_text[0];
    // SDL_Surface* surfaceMessage = TTF_RenderText_Shaded(font, text, textColor, backgroundColor);
    SDL_Surface* surfaceMessage = TTF_RenderText_Blended(font, text, textColor);
    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    SDL_Rect src;
    src.x = 0;
    src.y = 0;
    src.w = surfaceMessage->w;
    src.h = surfaceMessage->h;

    SDL_Rect dst;
    dst.x = p_x;
    dst.y = p_y;
    dst.w = src.w;
    dst.h = src.h;

    SDL_RenderCopy(renderer, message, &src, &dst);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(message);
}

void Game::render(SDL_Texture *p_tex) {
    SDL_RenderCopy(renderer, p_tex, NULL, NULL);
}

void Game::render(Entity &p_entity, SDL_Rect src) {
    if (src.w == 0) {
        SDL_QueryTexture(p_entity.getTexture(), NULL, NULL, &src.w, &src.h);
    }
    SDL_Rect dst = {(int)p_entity.getX(), (int)p_entity.getY(), p_entity.getWidth() , p_entity.getHeight()};
    if (p_entity.getFlip() == SDL_FLIP_HORIZONTAL) 
        SDL_RenderCopyEx(renderer, p_entity.getTexture(), &src, &dst, 0.0, NULL, SDL_FLIP_HORIZONTAL);
    else 
        SDL_RenderCopy(renderer, p_entity.getTexture(), &src, &dst);
}

void Game::gameRender() {
    //opening
    if (GameState == GameOpenning) {
        render(GameTexture[OpenningTexture]);
        SDL_RenderPresent(renderer);
        return;
    }
    //ending
    if (GameState == GameEnding) {
        render(GameTexture[FailureTexture]);
        renderText(750, 200, "YOUR SCORE", font, whiteColor, transparent);
        renderText(800, 300, toString(SCORE), font, whiteColor, transparent);
        renderText(650, 400, "PRESS R TO PLAY AGAIN", font, whiteColor, transparent);
        SDL_RenderPresent(renderer);
        return;
    }

    //playing

    //score
    render(GameTexture[BackGroundTexture]);
    renderText(SCREEN_WIDTH - 200, 10, toString(SCORE), font, whiteColor, whiteColor);

    //cat die
    if (cat[CatIdle].getHealth() == 0) {
        render(cat[CatDie], cat[CatDie].getCurrentFrame());
        SDL_RenderPresent(renderer);
        return;
    }

    //cat
    if (drawing) {
        render(cat[Chanting], cat[Chanting].getCurrentFrame());
    }
    else if (!drawing && lastMagic != CatIdle && lastMagic != Chanting) {
        if (cat[lastMagic].getCur() != -1) render(cat[lastMagic], cat[lastMagic].getCurrentFrame());
    }
    else render(cat[CatIdle], cat[CatIdle].getCurrentFrame());

    //drawing
    for (int i = 1; i < (int)points.size(); i++) {
        DrawSmoothStroke(renderer, points[i - 1].first, points[i - 1].second, points[i].first, points[i].second, 8);
    }

    //ghost
    for (auto &curGhost : vecGhost) {
        render(curGhost, curGhost.getCurrentFrame());
        int sx = curGhost.getX() + 20;
        int sy = curGhost.getY() - 5;
        for (int j = curGhost.getSize() - 1; j >= 0; j--) {
            bonusHeart.setX(sx); bonusHeart.setY(sy);
            attackPack.setX(sx);
            attackPack.setY(sy);
            int symbol = curGhost.getSymbol(j);
            if (symbol == Red) render(attackPack, attackPack.getFrame(0));
            if (symbol == Yellow) render(attackPack, attackPack.getFrame(1));
            if (symbol == Green) render(attackPack, attackPack.getFrame(2));
            if (symbol == Blue) render(attackPack, attackPack.getFrame(3));
            if (symbol == Heart) render(bonusHeart, bonusHeart.getFrame(0));
            if (symbol == Blue) sx += 15;
            else sx += attackPack.getWidth();
        }
    }

    //heart
    int hx = 50, hy = 10;
    for (int i = 1; i <= CatHealth; i++) {
        heart.setX(hx);
        heart.setY(hy);
        if (i <= cat[CatIdle].getHealth()) render(heart, heart.getFrame(1));
        else render(heart, heart.getFrame(0));
        hx += heart.getWidth() + 5;
    }


    SDL_RenderPresent(renderer);
}

void Game::cleanUp() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit;
    IMG_Quit;
}

void Game::gameLoop() {
    clear();
    handleEvents();
    gameUpdate();
    gameRender();
}