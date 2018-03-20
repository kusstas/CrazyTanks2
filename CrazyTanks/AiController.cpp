// CrazyTanks game, @kusstas 2018. All Rights Reserved.

#include "AiController.h"

#include "World.h"

#include "PlayerTank.h"

#include "SecureWall.h"
#include "Gold.h"

#include <random>

AiController::AiController()
{
    timerChange = 0.0f;
    timerReact = 0.0f;

    damageEffect = 0.0f;

    shouldFire_ = false;
}

void AiController::tick(float deltaTime)
{
    if (damageEffect)
    {
        timerDamageEffect += deltaTime;
        if (timerDamageEffect >= 2.0f)
        {
            damageEffect = false;
            timerDamageEffect = 0.0f;
        }
    }
    else
    {
        timerChange += deltaTime;
        if (timerChange > 1.5f && !shouldFire_)
        {
            changeDirect();

            if (moveDirect_ == ROTATION_Z_UP)
                moveDirect_ = ROTATION_Z_DOWN;

            timerChange = 0.0f;
        }

        checkEnemy();

        if (shouldFire_)
        {
            timerReact += deltaTime;
            if (timerReact >= 0.5f)
            {
                pawn_->fire();
                timerReact = 0.0f;
                shouldFire_ = false;
            }
            pawn_->stopMove();
        }
    }

    if (!shouldFire_)
        pawn_->startMove(moveDirect_);
}

void AiController::checkEnemy()
{
    if (shouldFire_)
        return;

    DVector2D loc = pawn_->getLocation();
    World* w = pawn_->getWorld();

    GameObject* goUp = w->trace(loc, ROTATION_Z_UP, 15);
    GameObject* goDn = w->trace(loc, ROTATION_Z_DOWN, 15);
    GameObject* goLt = w->trace(loc, ROTATION_Z_LEFT, 15);
    GameObject* goRt = w->trace(loc, ROTATION_Z_RIGHT, 15);


    PlayerTank* ptUp = dynamic_cast<PlayerTank*>(goUp);
    PlayerTank* ptDn = dynamic_cast<PlayerTank*>(goDn);
    PlayerTank* ptLt = dynamic_cast<PlayerTank*>(goLt);
    PlayerTank* ptRt = dynamic_cast<PlayerTank*>(goRt);

    SecureWall* swUp = dynamic_cast<SecureWall*>(goUp);
    SecureWall* swDn = dynamic_cast<SecureWall*>(goDn);
    SecureWall* swLt = dynamic_cast<SecureWall*>(goLt);
    SecureWall* swRt = dynamic_cast<SecureWall*>(goRt);

    Gold* glUp = dynamic_cast<Gold*>(goUp);
    Gold* glDn = dynamic_cast<Gold*>(goDn);
    Gold* glLt = dynamic_cast<Gold*>(goLt);
    Gold* glRt = dynamic_cast<Gold*>(goRt);

    if (ptUp != nullptr || swUp != nullptr || glUp != nullptr)
    {
        pawn_->setRotationZ(ROTATION_Z_UP);
        shouldFire_ = true;
    }
    else if (ptDn != nullptr || swDn != nullptr || glDn != nullptr)
    {
        pawn_->setRotationZ(ROTATION_Z_DOWN);
        shouldFire_ = true;
    }
    else if (ptLt != nullptr || swLt != nullptr || swLt != nullptr)
    {
        pawn_->setRotationZ(ROTATION_Z_LEFT);
        shouldFire_ = true;
    }
    else if (ptRt != nullptr || swRt != nullptr || glRt != nullptr)
    {
        pawn_->setRotationZ(ROTATION_Z_RIGHT);
        shouldFire_ = true;
    }
}

void AiController::onCollision()
{
    pawn_->fire();
}

void AiController::onOverstepBorder()
{
    changeDirect();
}

void AiController::onDamage()
{
    changeDirect();
    damageEffect = true;
    shouldFire_ = false;
}

void AiController::changeDirect()
{
    RotationZ r;
    do {
        r = static_cast<RotationZ>(rand() % 4);
    } while (r == moveDirect_);
    moveDirect_ = r;
}