// CrazyTanks game, @kusstas 2018. All Rights Reserved.

#ifndef ENEMY_TANK_H
#define ENEMY_TANK_H

#include "Tank.h"

class AiController;

class EnemyTank : public Tank
{
public:

    EnemyTank(World& world);
    ~EnemyTank();
    
    virtual Pixel getDrawing() const override;

    virtual void tick(float deltaTime) override;

    virtual void applyDamage(GameObject& initiator) override;
   
    virtual void onOverlap(GameObject& object, DVector2D location);
    virtual void onOverstepBorder();

    static int getCount();
    static int getTeam();

private:

    static int count;
    static int team_;

    AiController* aiController_;
};

#endif // !ENEMY_TANK_H