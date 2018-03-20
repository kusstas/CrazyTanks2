// CrazyTanks game, @kusstas 2018. All Rights Reserved.

#ifndef I_DAMAGED_H
#define I_DAMAGED_H

class GameObject;

class IDamaged
{
public:

    virtual void applyDamage(GameObject& initiator) = 0;
};

#endif // !I_DAMAGED_H