#pragma once
#include "oxygine-framework.h"
#include "Grid.h"
#include "Playground.h"
#include "MonsterSelect.h"
#include "Player.h"

using namespace oxygine;

DECLARE_SMART(Monster, spMonster);
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
    void createAndLaunchMonster(float speed);
    std::list<Monster *> & getMonster_list();
	spPlayer getMainPlayer();
	std::vector<Monster *> &getMonsterGarbage();

	Vector2 cell_size;
    spPlayground _playground;
    spMonsterSelect _selector;
    spMonsterSelect _selector2;
    spMonsterSelect _selector3;

private:
    Game();
    friend class Player;

    void doUpdate(const UpdateState& us) override;

    spJoystick _move;
    spPlayer _player;
    spGrid _grid;
    std::list<Monster*> monster_list;
    std::vector<Point> path;
	std::vector<Monster*> monsterGarbage;
};
