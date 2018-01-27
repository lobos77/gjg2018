#include "Player.h"
#include "Game.h"
#include "res.h"
#include "Joystick.h"
#include <iostream>


void Player::move_to(int x,int y)
{
    std::cout << "move to" << x << "," << y << std::endl;
    //spTween tween = _ship->addTween(Actor::TweenPosition(x,y), 5000)
    _view->setPosition(x,y);
    spTween tween = _ship->addTween(Actor::TweenPosition(x,y), 5000);
}


void Player::_init()
{
    //initialize player's ship
    _view->setPosition(_game->getSize() / 2);


    _ship = new Sprite;
    _ship->setResAnim(res::ui.getResAnim("ship"));


    ResAnim *resAnim = res::ui.getResAnim("anim");
    // second parameter is the time between each images
    // third parameter is the number of loops, -1 is infinite.

    // two tweens : one moving from 400 to 300
    // the other animating the sprite.
    spTween tween1 = _ship->addTween(TweenAnim(resAnim), 500, -1);


    _ship->attachTo(_view);
    _ship->setAnchor(Vector2(0.5f, 0.5f));

    _engine = new Sprite;
    _engine->setResAnim(res::ui.getResAnim("shipengine"));
    _engine->attachTo(_ship);
    //animate engine's fire
    _engine->addTween(Sprite::TweenColor(Color::Red), 500, -1, true);
    //by default it is hidden
    //and would be visible only if ship moves
    _engine->setVisible(false);
}

void Player::_update(const UpdateState& us)
{
    _engine->setVisible(false);

    Vector2 dir;
    if (_game->_move->getDirection(dir))
    {
        //update player position according to delta time and finger direction from virtual joystick
        Vector2 pos = _view->getPosition();
        pos = pos + dir * (us.dt / 1000.0f) * 5;
        _view->setPosition(pos);

        //rotate it
        float angle = atan2f(dir.y, dir.x);
        _view->setRotation(angle);

        //if player moves show engine's fire
        _engine->setVisible(true);
    }
}