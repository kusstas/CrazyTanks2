// CrazyTanks game, @kusstas 2018. All Rights Reserved.

#ifndef AI_CONTROLLER_H
#define AI_CONTROLLER_H

#include "Controller.h"
#include "CoreMinimal.h"

class AiController : public Controller
{
public:

    AiController();

    virtual void tick(float deltaTime) override;

    void onCollision();
    void onOverstepBorder();
    void onDamage();

private:

    RotationZ moveDirect_;
    float timerChange;
    float timerReact;
    float timerDamageEffect;

    void changeDirect();
    void checkEnemy();

    bool shouldFire_;
    bool damageEffect;
};

#endif // !AI_CONTROLLER_H