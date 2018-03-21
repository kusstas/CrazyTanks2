// CrazyTanks game, @kusstas 2018. All Rights Reserved.

#include "AiController.h"

#include "World.h"
#include "Projectile.h"
#include "PlayerTank.h"

#include "SecureWall.h"
#include "Gold.h"

#include <random>

AiController::AiController()
{
    maxDistanceCheck = 10;

    timerChange = 0.0f;
    timerReact = 0.0f;

    damageEffect = 0.0f;

    shouldFire_ = false;
    damageEffect = false;
}

void AiController::tick(float deltaTime)
{
    if (damageEffect)
    {
        if (timerDamageEffect >= 2.0f)
        {
            damageEffect = false;
            timerDamageEffect = 0.0f;
        }
        else
        {
            pawn_->startMove(moveDirect_);
            timerDamageEffect += deltaTime;
        }
    }
    else
    {
        checkEnemy();
        
        if (!shouldFire_)
            handleMove(deltaTime);

        handleFire(deltaTime);
    }

    if (!shouldFire_)
        pawn_->startMove(moveDirect_);
}

void AiController::checkEnemy()
{
    DVector2D loc = pawn_->getLocation();

    RotationZ findDirect;
    bool isFind = false;

    World* w = pawn_->getWorld();

    auto validate = [](GameObject& go) 
    {
        Projectile* p = dynamic_cast<Projectile*>(&go);
        return p == nullptr;
    };

    // trace all direct
    GameObject* goUp = w->trace(loc, ROTATION_Z_UP, maxDistanceCheck, validate);
    GameObject* goDn = w->trace(loc, ROTATION_Z_DOWN, maxDistanceCheck, validate);
    GameObject* goLt = w->trace(loc, ROTATION_Z_LEFT, maxDistanceCheck, validate);
    GameObject* goRt = w->trace(loc, ROTATION_Z_RIGHT, maxDistanceCheck, validate);

    // Check on player tank
    PlayerTank* ptUp = dynamic_cast<PlayerTank*>(goUp);
    PlayerTank* ptDn = dynamic_cast<PlayerTank*>(goDn);
    PlayerTank* ptLt = dynamic_cast<PlayerTank*>(goLt);
    PlayerTank* ptRt = dynamic_cast<PlayerTank*>(goRt);

    // Check on secure wall
    SecureWall* swUp = dynamic_cast<SecureWall*>(goUp);
    SecureWall* swDn = dynamic_cast<SecureWall*>(goDn);
    SecureWall* swLt = dynamic_cast<SecureWall*>(goLt);
    SecureWall* swRt = dynamic_cast<SecureWall*>(goRt);

    // Check on gold
    Gold* glUp = dynamic_cast<Gold*>(goUp);
    Gold* glDn = dynamic_cast<Gold*>(goDn);
    Gold* glLt = dynamic_cast<Gold*>(goLt);
    Gold* glRt = dynamic_cast<Gold*>(goRt);

    if (ptUp != nullptr || swUp != nullptr || glUp != nullptr)
    {
        isFind = true;
        findDirect = ROTATION_Z_UP;
    }
    else if (ptDn != nullptr || swDn != nullptr || glDn != nullptr)
    {
        isFind = true;
        findDirect = ROTATION_Z_DOWN;
    }
    else if (ptLt != nullptr || swLt != nullptr || swLt != nullptr)
    {
        isFind = true;
        findDirect = ROTATION_Z_LEFT;
    }
    else if (ptRt != nullptr || swRt != nullptr || glRt != nullptr)
    {
        isFind = true;
        findDirect = ROTATION_Z_RIGHT;
    }

    if (isFind)
    {
        if (!shouldFire_)
        {
            shouldFire_ = true;
            pawn_->setRotationZ(findDirect);
        }
    }
    else
    {
        timerReact = 0.0f;
        shouldFire_ = false;
    }
}

void AiController::handleFire(float deltaTime)
{
    if (shouldFire_)
    {
        timerReact += deltaTime;
        if (timerReact >= 0.4f)
            pawn_->fire();

        timerChange = 0.0f;
        pawn_->stopMove();
    }
}

void AiController::handleMove(float deltaTime)
{
    timerChange += deltaTime;
    if (timerChange >= 1.5f)
    {
        changeDirect();

        if (moveDirect_ == ROTATION_Z_UP)
            moveDirect_ = ROTATION_Z_DOWN;

        timerChange = 0.0f;
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
}

void AiController::changeDirect()
{
    RotationZ r;
    do {
        r = static_cast<RotationZ>(rand() % 4);
    } while (r == moveDirect_);
    moveDirect_ = r;
}