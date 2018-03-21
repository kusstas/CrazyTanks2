// CrazyTanks game, @kusstas 2018. All Rights Reserved.

#include "EnemyTank.h"

#include "AiController.h"
#include "World.h"

#include "Pixel.h"

int EnemyTank::count = 0;
int EnemyTank::team_ = 1;

EnemyTank::EnemyTank(World& world) : Tank(world)
{
    count++;

    maxCoolDown = 0.8f;
    maxDurationMove = 0.25f;
    indexTeam_ = getTeam();

    controller_ = new AiController();
}

EnemyTank::~EnemyTank()
{
    count--;
}

Pixel EnemyTank::getDrawing() const
{
    Pixel p = Tank::getDrawing();
    p.setColorSymbol(COLOR_LIGHT_GREEN);
    return p;
}

void EnemyTank::tick(float deltaTime)
{
    aiController_ = dynamic_cast<AiController*>(controller_);

    Tank::tick(deltaTime);
}

void EnemyTank::applyDamage(GameObject& initiator)
{
    Tank::applyDamage(initiator);

    if (aiController_ != nullptr)
        aiController_->onDamage();
}

void EnemyTank::onOverlap(GameObject& object, DVector2D location)
{
    Tank::onOverlap(object, location);

    if (aiController_ != nullptr)
        aiController_->onCollision();
}

void EnemyTank::onOverstepBorder()
{
    Tank::onOverstepBorder();

    if (aiController_ != nullptr)
        aiController_->onOverstepBorder();
}

int EnemyTank::getCount()
{
    return count;
}

int EnemyTank::getTeam()
{
    return team_;
}