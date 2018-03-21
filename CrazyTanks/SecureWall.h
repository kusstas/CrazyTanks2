// CrazyTanks game, @kusstas 2018. All Rights Reserved.

#ifndef SECURE_WALL_H
#define SECURE_WALL_H

#include "Wall.h"

class SecureWall : public Wall
{
public:

    SecureWall(World& world);
    virtual void applyDamage(GameObject& initiator) override;
};

#endif // !SECURE_WALL_H