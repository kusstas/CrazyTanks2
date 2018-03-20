// CrazyTanks game, @kusstas 2018. All Rights Reserved.

#include "SecureWall.h"


SecureWall::SecureWall(World& world) : Wall(world)
{
    maxLives_ = 10;
}