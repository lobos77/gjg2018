#pragma once
#include "Unit.h"
#include "Game.h"

DECLARE_SMART(Monster, spMonster);
class Monster: public Unit
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

	spGame game;
    spSprite _engine;
    spSprite _ship;
    bool following_path;
    std::vector<Point> path;
    Vector2 dir;
    int step;
    int lifePoint = 100;
    float speed;
    Vector2 pos;
	int monsterType;
public:
	int getMonsterType() const;

	void setMonsterType(int monsterType);
};
