#pragma once

#include "Entity.h"

class Ghost : public Entity {
private:
    vector<int> vecSymbol;
    int ghostSpeed;
    bool _isDead;
public:
    Ghost();
    void update();
    void GhostDie();
    void GhostAttack();
    void GhostMoving(double targetX, double targetY);
    void addSymbol(int symbol);
    int getSymbol(int id);
    void removeSymbol();
    int getFirstSymbol();
    int getSize();
    bool isDead();
    void setDead();
};