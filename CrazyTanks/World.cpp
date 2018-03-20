// CrazyTanks game, @kusstas 2018. All Rights Reserved.

#include "World.h"
#include "GameObject.h"

#include "Screen.h"
#include "Pixel.h"

#include <iterator>

using namespace std;

World::World()
{
}

World::World(const DVector2D& size)
{
    size_ = size;
}

World::World(int xSize, int ySize) : World(DVector2D(xSize, ySize))
{
}

World::~World()
{
    clear();
}

void World::beginPlay()
{
}

void World::tick(float deltaTime)
{
    for (int i = 0; i < gameObjects.size(); i++)
    {
        GameObject* go = gameObjects[i];

        if (go->isActive() && !go->isStatic())
            go->tick(deltaTime);
    }

    handleCollision();

    // phys tick
    for (int i = 0; i < gameObjects.size(); i++)
    {
        GameObject* go = gameObjects[i];

        if (go->isActive() && !go->isStatic())
            go->physTick();
    }

    destroyObjects();
}

void World::draw(Screen& screen)
{
    for (int i = 0; i < gameObjects.size(); i++)
    {
        GameObject* go = gameObjects[i];

        if (go->isActive())
        {
            int x = go->getLocation().x + offsetWorld_.x;
            int y = go->getLocation().y + offsetWorld_.y;

            screen.draw(x, y, go->getDrawing());
        }
    }
}

void World::clear()
{
    for (int i = 0; i < gameObjects.size(); i++)
    {
        delete gameObjects[i];
    }
}

const DVector2D& World::getSize() const
{
    return size_;
}

const vector<GameObject*>& World::getGameObjects() const
{
    return gameObjects;
}

GameObject* World::getGameObjectFromLocation(DVector2D location)
{
    GameObject* go = nullptr;

    for (int i = 0; i < gameObjects.size(); i++)
    {
        GameObject* curr = gameObjects[i];
        if (location == curr->getLocation())
        {
            go = curr;
            break;
        }
    }
    return go;
}

GameObject* World::getGameObjectFromLocation(int x, int y)
{
    return getGameObjectFromLocation(DVector2D(x, y));
}

GameObject* World::trace(DVector2D start, RotationZ direct, int distance)
{
    DVector2D vDirect = GameObject::getVector2DFromDirect(direct);

    for (int i = 1; i <= distance; i++)
    {
        DVector2D loc = vDirect * i;
        loc += start;
        GameObject* goRes = getGameObjectFromLocation(loc);

        if (goRes != nullptr)
            return goRes;
    }

    return nullptr;
}

GameObject* World::createGameObject()
{
    GameObject* go = createGameObject<GameObject>();
    return go;
}

void World::handleCollision()
{
    if (gameObjects.size() > 1)
    {
        for (int i = 0; i < gameObjects.size(); i++)
        {
            GameObject* go1 = gameObjects[i];

            for (int j = 0; j < gameObjects.size(); j++)
            {
                GameObject* go2 = gameObjects[j];

                if (go1 == go2)
                    continue;

                DVector2D v1 = go1->getLocation() - go1->getPrevLocation();
                DVector2D v2 = go2->getLocation() - go2->getPrevLocation();

                bool block = go1->isBlockObject() && go2->isBlockObject();
                bool intersect = go1->getLocation() == go2->getLocation();

                if (v1 != DVector2D::zeroVector && v2 != DVector2D::zeroVector)
                    intersect = intersect || (go1->getLocation() == go2->getPrevLocation());

                if (intersect)
                {
                    go1->onOverlap(*go2, go1->getLocation());
                    go2->onOverlap(*go1, go2->getLocation());

                    if (block)
                        go1->setLocation(go1->getPrevLocation());
                }
            }
        }
    }
}

void World::destroyObjects()
{
    for (vector<GameObject*>::iterator i = gameObjects.begin(); i != gameObjects.end(); ++i)
    {
        GameObject* go = *i;
        if (go->isShouldBeDestroyed())
        {
            vector<GameObject*>::iterator t;
            if (i == gameObjects.begin())
            {
                gameObjects.erase(i);
                t = gameObjects.begin();
            }
            else
            {
                t = i - 1;
                gameObjects.erase(i);
            }
            i = t;
            delete go;
        }
    }
}