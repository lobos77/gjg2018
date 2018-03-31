#include "Player.h"
#include "Game.h"
#include "res.h"
#include "Joystick.h"
#include <iostream>
#include <utility>


void Player::move_to(int x,int y)
{
    std::cout << "move to " << x << ", " << y << std::endl;
    //spTween tween = _ship->addTween(Actor::TweenPosition(x,y), 5000)
    //_view->setPosition(x,y);
    spTween tween = _ship->addTween(Actor::TweenPosition(x,y), 5000);
}

void Player::follow_path(std::vector<Point> path){
    this->path = std::move(path);
    this->step = 0;
    following_path = true;
    Vector2 pos = _view->getPosition();
    float norm = (pos.distance(this->path[step]))/_game->cell_size.x;
    //auto norm = (float)sqrt(pow((this->path[step].x - pos.x), 2) + pow((this->path[step].y - pos.y), 2));
    dir = Vector2((this->path[step].x-pos.x)/norm, (this->path[step].y-pos.y)/norm);
}

void Player::setSpeed(float speed) {
    Player::speed = speed;
}

void Player::_init()
{
    //initialize player's ship
    //_view->setPosition(_game->getSize() / 2);
    _view->setPosition(Vector2(0,0));

    speed = 0;

    _ship = new Sprite;
    _ship->setResAnim(res::ui.getResAnim("ship"));
    _ship->setPriority(100);


    ResAnim *resAnim = res::ui.getResAnim("anim");
    // second parameter is the time between each images
    // third parameter is the number of loops, -1 is infinite.

    // two tweens : one moving from 400 to 300
    // the other animating the sprite.
    spTween tween1 = _ship->addTween(TweenAnim(resAnim), 500, -1);

    _ship->setAlpha(100);
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

    pos = _view->getPosition();
    if(following_path) {
        if( (pos + dir*speed).x >= path[step].x*_game->cell_size.x && dir.x > 0  ||
            (pos - dir*speed).x <= path[step].x*_game->cell_size.x && dir.x < 0){
            pos.x = path[step].x*_game->cell_size.x;
        }else{
            pos.x += dir.x*speed;
        }
        if( dir.y > 0 && (pos + dir*speed).y >= path[step].y*_game->cell_size.y ||
            (pos - dir*speed).y <= path[step].y*_game->cell_size.y && dir.y < 0){
            pos.y = path[step].y*_game->cell_size.y;
        }else{
            pos.y += dir.y*speed;
        }

        if(pos == Vector2(path[step].x*_game->cell_size.x, path[step].y*_game->cell_size.y)){
            if(step == path.size()-1){
                following_path = false;
            }else {
                step++;
                float norm = (pos.distance(this->path[step]));
                dir = Vector2((path[step].x*_game->cell_size.x-pos.x)/norm, (path[step].y*_game->cell_size.y-pos.y)/norm);
                Vector2 tmp = dir;
            }
        }
        _view->setPosition(pos);
    }
}

const Vector2 &Player::getPos() const {
    return pos;
}

void Player::shoot(int ammoType){
    lifePoint -= ammoType;
    if(lifePoint <= 0){
		spGame game = Game::getInstance();
		game->getMonster_list().remove(this);
		_ship->setVisible(false);
		delete this;
    }
}