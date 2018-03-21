// CrazyTanks game, @kusstas 2018. All Rights Reserved.

#include "CrazyTanks.h"
#include "WorldTanks.h"

#include "PlayerTank.h"
#include "EnemyTank.h"
#include "Gold.h"

#include "Screen.h"

#include <string>
#include <conio.h>

void CrazyTanks::beginPlay()
{
    Game::beginPlay();

    isPlay_ = true;
    isLose_ = false;
    isWin_ = false;

    loadWorld<WorldTanks>();
}

void CrazyTanks::tick(float deltaTime)
{
    if (isPlay_)
    {
        Game::tick(deltaTime);

        int lives = PlayerTank::getInstance() != nullptr ? PlayerTank::getInstance()->getLives() : 0;

        isLose_ = lives == 0 || Gold::getInstance() == nullptr;
        isWin_ = EnemyTank::getCount() == 0;
        isPlay_ = !isLose_ && !isWin_;
    }
    else if (_kbhit())
    {
        if (_getch() == 'r') // press 'r' key and restart game
            beginPlay();
    }
}

void CrazyTanks::draw(Screen& screen)
{
    int lives = PlayerTank::getInstance() != nullptr ? PlayerTank::getInstance()->getLives() : 0;

    Game::draw(screen);

    if (isPlay_)
    {
        std::string str = "Lives: ";
        for (int i = 0; i < lives; i++)
            str += '#';
        screen.draw(50, 1, str.c_str());
    }
    else
    {
        if (isLose_)
            screen.draw(50, 1, "Game over, dont worry =) Try again!");
        else if (isWin_)
            screen.draw(50, 1, "Victory, Well done =) Try again!");

        screen.draw(50, 2, "Press 'r' key for restart!");
    }
}