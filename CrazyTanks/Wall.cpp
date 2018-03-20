// CrazyTanks game, @kusstas 2018. All Rights Reserved.

#include "Wall.h"
#include "Pixel.h"

Wall::Wall(World& world) : GameObject(world)
{
    isStatic_ = true;
    maxLives_ = 3;
    lives_ = 0;
}

void Wall::beginPlay()
{
    GameObject::beginPlay();

    lives_ = maxLives_;
}

Pixel Wall::getDrawing() const
{
    Pixel p('@', COLOR_LIGHT_BLUE, COLOR_BLACK);

    float lev = static_cast<float>(lives_) / maxLives_;

    if (lev <= 0.68f && lev > 0.34f)
        p.setColorSymbol(COLOR_LIGHT_GREEN);
    else if (lev <= 0.34f)
        p.setColorSymbol(COLOR_LIGHT_RED);

    return p;
}

void Wall::applyDamage(GameObject& damage)
{
    lives_--;
    if (lives_ == 0)
        destroy();
}