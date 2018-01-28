#include "Game.h"
#include "Joystick.h"
#include "Player.h"
#include "Map.h"
#include "res.h"
#include "Grid.h"

Game::Game()
{

}

void Game::init()
{
    //scene layer would have size of display
    setSize(getStage()->getSize());

    //create background
    //spSprite sky = new Sprite;
    //sky->setResAnim(res::ui.getResAnim("sky"));
    //sky->attachTo(this);

    //spSprite map = new Map;
    //map->setResAnim(res::ui.getResAnim("map"));
    //map->attachTo(this);

    for(int j = 0; j < 20; j ++){
        path.emplace_back(5+j, 5);
    }
    for(int j = 0; j <= 20; j ++){
        path.emplace_back(25, 5+j);
    }
    for(int j = 0; j < 20; j ++){
        path.emplace_back(25-j, 25);
    }
    for(int j = 0; j < 20; j ++){
        path.emplace_back(5, 25-j);
    }

    //create player ship

    _grid = new Grid;
    _grid->init(this);
    _grid->create(50);
    _grid->create_path(path);

    cell_size = _grid->getSquareSize();

    create_and_launch_player(15);

    //create virtual joystick
    /*_move = new Joystick;
    _move->attachTo(this);
    _move->setY(getHeight() - _move->getHeight());
    //*/
}

void Game::doUpdate(const UpdateState& us)
{
    //doUpdate is virtual method of Actor
    //it is being called each frame

    //update player each frame
    //_player->update(us);

    for(Player* monster : monster_list) {
        monster->update(us);
    }

    for (const std::vector<spTower> & towerRow : _grid->getCells()) {
        for (const spTower & tower : towerRow) {
            tower->doUpdate(us);
        }
    }
}

const std::list<Player *> &Game::getMonster_list() const {
    return monster_list;
}

void Game::create_and_launch_player(float speed) {
    auto * my_new_player = new Player;
    my_new_player->init(this);
    my_new_player->follow_path(path);
    my_new_player->setSpeed(speed);

    monster_list.push_back(my_new_player);
}
