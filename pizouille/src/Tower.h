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
    Tower();
    void build();
    void doUpdate(const UpdateState &us);
    void onClick();

private:
    bool built = false;

};


#endif //PROJECT_TOWER_H
