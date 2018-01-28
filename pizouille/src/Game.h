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
    static const spGame getInstance() {
        static spGame instance = new Game;
        return instance;
    }

    Player * get_player() { return _player;};
    void init();
    std::list<Player *> & getMonster_list();

    Vector2 cell_size;

private:
    Game();
    friend class Player;

    void doUpdate(const UpdateState& us);

    spJoystick _move;
    //spPlayer _player;
    Player* _player;
    spGrid _grid;
    std::list<Player*> monster_list;
};