// CrazyTanks game, @kusstas 2018. All Rights Reserved.

#include "GameObject.h"
#include "World.h"

#include "Pixel.h"

GameObject::GameObject(World& world) : world(&world)
{
    active_ = true;
    isStatic_ = false;
    blockObject_ = true;
    shouldBeDestroyed_ = false;
}

GameObject::~GameObject()
{
}

bool GameObject::isActive() const
{
    return active_;
}

bool GameObject::isStatic() const
{
    return isStatic_;
}

bool GameObject::isBlockObject() const
{
    return blockObject_;
}

bool GameObject::isShouldBeDestroyed() const
{
    return shouldBeDestroyed_;
}

const DVector2D& GameObject::getLocation() const
{
    return location_;
}

const DVector2D& GameObject::getPrevLocation() const
{
    return prevLocation_;
}

RotationZ GameObject::getRotationZ() const
{
    return rotationZ_;
}

World* GameObject::getWorld() const
{
    return world;
}

void GameObject::setActive(bool active)
{
    active_ = active;
}

void GameObject::setBlockObject(bool blockObject)
{
    blockObject_ = blockObject;
}

void GameObject::setLocation(const DVector2D& locaction)
{
    location_ = locaction;
    if (isStatic())
        prevLocation_ = getLocation();
}

void GameObject::setLocation(int x, int y)
{
    setLocation(DVector2D(x, y));
}

void GameObject::setRotationZ(RotationZ rotationZ)
{
    rotationZ_ = rotationZ;
}

void GameObject::move(DVector2D vector)
{
    setLocation(getLocation() + vector);
}

void GameObject::move(RotationZ direct, int scale)
{
    move(getVector2DFromDirect(direct) * scale);
}

Pixel GameObject::getDrawing() const
{
    return Pixel('#', COLOR_LIGHT_GREEN, COLOR_BLACK);
}

void GameObject::beginPlay()
{
}

void GameObject::tick(float deltaTime)
{
    checkOnOverstepBorder();
}

void GameObject::physTick()
{
    prevLocation_ = location_;
}

void GameObject::onOverlap(GameObject& object, DVector2D location)
{
}

void GameObject::onOverstepBorder()
{
}

void GameObject::destroy()
{
    shouldBeDestroyed_ = true;
}

void GameObject::checkOnOverstepBorder()
{
    DVector2D sizeWorld = world->getSize();

    bool isOverstep = false;
    if (location_.x < 0) {
        location_.x = 0;
        isOverstep = true;
    }
    else if (location_.x > sizeWorld.x - 1) {
        location_.x = sizeWorld.x - 1;
        isOverstep = true;
    }

    if (location_.y < 0) {
        location_.y = 0;
        isOverstep = true;
    }
    else if (location_.y > sizeWorld.y - 1) {
        location_.y = sizeWorld.y - 1;
        isOverstep = true;
    }

    if (isOverstep)
        onOverstepBorder();
}

DVector2D GameObject::getVector2DFromDirect(RotationZ direct)
{
    DVector2D vec;
    switch (direct)
    {
    case ROTATION_Z_DOWN:
        vec = DVector2D(0, 1);
        break;
    case ROTATION_Z_UP:
        vec = DVector2D(0, -1);
        break;
    case ROTATION_Z_LEFT:
        vec = DVector2D(-1, 0);
        break;
    case ROTATION_Z_RIGHT:
        vec = DVector2D(1, 0);
        break;
    }
    return vec;
}