#pragma once
#include "oxygine-framework.h"
#include "Grid.h"

using namespace oxygine;

DECLARE_SMART(Player, spPlayer);
DECLARE_SMART(Joystick, spJoystick);
DECLARE_SMART(Game, spGame);
DECLARE_SMART(Grid, spGrid);
class Game: public Actor
{
public:
    Game();

    void init();

private:
    friend class Player;
    void doUpdate(const UpdateState& us);

    spJoystick _move;

    spPlayer _player;
    spGrid _grid;
};