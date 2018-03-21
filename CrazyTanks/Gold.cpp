// CrazyTanks game, @kusstas 2018. All Rights Reserved.

#include "Gold.h"
#include "Projectile.h"
#include "PlayerTank.h"

#include "Pixel.h"

Gold* Gold::instance_ = nullptr;

Gold::Gold(World& world) : GameObject(world)
{
    instance_ = this;

    maxLives_ = 1;
    lives_ = 0;
}

Gold::~Gold()
{
    instance_ = nullptr;
}

void Gold::beginPlay()
{
    lives_ = maxLives_;
}

Pixel Gold::getDrawing() const
{
    return Pixel (' ', COLOR_BLACK, COLOR_YELLOW);
}

void Gold::applyDamage(GameObject& initiator)
{
    Projectile* p = dynamic_cast<Projectile*>(&initiator);

    if (p != nullptr)
    {
        if (p->getIndexTeam() != PlayerTank::getTeam())
        {
            lives_--;
            if (lives_ == 0)
                destroy();
        }
    }
}

const Gold* Gold::getInstance()
{
    return instance_;
}