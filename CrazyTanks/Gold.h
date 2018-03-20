// CrazyTanks game, @kusstas 2018. All Rights Reserved.

#ifndef GOLD_H
#define GOLD_H

#include "GameObject.h"
#include "IDamaged.h"

class Gold : public GameObject, public IDamaged
{
public:

    Gold(World& world);
    ~Gold();

    virtual void beginPlay() override;

    virtual Pixel getDrawing() const override;

    virtual void applyDamage(GameObject& initiator) override;

    static const Gold* getInstance();

private:

    static Gold* instance_;

    int lives_;
    int maxLives_;

};

#endif // !GOLD_H