#include "Ghost.h"
#include "Utilities.h"

Ghost::Ghost() {
    ghostSpeed = 1;
    _isDead = 0;
}

void Ghost::addSymbol(int symbol) {
    vecSymbol.push_back(symbol);
}

int Ghost::getSize() {
    return (int)(vecSymbol.size());
}

int Ghost::getSymbol(int id) {
    return vecSymbol[id];
}

int Ghost::getFirstSymbol() {
    return vecSymbol.back();
}

void Ghost::removeSymbol() {
    vecSymbol.pop_back();
}

void Ghost::update() {
    if (SDL_GetTicks() - frameStart >= frameDelay) {
        nextFrame();
        frameStart = SDL_GetTicks();
    }
}

void Ghost::GhostMoving(double targetX, double targetY) {
    double dist = distance(x, y, targetX, targetY);
    if (dist == 0) return;
    double dirX = 1.0 * (targetX - x) / dist;
    double dirY = 1.0 * (targetY - y) / dist;
    x += dirX * ghostSpeed;
    y += dirY * ghostSpeed;
    // cerr<<x<<" "<<y<<"\n";
}

void Ghost::setDead() {
    _isDead = 1;
}

bool Ghost::isDead() {
    return _isDead;
}