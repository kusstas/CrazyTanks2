// CrazyTanks game, @kusstas 2018. All Rights Reserved.

#ifndef SECURE_WALL_H
#define SECURE_WALL_H

#include "Wall.h"

class SecureWall : public Wall
{
public:
    SecureWall(World& world);
};

#endif // !SECURE_WALL_H