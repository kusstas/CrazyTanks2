#include "Projectile.h"
#include "Tank.h"

#include "IDamaged.h"

#include "Pixel.h"


Projectile::Projectile(World& world) : GameObject(world)
{
    blockObject_ = false;
}

void Projectile::tick(float deltaTime)
{
    durationMove += deltaTime;
    if (durationMove > 0.01f)
    {
        durationMove = 0;
        GameObject::move(getRotationZ(), 1);
    }

    GameObject::tick(deltaTime);
}

void Projectile::onOverstepBorder()
{
    destroy();
}

void Projectile::onOverlap(GameObject& object, DVector2D location)
{
    IDamaged* obj = dynamic_cast<IDamaged*>(&object);

    if (obj != nullptr)
        obj->applyDamage(*this);

    destroy();
}

Pixel Projectile::getDrawing() const
{
    return Pixel('.', COLOR_WHITE, COLOR_BLACK);
}

int Projectile::getIndexTeam() const
{
    return indexTeam_;
}

void Projectile::setIndexTeam(int index)
{
    indexTeam_ = index;
}