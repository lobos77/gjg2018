#include "Game.h"
#include "Joystick.h"
#include "Monster.h"
#include "Map.h"
#include "res.h"
#include "Grid.h"
#include <iostream>

Game::Game()
{

}

void Game::init()
{
    //scene layer would have size of display
    Vector2 game_size = getStage()->getSize();
    setSize(getStage()->getSize());

    //create background
    //spSprite sky = new Sprite;
    //sky->setResAnim(res::ui.getResAnim("sky"));
    //sky->attachTo(this);

    //spSprite map = new Map;
    //map->setResAnim(res::ui.getResAnim("map"));
    //map->attachTo(this);

    // Create playground
    _playground = new Playground;
    _playground->attachTo(this);

    game_size.x-=game_size.x/3;
    game_size.y-=100;
    _playground->setSize(game_size);

    _selector = new MonsterSelect;
    _selector->attachTo(this);
    _selector->setPosition(_playground->getX()+_playground->getWidth(),0);


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

    std::cout << "path created" << std::endl; 

    //create player ship

    _grid = new Grid;
    std::cout << "grid object initialized" << std::endl; 
    _grid->init(this);
    std::cout << "grid initialized" << std::endl; 
    _grid->create(50);
    std::cout << "grid created" << std::endl; 
    _grid->create_path(path);
    std::cout << "grid path created" << std::endl; 
    

    cell_size = _grid->getSquareSize();

    createAndLaunchMonster(15);

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

    for(Monster* monster : monster_list) {
        monster->update(us);
    }

    for (const std::vector<spTower> & towerRow : _grid->getCells()) {
        for (const spTower & tower : towerRow) {
            tower->doUpdate(us);
        }
    }
}

std::list<Monster *> & Game::getMonster_list() {
    return monster_list;
}

void Game::createAndLaunchMonster(float speed) {
    auto * myMonster = new Monster;
    myMonster->init(this);
    myMonster->follow_path(path);
    myMonster->setSpeed(speed);
    myMonster->setMonsterType(1);

    monster_list.push_back(myMonster);
}

    monster_list.push_back(my_new_player);
}
