#pragma once
#include "Unit.h"

DECLARE_SMART(Player, spPlayer);
class Player: public Unit
{
public:
    void move_to(int x,int y);
    void follow_path(std::vector<Point> path);

    void setSpeed(float speed);
    void shoot(int ammoType);

    const Vector2 &getPos() const;

protected:
    void _init();
    void _update(const UpdateState& us);

    spSprite _engine;
    spSprite _ship;
    bool following_path;
    std::vector<Point> path;
    Vector2 dir;
    int step;
    int lifePoint = 100;
    float speed;
    Vector2 pos;
};
