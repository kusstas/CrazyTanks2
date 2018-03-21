// CrazyTanks game, @kusstas 2018. All Rights Reserved.

#include "PlayerTank.h"
#include "PlayerController.h"

PlayerTank* PlayerTank::instance = nullptr;
int PlayerTank::team_ = 0;

PlayerTank::PlayerTank(World& world) : Tank(world)
{
    instance = this;
    indexTeam_ = getTeam();

    maxDurationMove = 0.05f;

    controller_ = new PlayerController();
}

PlayerTank::~PlayerTank()
{
    instance = nullptr;
}

const PlayerTank* PlayerTank::getInstance()
{
    return instance;
}

int PlayerTank::getTeam()
{
    return team_;
}