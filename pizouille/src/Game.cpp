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
    spSprite sky = new Sprite;
    sky->setResAnim(res::ui.getResAnim("sky"));
    sky->attachTo(this);

    //spSprite map = new Map;
    //map->setResAnim(res::ui.getResAnim("map"));
    //map->attachTo(this);

    //create player ship
    _player = new Player;
    _player->init(this);

    _grid = new Grid;
    _grid->init(this);
    _grid->create(50);

    //create virtual joystick
    _move = new Joystick;
    _move->attachTo(this);
    _move->setY(getHeight() - _move->getHeight());
}

void Game::doUpdate(const UpdateState& us)
{
    //doUpdate is virtual method of Actor
    //it is being called each frame

    //update player each frame
    //_player->update(us);
}