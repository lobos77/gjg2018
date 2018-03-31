//
// Created by mick on 1/27/18.
//

#ifndef PROJECT_TOWER_H
#define PROJECT_TOWER_H

#pragma once
#include "oxygine-framework.h"
using namespace oxygine;

DECLARE_SMART(Tower, spTower);
class Tower : public Sprite {
public:
    Tower() {};
    Tower(Vector2 pos);
    void build();
    void doUpdate(const UpdateState &us);
    void onClick();

private:
    bool built = false;
    Vector2 position;
    unsigned int range = 20;
    unsigned int attack_speed = 500;
    unsigned int power = 10;
};


#endif //PROJECT_TOWER_H
