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
    Player * get_player() { return my_new_player;};
    void init();
    void create_and_launch_player(float speed);

    Vector2 cell_size;

private:
    friend class Player;
    void doUpdate(const UpdateState& us);

    spJoystick _move;

    //spPlayer _player;
    spPlayer _player;
    spGrid _grid;
    std::list<Player*> monster_list;
    std::vector<Point> path;

public:
    const std::list<Player *> &getMonster_list() const;
};