// CrazyTanks game, @kusstas 2018. All Rights Reserved.

#include "SecureWall.h"
#include "Projectile.h"
#include "PlayerTank.h"


SecureWall::SecureWall(World& world) : Wall(world)
{
    maxLives_ = 10;
}

void SecureWall::applyDamage(GameObject& initiator)
{
    Projectile* p = dynamic_cast<Projectile*>(&initiator);

    if (p != nullptr)
    {
        if (p->getIndexTeam() != PlayerTank::getTeam())
            Wall::applyDamage(initiator);
    }
}