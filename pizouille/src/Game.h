#pragma once
#include "oxygine-framework.h"
#include "Grid.h"
#include "Playground.h"
#include "MonsterSelect.h"

using namespace oxygine;

DECLARE_SMART(Player, spPlayer);
DECLARE_SMART(Joystick, spJoystick);
DECLARE_SMART(Game, spGame);
DECLARE_SMART(Grid, spGrid);
DECLARE_SMART(Playground, spPlayground);
DECLARE_SMART(MonsterSelect, spMonsterSelect);
class Game: public Actor
{
public:
    static const spGame getInstance() {
        static spGame instance = new Game;
        return instance;
    }

    void init();
    void create_and_launch_player(float speed);
    std::list<Player *> & getMonster_list();

    Vector2 cell_size;
    spPlayground _playground;
    spMonsterSelect _selector;

private:
    Game();
    friend class Player;

    void doUpdate(const UpdateState& us);

    spJoystick _move;
    spPlayer _player;
    spGrid _grid;
    std::list<Player*> monster_list;
    std::vector<Point> path;
};
