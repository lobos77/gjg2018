//
// Created by mick on 1/27/18.
//
#pragma once

#include <climits>
#include "Tower.h"
#include "oxygine-framework.h"
#include "res.h"
using namespace oxygine;


#include "Tower.h"
#include "Monster.h"
#include "Game.h"

Tower::Tower(Vector2 pos) : position(pos) {
    setResAnim(res::ui.getResAnim("tiled2"));
    spGame game = Game::getInstance();
}

void Tower::build() {
    setResAnim(res::ui.getResAnim("tower")); //SelectedSimpleSquare
    built = true;
}


void Tower::onClick() {
    if(!built) {
        build();
    }else{
    	power += 10;
    }
}

void Tower::doUpdate(const UpdateState& us) {
    static timeMS lastAttack = 0;

    if(built) {
        if (lastAttack - us.time >= attack_speed) {
            unsigned int min_distance = UINT_MAX;
            unsigned int distance;
            Monster* target = nullptr;

            spGame game = Game::getInstance();
            for(Monster *const & player : game->getMonster_list()) {
                distance = static_cast<unsigned int>(position.distance(player->getPos()));
                if(distance < min_distance) {
                    min_distance = distance;
                    target = player;
                }
            }

            if(min_distance <= range) {
                lastAttack = us.time;
                target->shoot(power);
            }
        }
    }
}