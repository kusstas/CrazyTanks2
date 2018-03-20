// CrazyTanks game, @kusstas 2018. All Rights Reserved.

#ifndef WALL_H
#define WALL_H

#include "GameObject.h"
#include "IDamaged.h"

class Wall : public GameObject, public IDamaged
{
public:

    Wall(World& world);

    virtual void beginPlay() override;

    virtual Pixel getDrawing() const override;

    virtual void applyDamage(GameObject& damage) override;

protected:

    int lives_;
    int maxLives_;

};

#endif // !WALL_H