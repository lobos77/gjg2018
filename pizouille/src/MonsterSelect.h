//
// Created by mick on 1/27/18.
//

#ifndef PROJECT_MAP_H
#define PROJECT_MAP_H

#pragma once

#include <string>
#include "oxygine-framework.h"
using namespace oxygine;


class MonsterSelect : public Sprite {
public:
    MonsterSelect();

    void setAnim(std::string myCardName);
    bool isSelected();

private:
    void onEvent(Event* ev);
    bool _pressed;
    bool selected = false;

    spSprite _finger;
};


#endif //PROJECT_MAP_H
