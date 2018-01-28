//
// Created by mick on 1/27/18.
//

#ifndef PROJECT_MAP_H
#define PROJECT_MAP_H

#pragma once
#include "oxygine-framework.h"
using namespace oxygine;


class MonsterSelect : public Sprite {
public:
    MonsterSelect();

private:
    void onEvent(Event* ev);
    bool _pressed;

    spSprite _finger;
};


#endif //PROJECT_MAP_H
