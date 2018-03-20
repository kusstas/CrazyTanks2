// CrazyTanks game, @kusstas 2018. All Rights Reserved.

#include "CrazyTanks.h"
#include "WorldTanks.h"

#include "PlayerTank.h"
#include "EnemyTank.h"
#include "Gold.h"

#include "Screen.h"

#include <string>

void CrazyTanks::beginPlay()
{
    Game::beginPlay();

    isLose_ = false;
    isWin_ = false;

    loadWorld<WorldTanks>();
}

void CrazyTanks::tick(float deltaTime)
{
    Game::tick(deltaTime);

    int lives = PlayerTank::getInstance() != nullptr ? PlayerTank::getInstance()->getLives() : 0;

    isLose_ = lives == 0 || Gold::getInstance() == nullptr;
    isWin_ = EnemyTank::getCount() == 0;
}

void CrazyTanks::draw(Screen& screen)
{
    int lives = PlayerTank::getInstance() != nullptr ? PlayerTank::getInstance()->getLives() : 0;

    Game::draw(screen);

    if (isLose_)
    {
        screen.draw(50, 1, "You lose!");
    }
    else if (isWin_)
    {
        screen.draw(50, 1, "You win!");
    }
    else
    {
        std::string str = "Lives: ";
        for (int i = 0; i < lives; i++)
            str += '#';
        screen.draw(50, 1, str.c_str());
    }  
}