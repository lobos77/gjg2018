//
// Created by mick on 1/27/18.
//
#pragma once
#include "Tower.h"
#include "oxygine-framework.h"
#include "res.h"
using namespace oxygine;


#include "Tower.h"

Tower::Tower() {
    setResAnim(res::ui.getResAnim("tiled2"));
}

void Tower::build() {
    setResAnim(res::ui.getResAnim("tower")); //SelectedSimpleSquare
    built = true;
}

void Tower::onClick() {
    if(!built) {
        build();
    }
}

void Tower::doUpdate(const UpdateState& us) {
    if(built) {
        // Do firing
    }
}